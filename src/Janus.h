#ifndef JANUS_H
#define JANUS_H

#include "apollo_cyber.h"
// #include "common/logger.h"
#include "ros2_node.h"

using ApolloCyberPtr = janus::ApolloCyber*;
using Ros2NodePtr = janus::Ros2Node*;

class Janus {
 public:
  Janus() = default;
  ~Janus() = default;

  bool Init();

 public:
  ApolloCyberPtr apollo_cyber_;
  Ros2NodePtr ros2_node_;

 private:
};
#endif  // JANUS_H