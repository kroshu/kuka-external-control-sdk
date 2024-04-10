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

#ifndef KUKA_EXTERNAL_CONTROL__IIQKA_ARENA_WRAPPER_H_
#define KUKA_EXTERNAL_CONTROL__IIQKA_ARENA_WRAPPER_H_

#include <google/protobuf/arena.h>

namespace kuka::external::control::iiqka {
template <typename T>
struct ArenaWrapper {
  ArenaWrapper() {
    initial_buffer_ = new char[kBufferSize];

    google::protobuf::ArenaOptions arena_options;
    arena_options.initial_block = initial_buffer_;
    arena_options.initial_block_size = kInitialBlockSize;
    arena_options.max_block_size = 0;
    arena_options.start_block_size = 0;

    arena_ = new google::protobuf::Arena(arena_options);
  }

  ~ArenaWrapper() {
    delete arena_;
    delete[] initial_buffer_;
  }

  T* CreateMessage() { return (message_ = google::protobuf::Arena::CreateMessage<T>(arena_)); }

  bool SerializeExistingMessageToArray(unsigned char* serialized_bytes, std::size_t size) {
    if (!message_->SerializeToArray(serialized_bytes, size)) {
      return false;
    }

    ResetIfNecessary();
    return true;
  }

  bool SerializeToArray(unsigned char* serialized_bytes, std::size_t size) {
    message_ = google::protobuf::Arena::CreateMessage<T>(arena_);
    return SerializeExistingMessageToArray(serialized_bytes, size);
  }

  bool ParseFromArray(const unsigned char* serialized_bytes, std::size_t size) {
    message_ = google::protobuf::Arena::CreateMessage<T>(arena_);

    if (!message_->ParseFromArray(serialized_bytes, size)) {
      return false;
    }

    ResetIfNecessary();
    return true;
  }

  google::protobuf::Arena* Get() { return arena_; }

  T* GetMessage() { return message_; }

 private:
  void ResetIfNecessary() {
    if (arena_->SpaceUsed() > kResetArenaThreshold) {
      arena_->Reset();
    }
  }
  char* initial_buffer_;
  google::protobuf::Arena* arena_;
  T* message_ = nullptr;
  const std::size_t kBufferSize = 8000;
  const std::size_t kInitialBlockSize = kBufferSize;
  const std::size_t kResetArenaThreshold =
      6000;
};

}  // namespace kuka::external::control::iiqka

#endif  // KUKA_EXTERNAL_CONTROL__IIQKA_ARENA_WRAPPER_H_
