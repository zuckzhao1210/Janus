#include "Janus.h"
#include "modules/common_msgs/control_msgs/control_cmd.pb.h"

using namespace apollo::control;

int main(int argc, char * argv[])
{
    Janus janus;
    auto init_success = janus.Init();
    auto writer = janus.apollo_cyber_->CreateWriter<ControlCommand>("/apollo/control");
    return 0;
}