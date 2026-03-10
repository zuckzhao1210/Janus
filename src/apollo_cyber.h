#ifndef APOLLO_CYBER_H
#define APOLLO_CYBER_H

#include <string>

#include "cyber/common/global_data.h"
#include "cyber/node/writer.h"
#include "cyber/proto/role_attributes.pb.h"
#include "cyber/transport/qos/qos_profile_conf.h"
#include "cyber/transport/transport.h"
#include "cyber/node/node_channel_impl.h"
#include "cyber/node/node.h"
#include "cyber/state.h"

using apollo::cyber::proto::RoleAttributes;
using namespace apollo::cyber;

namespace apollo {
namespace cyber {
std::unique_ptr<Node> CreateNode(const std::string& node_name,
                                 const std::string& name_space = "");
}  // namespace cyber
}  // namespace apollo

namespace janus {

class ApolloCyber {
 public:
  ~ApolloCyber() = default;

  static ApolloCyber& Instance() {
    static ApolloCyber instance_("janus");
    return instance_;
  }

  Node* GetNode() { return node_ptr_.get(); }

 private:
  ApolloCyber(const std::string& node_name) : node_name_(node_name) {
    node_ptr_ = apollo::cyber::CreateNode(node_name_);
    SetState(STATE_INITIALIZED);
  };

 private:
  std::unique_ptr<NodeChannelImpl> node_channel_impl_ = nullptr;
  std::string node_name_;
  std::unique_ptr<Node> node_ptr_ = nullptr;
};

}  // namespace janus
#endif  // APOLLO_CYBER_H