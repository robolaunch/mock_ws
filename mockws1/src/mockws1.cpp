#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

// This is only true if the executable is mockws1
bool took_message = true;

// Get any message?
bool took_any_message = false;


// A subscriber to topic3 that will take the message, and if it is "Hello World", makes the took_message variable true
void callback(const std_msgs::msg::String::SharedPtr msg)
{
    // if msg-> data starts with "Hello World"
    if (msg->data.substr(0, 11) == "Hello World") {
        took_message = true;
        took_any_message = true;
    }
}


int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    // start a node!
    //rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("mockws1");
    auto node = std::make_shared<rclcpp::Node>("temp1");
    auto publisher = node->create_publisher<std_msgs::msg::String>("x1", 10);
    rclcpp::WallRate loop_rate(1);
    // subscribe to topic3
    auto subscription = node->create_subscription<std_msgs::msg::String>("x3", 10, callback);
    int i = 0;
    while (rclcpp::ok()) {
        if(took_message) {
            RCLCPP_INFO(node->get_logger(), "I took the message!");
            auto msg = std_msgs::msg::String();
            msg.data = "Hello World" + std::to_string(i);
            publisher->publish(msg);
            rclcpp::spin_some(node);
            loop_rate.sleep();
            took_message = false;
            i++;
        }
        else if(!took_any_message) {
            RCLCPP_INFO(node->get_logger(), "I didn't take any message!");
            auto msg = std_msgs::msg::String();
            msg.data = "Hello World" + std::to_string(i);
            publisher->publish(msg);
            rclcpp::spin_some(node);
            loop_rate.sleep();
        }
        else{
            rclcpp::spin_some(node);
            loop_rate.sleep();
        }
    }

    return 0;
}
