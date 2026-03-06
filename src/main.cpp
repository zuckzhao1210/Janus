#include "Janus.h"
#include "modules/common_msgs/control_msgs/control_cmd.pb.h"

using namespace apollo::control;

int main(int argc, char* argv[]) {
  Janus janus;
  auto init_success = janus.Init();
  auto writer = janus.apollo_cyber_->GetNode()->CreateWriter<ControlCommand>(
      "/apollo/control");

  while (true) {
    ControlCommand control_cmd;
    control_cmd.set_acceleration(10.0);
    writer->Write(control_cmd);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return 0;
}