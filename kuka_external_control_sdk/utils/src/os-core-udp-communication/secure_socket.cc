// Copyright 2023 KUKA Deutschland GmbH
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "kuka/external-control-sdk/utils/os-core-udp-communication/secure_socket.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

namespace os::core::udp::communication
{

int dtls_verify_callback(int /*ok*/, X509_STORE_CTX * /*ctx*/) { return 1; }

const std::string MY_COOKIE = "MySuperSecureAndSecretCookie;)";

int dtls_cookie_generate_callback(SSL * /*ssl*/, unsigned char * cookie, unsigned int * cookie_len)
{
  memcpy(cookie, MY_COOKIE.c_str(), MY_COOKIE.size());
  *cookie_len = MY_COOKIE.size();
  return 1;
}

int dtls_cookie_verify_callback(
  SSL * /*ssl*/, const unsigned char * cookie, unsigned int cookie_len)
{
  return memcmp(cookie, MY_COOKIE.c_str(), cookie_len) == 0 ? 1 : 0;
}

SecureSocket::SecureSocket(Mode mode) : mode_(mode) {}

SecureSocket::SecureSocket(
  Mode mode, const std::string & certificate_path, const std::string & private_key_path)
: mode_(mode),
  certificate_path_(std::make_optional(certificate_path)),
  private_key_path_(std::make_optional(private_key_path))
{
}

SecureSocket::~SecureSocket() { Close(); }

int SecureSocket::Map(int flags)
{
  if (IsActive())
  {
    return SetError(ErrorCode::kAlreadyActive);
  }

  // create SSL context
  if (mode_ != Mode::accepted)
  {
    ssl_context_ = SSL_CTX_new(DTLS_method());
    if (ssl_context_ == nullptr)
    {
      return SetError(ErrorCode::kSecureLayerError, 0);
    }

    SSL_CTX_set_verify(
      ssl_context_, SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE, dtls_verify_callback);
    SSL_CTX_set_session_cache_mode(ssl_context_, SSL_SESS_CACHE_OFF);
    SSL_CTX_set_cookie_generate_cb(ssl_context_, &dtls_cookie_generate_callback);
    SSL_CTX_set_cookie_verify_cb(ssl_context_, &dtls_cookie_verify_callback);

    if (certificate_path_.has_value())
    {
      if (!SSL_CTX_use_certificate_file(
            ssl_context_, certificate_path_.value().c_str(), SSL_FILETYPE_PEM))
      {
        SSL_CTX_free(ssl_context_);
        ssl_context_ = nullptr;
        return SetError(ErrorCode::kSecureLayerError, 0);
      }
    }
    if (private_key_path_.has_value())
    {
      if (!SSL_CTX_use_PrivateKey_file(
            ssl_context_, private_key_path_.value().c_str(), SSL_FILETYPE_PEM))
      {
        SSL_CTX_free(ssl_context_);
        ssl_context_ = nullptr;
        return SetError(ErrorCode::kSecureLayerError, 0);
      }
      if (!SSL_CTX_check_private_key(ssl_context_))
      {
        SSL_CTX_free(ssl_context_);
        ssl_context_ = nullptr;
        return SetError(ErrorCode::kSecureLayerError, 0);
      }
    }
  }

  if (Socket::Map(flags) < 0)
  {
    SSL_CTX_free(ssl_context_);
    ssl_context_ = nullptr;
    return SetError(ErrorCode::kSocketError);
  }

  if (!ssl_obj_ && mode_ != Mode::server)
  {
    // create SSL object
    ssl_obj_ = SSL_new(ssl_context_);
    if (ssl_obj_ == nullptr)
    {
      SSL_CTX_free(ssl_context_);
      ssl_context_ = nullptr;
      return SetError(ErrorCode::kSecureLayerError, 0);
    }
    SSL_set_fd(ssl_obj_, socket_fd_);
  }

  return socket_fd_;
}

int SecureSocket::DoHandshake()
{
  if (ssl_up_)
  {
    return SSL_ERROR_SYSCALL;
  }

  if (mode_ == Mode::expect_client)
  {
    int ret = SSL_get_error(ssl_obj_, SSL_accept(ssl_obj_));
    if (!(ret == SSL_ERROR_NONE || ret == SSL_ERROR_WANT_READ))
    {
      return SetError(ErrorCode::kSecureLayerError, ret);
    }
    ssl_up_ = true;
  }
  else if (mode_ == Mode::client)
  {
    int ret = SSL_get_error(ssl_obj_, SSL_connect(ssl_obj_));
    if (!(ret == SSL_ERROR_NONE || ret == SSL_ERROR_WANT_READ))
    {
      return SetError(ErrorCode::kSecureLayerError, ret);
    }
    ssl_up_ = true;
  }
  else
  {
    ssl_up_ = true;
  }
  return SetError(ErrorCode::kSuccess);
}

int SecureSocket::Send(const unsigned char * raw_data, int raw_data_size, int /*flags*/)
{
  if (!IsActive() || !ssl_up_)
  {
    return SetError(ErrorCode::kNotActive);
  }
  if (remote_address_ == std::nullopt)
  {
    return SetError(ErrorCode::kNotConnected);
  }
  size_t sent_bytes = 0;
  int ret = SSL_write_ex(ssl_obj_, raw_data, raw_data_size, &sent_bytes);
  if (ret <= 0)
  {
    return SetError(ErrorCode::kSecureLayerError, SSL_get_error(ssl_obj_, ret));
  }
  return sent_bytes;
}

int SecureSocket::SendTo(
  const SocketAddress & /*remote_address*/, const unsigned char * /*raw_data*/,
  int /*raw_data_size*/, int /*flags*/)
{
  throw "NOT SUPPORTED";
}

int SecureSocket::Receive(unsigned char * buffer, int buffer_size, int /*flags*/)
{
  if (!IsActive() || !ssl_up_)
  {
    return SetError(ErrorCode::kNotActive);
  }
  if (local_address_ == std::nullopt)
  {
    return SetError(ErrorCode::kNotBound);
  }
  size_t received_bytes;
  int ret = SSL_read_ex(ssl_obj_, buffer, buffer_size, &received_bytes);
  if (ret == 0)
  {
    Close();
    return SetError(ErrorCode::kClosed);
  }
  else if (ret < 0)
  {
    return SetError(ErrorCode::kSecureLayerError, SSL_get_error(ssl_obj_, ret));
  }
  return received_bytes;
}

int SecureSocket::ReceiveFrom(
  SocketAddress & /*incoming_remote_address*/, unsigned char * /*buffer*/, int /*buffer_size*/,
  int /*flags*/)
{
  throw "NOT SUPPORTED";
}

std::string SecureSocket::GetLastErrorText() const
{
  if (last_error_state_ == ErrorCode::kSecureLayerError)
  {
    return GetSSLErrorText();
  }
  else
  {
    return Socket::GetLastErrorText();
  }
}

int SecureSocket::Close()
{
  if (IsActive())
  {
    if (ssl_obj_)
    {
      if (ssl_up_)
      {
        SSL_shutdown(ssl_obj_);
      }
      SSL_free(ssl_obj_);
    }
    if (ssl_context_ && mode_ != Mode::accepted)
    {
      SSL_CTX_free(ssl_context_);
    }
    ::close(socket_fd_);
    socket_fd_ = -1;
    ssl_up_ = false;
    ssl_obj_ = nullptr;
    ssl_context_ = nullptr;
    return ErrorCode::kSuccess;
  }
  return ErrorCode::kNotActive;
}

int SecureSocket::SetError(ErrorCode code, int err_no)
{
  last_error_state_ = code;
  if (code == ErrorCode::kSecureLayerError)
  {
    last_errno_ = err_no;
  }
  else if (code == ErrorCode::kSocketError)
  {
    last_errno_ = errno;
  }
  else
  {
    last_errno_ = 0;
  }
  return code;
}

std::unique_ptr<SecureSocket> SecureSocket::Accept()
{
  if (mode_ != Mode::server)
  {
    SetError(ErrorCode::kError);
    return nullptr;
  }
  if (!IsActive() || !ssl_up_)
  {
    SetError(ErrorCode::kNotActive);
    return nullptr;
  }

  SSL * new_ssl = SSL_new(ssl_context_);
  auto bio = BIO_new_dgram(socket_fd_, BIO_NOCLOSE);
  SSL_set_bio(new_ssl, bio, bio);
  SSL_set_options(new_ssl, SSL_OP_COOKIE_EXCHANGE);

  sockaddr_in client_addr;
  memset(&client_addr, 0, sizeof(struct sockaddr_in));

  int ret = 0;
  if ((ret = DTLSv1_listen(new_ssl, (BIO_ADDR *)&client_addr)) > 0)
  {
    SocketAddress addr(&client_addr);
    auto accepted = CreateAcceptedSocket(ssl_context_, new_ssl, &client_addr);
    if (accepted->GetLastSocketError().first == ErrorCode::kSuccess)
    {
      ret = SSL_accept(new_ssl);
    }
    return (accepted);
  }
  else if (ret == 0)
  {
    SetError(ErrorCode::kSocketError, errno);
    return nullptr;
  }
  else
  {
    SetError(ErrorCode::kSecureLayerError, SSL_get_error(new_ssl, ret));
    return nullptr;
  }
}

std::unique_ptr<SecureSocket> SecureSocket::CreateAcceptedSocket(
  SSL_CTX * ssl_ctx, SSL * ssl_obj, const struct sockaddr_in * remote)
{
  std::unique_ptr<SecureSocket> accepted_socket = std::make_unique<SecureSocket>(Mode::accepted);
  accepted_socket->ssl_context_ = ssl_ctx;
  accepted_socket->ssl_obj_ = ssl_obj;
  accepted_socket->ssl_up_ = true;
  int fd = accepted_socket->Map();
  accepted_socket->SetReuseAddress();
  accepted_socket->Bind(local_address_.value());
  accepted_socket->Connect(SocketAddress(remote));

  BIO_set_fd(SSL_get_rbio(ssl_obj), fd, BIO_NOCLOSE);
  int ss = AF_INET;
  BIO_ctrl(SSL_get_rbio(ssl_obj), BIO_CTRL_DGRAM_SET_CONNECTED, 0, &ss);

  return accepted_socket;
}

std::string SecureSocket::GetSSLErrorText() const
{
  char ssl_err_buf[1024];
  return ERR_error_string(last_errno_, ssl_err_buf);
}

}  // namespace os::core::udp::communication
