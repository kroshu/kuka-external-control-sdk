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

#ifndef OS_CORE_COMM_UDP_SOCKET_H
#define OS_CORE_COMM_UDP_SOCKET_H

#include <netinet/in.h>

#include <chrono>
#include <optional>
#include <string>

namespace os::core::udp::communication {

class SocketAddress {
 public:
  SocketAddress();
  SocketAddress(const std::string &ip, int port);
  SocketAddress(const std::string &ip);
  SocketAddress(int port);
  SocketAddress(const struct sockaddr_in *raw_address);

  static std::optional<SocketAddress> SafeConstruct(const std::string &ip, int port = 0);

 public:
  struct sockaddr *RawAddr();
  const struct sockaddr *RawAddr() const;
  struct sockaddr_in *RawInetAddr();
  const struct sockaddr_in *RawInetAddr() const;
  size_t Size() const;
  const std::string Ip() const;
  uint16_t Port() const;

 public:
  static const std::string kAnyAddress;

 protected:
  struct sockaddr_in sockaddr_;
  char ip_[INET_ADDRSTRLEN];
  uint16_t port_;
};

class Socket {
 public:
  enum ErrorCode {
    kSuccess = 0,
    kSocketError = -1,
    kNotActive = -2,
    kAlreadyActive = -2,
    kNotBound = -3,
    kNotConnected = -4,
    kTimeout = -5,
    kError = -6,
    kClosed = -7,
    kInvalidMessage = -8,
    kSecureLayerError = -100,
  };

  static constexpr int kBlockingTimeout = -1;

 public:
  virtual ~Socket();

 public:
  /* creates a new socket with the given `flags`, and returns the underlaying
   * socket identifer */
  virtual int Map(int flags = 0);

  /*sets generic socket option*/
  int SetSocketOption(int level, int optname, const void *optval, socklen_t optlen);

  /* sets a given `timeout` (in ms) for *send* operation to wait if there was
   * no packet send */
  int SetSendTimeout(const std::chrono::microseconds &timeout);

  /* sets a given `timeout` (in ms) for *receive* operation to wait if there
   * was no packet receive*/
  int SetReceiveTimeout(const std::chrono::microseconds &timeout);

  /* join a multicast group with the given `multicast_address` to able receive
   * the packets*/
  int JoinMulticastGroup(const SocketAddress &multicast_address,
                         const SocketAddress &interface_address = SocketAddress());

  /* leave a multicast group with the given `multicast_address`*/
  int LeaveMulticastGroup(const SocketAddress &multicast_address,
                          const SocketAddress &interface_address = SocketAddress());

  /* sets the given `ttl`for multicast sending (IP packet property) */
  int SetTTLForMulticast(int ttl = 1);

  /* sets the given `ttl`for unicast sending (IP packet property) */
  int SetTTLForUnicast(int ttl = 1);

  /* sets the to socket to be able to reuse address */
  int SetReuseAddress(int flag = 1);

  /* sets the to sockets rx buffer size */
  int SetReceiveBufferSize(int size);

  /* binds the socket to the given `local_address` */
  virtual int Bind(const SocketAddress &local_address);

  /* connects the socket to the given `remote_address` */
  virtual int Connect(const SocketAddress &remote_address);

  /* do handshake - TODO: maybe enough on securesocket*/
  virtual int DoHandshake() { return ErrorCode::kSuccess; }

  /* wait for event(read or write) on the socket until given time*/
  int Select(std::chrono::microseconds timeout, bool read = true);

  /* sends the given `raw_data` to the previously connected remote address */
  virtual int Send(const unsigned char *raw_data, int raw_data_size, int flags = 0);

  /* sends the given `raw_data` to the given `remote_address` */
  virtual int SendTo(const SocketAddress &remote_address, const unsigned char *raw_data,
                     int raw_data_size, int flags = 0);

  /* receives a packet on the previously bind address into the given `buffer`
   */
  virtual int Receive(unsigned char *buffer, int buffer_size, int flags = 0);

  /* receives a packet on the previously bind address into the given `buffer`
   * or timeout after the given `timeout` */
  virtual int ReceiveOrTimeout(const std::chrono::microseconds &timeout, unsigned char *buffer,
                               int buffer_size, int flags = 0);

  /* receives a packet on the previously bind address into the given `buffer`,
   * extracting the remote address to `incoming_remote_address` */
  virtual int ReceiveFrom(SocketAddress &incoming_remote_address, unsigned char *buffer,
                          int buffer_size, int flags = 0);

  /* receives a packet on the previously bind address into the given `buffer`,
   * extracting the remote address to `incoming_remote_address` or timeout
   * after the given `timeout` */
  virtual int ReceiveFromOrTimeout(const std::chrono::microseconds &timeout,
                                   SocketAddress &incoming_remote_address, unsigned char *buffer,
                                   int buffer_size, int flags = 0);

  /* receives all packets present on the previously bound address, puts last into the given `buffer` */
  virtual int ReceiveAllWithTimeout(const std::chrono::microseconds &timeout, unsigned char *buffer, int buffer_size, int flags = 0);

  /* freeing up the socket */
  virtual int Close();

  /* shutting down both incoming and outgoing communication of the socket */
  virtual int Shutdown();

 public:
  int GetSocketFd() const;
  bool IsActive() const;
  virtual std::string GetLastErrorText() const;
  bool IsReadable() const;
  std::pair<ErrorCode, int> GetLastSocketError() const;
  bool IsDGRAM() const;

 protected:
  virtual int SetError(ErrorCode code, int err_no = 0);

 protected:
  int socket_fd_ = -1;
  std::optional<SocketAddress> local_address_;
  std::optional<SocketAddress> remote_address_;

  ErrorCode last_error_state_ = ErrorCode::kSuccess;
  int last_errno_ = 0;

  static constexpr uint32_t kMicroToSec = 1000000;
};

}  // namespace os::core::udp::communication

#endif  // OS_CORE_COMM_UDP_SOCKET_H
