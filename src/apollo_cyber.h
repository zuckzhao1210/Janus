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

using apollo::cyber::proto::RoleAttributes;
using namespace apollo::cyber;

namespace janus {

class ApolloCyber {
 public:
  ~ApolloCyber() = default;

  static ApolloCyber& Instance() {
    static ApolloCyber instance_("janus");
    return instance_;
  }

  template <typename MessageT>
  auto CreateWriter(const std::string& channel_name)
      -> std::shared_ptr<Writer<MessageT>>;

 private:
  ApolloCyber(const std::string& node_name) : node_name_(node_name) {
    node_ = apollo::cyber::CreateNode(node_name_);
  };

 private:
  std::unique_ptr<NodeChannelImpl> node_channel_impl_ = nullptr;
  std::string node_name_;
  std::unique_ptr<Node> node_ = nullptr;
};

template <typename MessageT>
auto ApolloCyber::CreateWriter(const std::string& channel_name)
    -> std::shared_ptr<Writer<MessageT>> {
  return node_->CreateWriter<MessageT>(channel_name);
}
}  // namespace janus
#endif  // APOLLO_CYBER_H