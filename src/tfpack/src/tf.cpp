#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>
#include <sensor_msgs/LaserScan.h>

std::string turtle_name;



void poseCallback(const turtlesim::PoseConstPtr& msg){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg->x, msg->y, 0.0) );
  tf::Quaternion q;
  q.setRPY(0, 0, msg->theta);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", turtle_name));
  std::cout<<"finish the transfor!!!!"<<std::endl;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_broadcaster");
  //if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  //turtle_name = argv[1];
  turtle_name = "turtle1";

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback);

  ros::Rate loop_rate(1000);
  int n{0};
  while(ros::ok()){

    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin( tf::Vector3(n/1e5, n/1e5, 0.0) );
    tf::Quaternion q;
    q.setRPY(0, 0, n/360);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", turtle_name));

    static tf::TransformBroadcaster br1;
    tf::Transform transform1;
    transform1.setOrigin( tf::Vector3(-n/1e5, -n/1e5, 0.0) );
    tf::Quaternion q1;
    q.setRPY(0, 0, -n/360);
    transform1.setRotation(q);
    br1.sendTransform(tf::StampedTransform(transform1, ros::Time::now(), "map", "turtle2"));

    ros::Publisher pub = node.advertise<sensor_msgs::LaserScan>("scan", 10);
    sensor_msgs::LaserScan scanmsg;
    scanmsg.header.frame_id = "map";
    scanmsg.header.stamp = ros::Time::now();
    scanmsg.angle_min =0;
    scanmsg.angle_max = 6.28;
    scanmsg.angle_increment = 0.017;
    scanmsg.time_increment =0.000557;
    scanmsg.scan_time =0.2 ;
    scanmsg.range_min = 0.01;
    scanmsg.range_max = 5.0;
    scanmsg.ranges.resize(360);
    scanmsg.intensities.resize(360);
    for(int i = 0; i<360;i++){
	scanmsg.ranges[i] = n/1e5;
    }
    pub.publish(scanmsg);

   ros::spinOnce();
   loop_rate.sleep();
   n++;
   }

  return 0;
};
