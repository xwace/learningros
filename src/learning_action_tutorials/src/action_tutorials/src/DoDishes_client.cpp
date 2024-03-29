#include <actionlib/client/simple_action_client.h>
#include "action_tutorials/DoDishesAction.h"

typedef actionlib::SimpleActionClient<action_tutorials::DoDishesAction> Client;

// 当action完成后会调用次回调函数一次
void doneCb(const actionlib::SimpleClientGoalState& state,
        const action_tutorials::DoDishesResultConstPtr& result)
{
    ROS_INFO("Yay! The dishes are now clean");
    ros::shutdown();
}

// 当action激活后会调用次回调函数一次
void activeCb()
{
    ROS_INFO("Goal just went active");
}

// 收到feedback后调用的回调函数
void feedbackCb(const action_tutorials::DoDishesFeedbackConstPtr& feedback)
{
    ROS_INFO(" percent_complete : %f ", feedback->percent_complete);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "do_dishes_client");

	// 定义一个客户端
    Client client("do_dishes", true);

	// 等待服务器端
    ROS_INFO("Waiting for action server to start.");
    client.waitForServer();
    ROS_INFO("Action server started, sending goal.");

	// 创建一个action的goal
    action_tutorials::DoDishesGoal goal;
    goal.dishwasher_id = 1;

    // 发送action的goal给服务器端，并且设置回调函数
    client.sendGoal(goal,  &doneCb, &activeCb, &feedbackCb);

    //获取服务端的结果
    bool finished_before_timeout = client.waitForResult(ros::Duration(20));//设置等待时间:20s内如果没有结果返回则结束
    if(finished_before_timeout)
    {
	action_tutorials::DoDishesResultConstPtr result = client.getResult();
	std::cout<<"Result: "<<result->total_dishes_cleaned<<std::endl;
    }

    ros::spin();

    return 0;
}
