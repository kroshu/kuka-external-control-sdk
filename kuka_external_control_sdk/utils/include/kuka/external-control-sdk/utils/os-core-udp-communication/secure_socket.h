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

#ifndef KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__SECURE_SOCKET_H_
#define KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__SECURE_SOCKET_H_

#include <openssl/err.h>
#include <openssl/ssl.h>

#include <memory>
#include <string>

#include "kuka/external-control-sdk/utils/os-core-udp-communication/socket.h"

namespace os::core::udp::communication
{

class SecureSocket : public Socket
{
public:  // <types>
  typedef Socket::ErrorCode ErrorCode;
  enum class Mode
  {
    client,
    expect_client,
    server,
    accepted
  };

public:  // <ctor>
  explicit SecureSocket(Mode mode);
  SecureSocket(
    Mode mode, const std::string & certificate_path, const std::string & private_key_path);
  virtual ~SecureSocket();

public:  // <Socket>
  int Map(int flags = 0) override;
  int DoHandshake() override;

  int Send(const unsigned char * raw_data, int raw_data_size, int flags = 0) override;
  int SendTo(
    const SocketAddress & remote_address, const unsigned char * raw_data, int raw_data_size,
    int flags = 0) override;
  int Receive(unsigned char * buffer, int buffer_size, int flags = 0) override;
  int ReceiveFrom(
    SocketAddress & incoming_remote_address, unsigned char * buffer, int buffer_size,
    int flags = 0) override;
  int Close() override;
  std::string GetLastErrorText() const override;

protected:  // <Socket>
  int SetError(ErrorCode code, int err_no = 0) override;

public:  // <operations>
  std::unique_ptr<SecureSocket> Accept();

protected:  // <operations>
  std::unique_ptr<SecureSocket> CreateAcceptedSocket(
    SSL_CTX * ssl_ctx, SSL * ssl_obj, const struct sockaddr_in * remote);
  std::string GetSSLErrorText() const;

protected:
  Mode mode_;
  std::optional<std::string> certificate_path_;
  std::optional<std::string> private_key_path_;

protected:
  bool ssl_up_ = false;
  SSL_CTX * ssl_context_ = nullptr;
  SSL * ssl_obj_ = nullptr;
};

}  // namespace os::core::udp::communication

#endif  // KUKA__EXTERNAL_CONTROL_SDK__UTILS__OS_CORE_UDP_COMMUNICATION__SECURE_SOCKET_H_
