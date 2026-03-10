#include "apollo_cyber.h"

namespace apollo {
namespace cyber {
std::unique_ptr<Node> CreateNode(const std::string& node_name,
                                 const std::string& name_space) {
  return std::unique_ptr<Node>(new Node(node_name, name_space));
}

}  // namespace cyber
}  // namespace apollo