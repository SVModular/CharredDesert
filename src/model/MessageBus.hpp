#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <cstdint>

template <typename T>
class Message {
public:
  std::string id;
  T value;
};

template <typename T>
class MessageBus {
public:
  MessageBus<T>() { }

  void send(std::string id, Message<T> *message) {
    std::lock_guard<std::mutex> lock(memberMutex);

    if (members[id]) {
      if (memberData[id]) {
        Message<T> *old = memberData[id];
        memberData.erase(id);

        delete old;
      }

      memberData[id] = message;
    } else {
      fprintf(stderr, "Unknown member sent data to the MessageBus: %s\n", id.c_str());
    }
  }

  std::vector<T> *currentValues() {
    std::vector<T> *data = new std::vector<T>();

    std::lock_guard<std::mutex> lock(memberMutex);

    for (const auto &e : memberData) {
      Message<T> *message = (Message<T> *) e.second;
      data->push_back(message->value);
    }

    return data;
  }

  std::string registerMember() {
    std::lock_guard<std::mutex> lock(memberMutex);

    std::string id = std::to_string(busId);
    busId++;

    members[id] = true;

    return id;
  }

  void deregisterMember(std::string id) {
    std::lock_guard<std::mutex> lock(memberMutex);

    if (members[id]) {
      if (memberData[id]) {
        Message<T> *old = memberData[id];
        delete old;
        memberData.erase(id);
      }

      members.erase(id);
    } else {
      fprintf(stderr, "Unknown member tried to deregister: %s\n", id.c_str());
    }
  }

private:
  std::mutex memberMutex;
  std::unordered_map<std::string, Message<T> *> memberData;
  std::unordered_map<std::string, bool> members;
  // this would be better handled with a uuid
  uint64_t busId = 0;
};
