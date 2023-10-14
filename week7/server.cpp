#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/action/move.hpp>

using namespace std::placeholders;

class RobotMovementServer : public rclcpp::Node {
public:
    RobotMovementServer() : Node("robot_movement_server") {
        server_ = rclcpp_action::create_server<example_interfaces::action::MoveAction>(
            this,
            "move_action",
            std::bind(&RobotMovementServer::handle_goal, this, _1, _2),
            std::bind(&RobotMovementServer::handle_cancel, this, _1),
            std::bind(&RobotMovementServer::handle_accepted, this, _1)
        );
    }

private:
    rclcpp_action::Server<example_interfaces::action::MoveAction>::SharedPtr server_;

    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID & uuid,
        std::shared_ptr<const example_interfaces::action::MoveAction::Goal> goal);

    rclcpp_action::CancelResponse handle_cancel(
        const std::shared_ptr<rclcpp_action::ServerGoalHandle<example_interfaces::action::MoveAction>> goal_handle);

    void handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<example_interfaces::action::MoveAction>> goal_handle);
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotMovementServer>());
    rclcpp::shutdown();
    return 0;
}
