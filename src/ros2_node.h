#ifndef ROS2_NODE_H
#define ROS2_NODE_H

#include <string>

namespace janus
{
class Ros2Node
{
  public:
    ~Ros2Node() = default;
    static Ros2Node& Instance() {
        static Ros2Node instance_("janus");
        return instance_;
    }

  private:
    Ros2Node(const std::string& node_name): node_name_(node_name) {};
    std::string node_name_;
};
} // namespace janus

#endif // ROS2_NODE_H