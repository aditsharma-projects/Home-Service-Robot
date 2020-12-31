#include <ros/ros.h>
#include "std_msgs/Bool.h"

int main(int argc, char** argv){
  ros::init(argc, argv, "add_marker_helper");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher pub2 = n.advertise<std_msgs::Bool>("markerLocation", 10);
  std_msgs::Bool start, end;
  start.data = false;
  end.data = true;
  ros::Duration(5.0).sleep();
  pub2.publish(start);
  ROS_INFO("Published");
  ros::Duration(5.0).sleep();
  pub2.publish(end);
  ros::Duration(5.0).sleep();
}