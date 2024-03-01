// This material is the exclusive property of KUKA Deutschland GmbH.
// Except as expressly permitted by separate agreement, this material may only
// be used by members of the development department of KUKA Deutschland GmbH for
// internal development purposes of KUKA Deutschland GmbH.
//
// Copyright (C)
// KUKA Deutschland GmbH, Germany. All Rights Reserved.

#ifndef OS_CORE_COMM_DISSECTOR_H
#define OS_CORE_COMM_DISSECTOR_H

#include <functional>
#include <memory>
#include <vector>

#include "socket.h"

namespace os::core::udp::communication {

/*
  *Dissector* handles message dissection for packets.
  It allows to receive messages/PDUs instead of just whole packets - with similar interface to
  socket.
  -
  The default behaviour is same as normal socket receive: just returning the whole packet .
  For custom dissector (behaviour to determine message is valid and if yes what length it has) the
  *Dissect()* fn must be implemented.
*/
class Dissector {
 public:
  using raw_message_t = std::pair<char*, size_t>;

 public:
  Dissector(std::shared_ptr<Socket> socket, size_t buffer_size);
  virtual ~Dissector() = default;

 public:  //<socket operations>
  virtual Socket::ErrorCode Receive(raw_message_t& message, int flags = 0);
  virtual Socket::ErrorCode ReceiveOrTimeout(const std::chrono::microseconds& timeout,
                                             raw_message_t& message, int flags = 0);

 protected:
  virtual int Dissect(char* /*cursor_ptr*/, size_t available_bytes) { return available_bytes; }

 public:  //<properties>
  std::string GetLastErrorText() const { return socket_->GetLastErrorText(); };
  std::pair<Socket::ErrorCode, int> GetLastSocketError() const {
    return socket_->GetLastSocketError();
  };
  const char* Cursor() const { return buffer_.data() + data_cursor_; }
  char* Cursor() { return buffer_.data() + data_cursor_; }
  std::shared_ptr<Socket>& socket() { return socket_; }
  const std::shared_ptr<Socket>& socket() const { return socket_; }

 protected:
  std::shared_ptr<Socket> socket_;

 protected:
  std::vector<char> buffer_;
  int maximum_buffer_size_{0};

 protected:
  int data_cursor_{0};
  int data_length_{0};
};

/*
 *DynamicDissector* is special version of *Dissector* to enable dynamic dissector behaviour to avoid
 *creating new derived classes for smaller logics.
 */
class DynamicDissector : public Dissector {
 public:
  using dissector_fn_t = int(char* data_ptr, size_t data_length);

 public:
  DynamicDissector(std::shared_ptr<Socket> socket, size_t buffer_size,
                   std::function<dissector_fn_t> dissector_fn);

 protected:  //<Dissector>
  virtual int Dissect(char* cursor_ptr, size_t available_bytes) {
    return message_dissector_fn_(cursor_ptr, available_bytes);
  }

 public:
  std::function<dissector_fn_t> message_dissector_fn_;
};

}  // namespace os::core::udp::communication

#endif  // OS_CORE_COMM_DISSECTOR_H
