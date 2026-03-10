#include <iostream>

#include "Janus.h"
#include "cyber/state.h"
#include "modules/common_msgs/control_msgs/control_cmd.pb.h"

using namespace apollo::control;
using namespace apollo::cyber::service_discovery;

int main(int argc, char* argv[]) {
  Janus janus;
  auto init_success = janus.Init();
  if (!init_success) {
    return -1;
  }

  auto reader = janus.apollo_cyber_->GetNode()->CreateReader<ControlCommand>(
      "/apollo/control", [](const std::shared_ptr<ControlCommand>& msg) {
        std::string msg_debug_str = msg->ShortDebugString();
        std::cout << "Received message: {" << msg_debug_str << "}" << std::endl;
      });
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }
  return 0;
}