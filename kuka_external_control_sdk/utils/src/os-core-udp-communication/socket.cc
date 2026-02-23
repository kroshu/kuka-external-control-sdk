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

#include "kuka/external-control-sdk/utils/os-core-udp-communication/socket.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <string>

namespace os::core::udp::communication
{

const char SocketAddress::kAnyAddress[] = "0.0.0.0";

// Possible features:
// - IPv6
// - implement isReadable(MSG_PEEK) to check whether any message without consuming it

SocketAddress::SocketAddress()
{
  memset(&sockaddr_, 0, sizeof(sockaddr_));
  sockaddr_.sin_family = AF_INET;
  sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
  sockaddr_.sin_port = htons(0);
  port_ = 0;
  memset(ip_, 0, INET_ADDRSTRLEN);
  memcpy(ip_, kAnyAddress, strlen(kAnyAddress));
}

SocketAddress::SocketAddress(const std::string & ip, int port)
{
  memset(&sockaddr_, 0, sizeof(sockaddr_));
  sockaddr_.sin_family = AF_INET;
  sockaddr_.sin_addr.s_addr = inet_addr(ip.c_str());
  sockaddr_.sin_port = htons(port);
  port_ = port;
  memset(ip_, 0, INET_ADDRSTRLEN);
  memcpy(ip_, ip.c_str(), ip.size());
}

SocketAddress::SocketAddress(const std::string & ip)
{
  memset(&sockaddr_, 0, sizeof(sockaddr_));
  sockaddr_.sin_family = AF_INET;
  sockaddr_.sin_addr.s_addr = inet_addr(ip.c_str());
  sockaddr_.sin_port = htons(0);
  port_ = 0;
  memset(ip_, 0, INET_ADDRSTRLEN);
  memcpy(ip_, ip.c_str(), ip.size());
}

SocketAddress::SocketAddress(int port)
{
  memset(&sockaddr_, 0, sizeof(sockaddr_));
  sockaddr_.sin_family = AF_INET;
  sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
  sockaddr_.sin_port = htons(port);
  port_ = port;
  memset(ip_, 0, INET_ADDRSTRLEN);
  memcpy(ip_, kAnyAddress, strlen(kAnyAddress));
}

SocketAddress::SocketAddress(const struct sockaddr_in * raw_address)
{
  memcpy(&sockaddr_, raw_address, sizeof(sockaddr_));
  port_ = ntohs(sockaddr_.sin_port);
  inet_ntop(AF_INET, &(sockaddr_.sin_addr), ip_, sizeof(ip_));
}

bool IsValidIP(const char * ip_address)
{
  struct sockaddr_in sa;
  int result = inet_pton(AF_INET, ip_address, &(sa.sin_addr));
  return result != 0;
}

std::optional<SocketAddress> SocketAddress::SafeConstruct(const std::string & ip, int port)
{
  if (!IsValidIP(ip.c_str()))
  {
    return std::nullopt;
  }
  return SocketAddress(ip, port);
}

struct sockaddr * SocketAddress::RawAddr()
{
  return reinterpret_cast<struct sockaddr *>(&sockaddr_);
}

const struct sockaddr * SocketAddress::RawAddr() const
{
  return reinterpret_cast<const struct sockaddr *>(&sockaddr_);
}

struct sockaddr_in * SocketAddress::RawInetAddr() { return &sockaddr_; }

const struct sockaddr_in * SocketAddress::RawInetAddr() const { return &sockaddr_; }

size_t SocketAddress::Size() const { return sizeof(sockaddr_); }
const std::string SocketAddress::Ip() const { return std::string(ip_); }
uint16_t SocketAddress::Port() const { return port_; }

Socket::~Socket()
{
  if (IsActive())
  {
    Close();
  }
}

int Socket::Map(int flags)
{
  if (IsActive())
  {
    return SetError(ErrorCode::kAlreadyActive);
  }
  socket_fd_ = socket(AF_INET, SOCK_DGRAM, flags);
  if (socket_fd_ < 0)
  {
    SetError(kSocketError);
  }
  return socket_fd_;
}

int Socket::SetSocketOption(int level, int optname, const void * optval, socklen_t optlen)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }

  return setsockopt(socket_fd_, level, optname, optval, optlen);
}

int Socket::SetReuseAddress(int flag)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  return setsockopt(
    socket_fd_, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&flag), sizeof(flag));
}

int Socket::SetReceiveBufferSize(int size)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  return setsockopt(socket_fd_, SOL_SOCKET, SO_RCVBUF, &size, (socklen_t)sizeof(int));
}

int Socket::SetSendTimeout(const std::chrono::microseconds & timeout)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  struct timeval time;
  time.tv_sec = timeout.count() / kMicroToSec;
  time.tv_usec = timeout.count() % kMicroToSec;
  return setsockopt(
    socket_fd_, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<char *>(&time), sizeof(struct timeval));
}

int Socket::SetReceiveTimeout(const std::chrono::microseconds & timeout)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  struct timeval time;
  time.tv_sec = timeout.count() / kMicroToSec;
  time.tv_usec = timeout.count() % kMicroToSec;
  return setsockopt(
    socket_fd_, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char *>(&time), sizeof(struct timeval));
}

int Socket::JoinMulticastGroup(
  const SocketAddress & multicast_address, const SocketAddress & interface_address)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  struct ip_mreq mreq;
  mreq.imr_multiaddr.s_addr = multicast_address.RawInetAddr()->sin_addr.s_addr;
  mreq.imr_interface.s_addr = interface_address.RawInetAddr()->sin_addr.s_addr;
  return setsockopt(
    socket_fd_, IPPROTO_IP, IP_ADD_MEMBERSHIP, reinterpret_cast<char *>(&mreq), sizeof(mreq));
}

int Socket::LeaveMulticastGroup(
  const SocketAddress & multicast_address, const SocketAddress & interface_address)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  struct ip_mreq mreq;
  mreq.imr_multiaddr.s_addr = multicast_address.RawInetAddr()->sin_addr.s_addr;
  mreq.imr_interface.s_addr = interface_address.RawInetAddr()->sin_addr.s_addr;
  return setsockopt(
    socket_fd_, IPPROTO_IP, IP_DROP_MEMBERSHIP, reinterpret_cast<char *>(&mreq), sizeof(mreq));
}

int Socket::SetTTLForMulticast(int ttl)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  return setsockopt(socket_fd_, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
}

int Socket::SetTTLForUnicast(int ttl)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  return setsockopt(socket_fd_, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
}

int Socket::Bind(const SocketAddress & local_address)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  auto result = ::bind(socket_fd_, local_address.RawAddr(), local_address.Size());
  if (result < 0)
  {
    return SetError(ErrorCode::kSocketError);
  }
  local_address_ = local_address;
  SetError(ErrorCode::kSuccess);
  return result;
}

int Socket::Connect(const SocketAddress & remote_address)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  auto result = ::connect(socket_fd_, remote_address.RawAddr(), remote_address.Size());
  if (result < 0)
  {
    return SetError(ErrorCode::kSocketError);
  }
  remote_address_ = remote_address;
  SetError(ErrorCode::kSuccess);
  return result;
}

int Socket::Select(std::chrono::microseconds timeout, bool read)
{
  fd_set fds;
  struct timeval tv;
  tv.tv_sec = timeout.count() / kMicroToSec;
  tv.tv_usec = (timeout.count() % kMicroToSec);
  FD_ZERO(&fds);
  FD_SET(socket_fd_, &fds);
  fd_set * rset = nullptr;
  fd_set * wset = nullptr;
  if (read)
  {
    rset = &fds;
  }
  else
  {
    wset = &fds;
  }

  return select(socket_fd_ + 1, rset, wset, nullptr, &tv);
}

int Socket::Send(const unsigned char * raw_data, int raw_data_size, int flags)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  if (remote_address_ == std::nullopt)
  {
    return SetError(ErrorCode::kNotConnected);
  }
  int sent_bytes = ::send(socket_fd_, raw_data, raw_data_size, flags);
  if (sent_bytes < 0)
  {
    return SetError(ErrorCode::kSocketError);
  }
  SetError(ErrorCode::kSuccess);
  return sent_bytes;
}

int Socket::SendTo(
  const SocketAddress & remote_address, const unsigned char * raw_data, int raw_data_size,
  int flags)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  SocketAddress * nonconst_remote_address = const_cast<SocketAddress *>(&remote_address);

  int sent_bytes = sendto(
    socket_fd_, raw_data, raw_data_size, flags, nonconst_remote_address->RawAddr(),
    remote_address.Size());
  if (sent_bytes < 0)
  {
    return SetError(ErrorCode::kSocketError);
  }
  SetError(ErrorCode::kSuccess);
  return sent_bytes;
}

int Socket::Receive(unsigned char * buffer, int buffer_size, int flags)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }

  if (IsDGRAM() && local_address_ == std::nullopt)
  {
    return SetError(ErrorCode::kNotBound);
  }
  int received_bytes = recv(socket_fd_, buffer, buffer_size - 1, flags);
  if (received_bytes < 0)
  {
    return SetError(ErrorCode::kSocketError);
  }

  buffer[received_bytes] = '\0';  // Buffer is reused, null terminate for safety
  SetError(ErrorCode::kSuccess);
  return received_bytes;
}

int Socket::ReceiveOrTimeout(
  const std::chrono::microseconds & timeout, unsigned char * buffer, int buffer_size, int flags)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }

  // blocking mode...
  if (timeout.count() < 0)
  {
    if (timeout == std::chrono::microseconds(Socket::kBlockingTimeout))
    {
      return Receive(buffer, buffer_size, flags);
    }
    else
    {
      return SetError(ErrorCode::kError);
    }
  }

  int retval = Select(timeout);
  if (retval == 0)
  {
    return SetError(ErrorCode::kTimeout);
  }
  else if (retval < 0)
  {
    return SetError(ErrorCode::kError);  // some error
  }
  else
  {
    return Receive(buffer, buffer_size, MSG_DONTWAIT | flags);
  }
}

int Socket::ReceiveFrom(
  SocketAddress & incoming_remote_address, unsigned char * buffer, int buffer_size, int flags)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  struct sockaddr_in recv_addr;
  socklen_t addr_len = sizeof(struct sockaddr_in);
  memset(&recv_addr, 0, sizeof(recv_addr));
  int received_bytes =
    recvfrom(socket_fd_, buffer, buffer_size - 1, flags, (struct sockaddr *)&recv_addr, &addr_len);
  incoming_remote_address = SocketAddress(&recv_addr);
  if (received_bytes < 0)
  {
    return (ErrorCode::kSocketError);
  }

  buffer[received_bytes] = '\0';  // Buffer is reused, null terminate for safety
  SetError(ErrorCode::kSuccess);
  return received_bytes;
}

int Socket::ReceiveFromOrTimeout(
  const std::chrono::microseconds & timeout, SocketAddress & incoming_remote_address,
  unsigned char * buffer, int buffer_size, int flags)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }
  int retval = Select(timeout);
  if (retval == 0)
  {
    return SetError(ErrorCode::kTimeout);
  }
  else if (retval < 0)
  {
    return SetError(ErrorCode::kError);  // some  select error
  }
  else
  {
    return ReceiveFrom(incoming_remote_address, buffer, buffer_size, MSG_DONTWAIT | flags);
  }
}

int Socket::ReceiveAllWithTimeout(
  const std::chrono::microseconds & timeout, unsigned char * buffer, int buffer_size, int flags)
{
  if (!IsActive())
  {
    return SetError(ErrorCode::kNotActive);
  }

  if (IsDGRAM() && local_address_ == std::nullopt)
  {
    return SetError(ErrorCode::kNotBound);
  }

  int select_ret = 0;
  int recvd_bytes = 0;
  // Receive all messages in buffer
  do
  {
    select_ret = Select(timeout);
    // Timeout - don't recv anymore
    if (select_ret <= 0)
    {
      break;
    }
    recvd_bytes = recv(socket_fd_, buffer, buffer_size - 1, MSG_DONTWAIT | flags);
    if (recvd_bytes >= 0)
    {
      buffer[recvd_bytes] = '\0';  // Buffer is reused, null terminate for safety
    }
  } while (recvd_bytes > 0);

  // some  select error
  if (select_ret < 0)
  {
    return SetError(ErrorCode::kError);
  }

  // Recv error
  if (recvd_bytes < 0)
  {
    return SetError(ErrorCode::kSocketError);
  }

  // Timeout, no messages left in buffer
  // OR connection closed by peer
  return SetError(ErrorCode::kSuccess);
}

int Socket::Close()
{
  if (IsActive())
  {
    ::close(socket_fd_);
    socket_fd_ = -1;
    return SetError(ErrorCode::kSuccess);
  }
  return SetError(ErrorCode::kNotActive);
}

int Socket::Shutdown()
{
  if (IsActive())
  {
    ::shutdown(socket_fd_, SHUT_RDWR);
    return SetError(ErrorCode::kSuccess);
  }
  return SetError(ErrorCode::kNotActive);
}

int Socket::GetSocketFd() const { return socket_fd_; }
bool Socket::IsActive() const { return socket_fd_ >= 0; }

std::string Socket::GetLastErrorText() const { return std::strerror(last_errno_); }

std::pair<Socket::ErrorCode, int> Socket::GetLastSocketError() const
{
  return {last_error_state_, last_errno_};
}

bool Socket::IsReadable() const { throw "NOT IMPLEMENTED"; }

bool Socket::IsDGRAM() const
{
  int type;
  socklen_t type_len = sizeof(type);
  getsockopt(socket_fd_, SOL_SOCKET, SO_TYPE, &type, &type_len);
  return type == SOCK_DGRAM;
}

int Socket::SetError(ErrorCode code, int)
{
  last_error_state_ = code;
  if (code == ErrorCode::kSocketError)
  {
    last_errno_ = errno;
  }
  else
  {
    last_errno_ = 0;
  }
  return code;
}

}  // namespace os::core::udp::communication
