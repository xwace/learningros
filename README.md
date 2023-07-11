# learningros
ros入门简单例子：1.包括发布订阅主题，显示点的位姿态（位置＋方向）2.模板实现subscribe(&amp;cb,this);理解回调cb(T*ags)如何获取话题给的值

所有ros目录架构：
catkin_ws:生成src目录，catkin_make,生成以下:
src devel build

source devel/setup.bash
进入src:catkin_create_pkg package roscpp rospy dynamic_reconfigure
package功能包:include,src,rviz,launch,cfg
