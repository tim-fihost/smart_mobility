#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/action/move.hpp>

using namespace std::placeholders;

class RobotMovementClient : public rclcpp::Node {
public:
    RobotMovementClient() : Node("robot_movement_client") {
        client_ = rclcpp_action::create_client<example_interfaces::action::MoveAction>(
            this,
            "move_action"
        );
    }

    void send_goal(float distance);

private:
    rclcpp_action::Client<example_interfaces::action::MoveAction>::SharedPtr client_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotMovementClient>();
    node->send_goal(1.5);  // Move the robot 1.5 meters forward
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
