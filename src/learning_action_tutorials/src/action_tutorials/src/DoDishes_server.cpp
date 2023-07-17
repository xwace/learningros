#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include "action_tutorials/DoDishesAction.h"
#include <boost/algorithm/string.hpp>

typedef actionlib::SimpleActionServer<action_tutorials::DoDishesAction> Server;

// 收到action的goal后调用的回调函数
void execute(const action_tutorials::DoDishesGoalConstPtr& goal, Server* as)
{
    ros::Rate r(1);
    action_tutorials::DoDishesFeedback feedback;

    ROS_INFO("Dishwasher %d is working.", goal->dishwasher_id);

    // 假设洗盘子的进度，并且按照1hz的频率发布进度feedback
    for(int i=1; i<=10; i++)
    {
        feedback.percent_complete = i * 10;
        as->publishFeedback(feedback);
        r.sleep();
    }

	// 当action完成后，向客户端返回结果
    ROS_INFO("Dishwasher %d finish working.", goal->dishwasher_id);
    as->setSucceeded();
}

class RoomSegmentationServer {
    ros::NodeHandle nh;
    Server server;

    //!!!成员变量在使用初始化列表初始化时，与构造函数中初始化成员列表的顺序无关，只与定义成员变量的顺序有关!!!
    //Server server; Error as in the server(nh, name...) nh is empty!!
    ///ros::NodeHandle nh;

public:
    RoomSegmentationServer(ros::NodeHandle nh_, std::string name) : nh(nh_), server(nh, name, boost::bind(
            &RoomSegmentationServer::callback, this, _1), false) {
        server.start();
    };

    void callback(const action_tutorials::DoDishesGoalConstPtr &goal) {
        ros::Rate r(1);
        action_tutorials::DoDishesFeedback feedback;

        ROS_INFO("Dishwasher %d is working.", goal->dishwasher_id);

        // 假设洗盘子的进度，并且按照1hz的频率发布进度feedback
        for (int i = 1; i <= 10; i++) {
            feedback.percent_complete = i * 10;
            server.publishFeedback(feedback);
            r.sleep();
        }

        // 当action完成后，向客户端返回结果
        ROS_INFO("Dishwasher %d finish working.", goal->dishwasher_id);
        server.setSucceeded();
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "do_dishes_server");
    ros::NodeHandle nh;

    RoomSegmentationServer server(nh,"do_dishes");

    // 定义一个服务器
    //Server server(nh, "do_dishes", boost::bind(&execute, _1, &server), false);

	// 服务器开始运行
    //server.start();

    ros::spin();

    return 0;
}
