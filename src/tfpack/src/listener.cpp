#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>
#include <sensor_msgs/LaserScan.h>

void poseCallback(const sensor_msgs::LaserScan::ConstPtr& scanmsg){
    ROS_INFO("I heard: [%f]", scanmsg->ranges[0]);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "my_listener");
    ros::NodeHandle n;

    std::cout<<"listerning!!!!"<<std::endl;
    ros::Subscriber sub = n.subscribe("scan", 1, poseCallback);
    ros::spin();

    return 0;
}
