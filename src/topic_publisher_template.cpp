#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>

namespace ros_template_programs {
    class TopicPublisher {
        private:
            ros::NodeHandle nh_;
            ros::NodeHandle pnh_;
            ros::Publisher pub_msg_;
            ros::Timer timer_;
            std_msgs::String msg_;
            void callbackTimer(const ros::TimerEvent&);

        public:
            TopicPublisher( );
    };
}

void ros_template_programs::TopicPublisher::callbackTimer(const ros::TimerEvent&) {
    pub_msg_.publish(msg_);
    ROS_INFO("\n[%s] Message Published\n%s\n", ros::this_node::getName().c_str(), msg_.data.c_str() );
    return;
}

ros_template_programs::TopicPublisher::TopicPublisher( ) : nh_(), pnh_("~") {
    msg_.data = pnh_.param<std::string>("message", "Hello, World!");
    pub_msg_ = nh_.advertise<std_msgs::String>("topic", 1);
    timer_ = nh_.createTimer(ros::Duration(0.5), &TopicPublisher::callbackTimer, this);
}

int main(int argc, char *argv[])  {
    ros::init(argc, argv, "topic_publisher_template");
    ros_template_programs::TopicPublisher topic_pub;
    ros::spin();
    return 0;
}