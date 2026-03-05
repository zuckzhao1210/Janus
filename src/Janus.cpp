#include "Janus.h"

using namespace janus;

bool Janus::Init() {
    apollo_cyber_ = &ApolloCyber::Instance();
    ros2_node_ = &Ros2Node::Instance();
    return true;
}
