#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "std_msgs/Bool.h"

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<std_msgs::Bool>("markerLocation", 1);
  std_msgs::Bool start, end;
  start.data = false;
  end.data = true;
  
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup;
  move_base_msgs::MoveBaseGoal dropoff;

  // set up the frame parameters
  
  pickup.target_pose.header.frame_id = "map";
  pickup.target_pose.header.stamp = ros::Time::now();
  
  dropoff.target_pose.header.frame_id = "map";
  dropoff.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  
  pickup.target_pose.pose.position.x = -4.5;
  pickup.target_pose.pose.position.y = -1;
  pickup.target_pose.pose.orientation.w = 1.0;
  
  dropoff.target_pose.pose.position.x = 5.6;
  dropoff.target_pose.pose.position.y = 2.6;
  dropoff.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup goal");
  ac.sendGoal(pickup);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved to the pickup location");
    pub.publish(start);
   
  }
  else
    ROS_INFO("The base failed to move to the pickup location for some reason");

  ros::Duration(5.0).sleep();
  //Sending dropoff goal
  ROS_INFO("Sending dropoff goal");
  ac.sendGoal(dropoff);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base moved to the dropoff location");
    pub.publish(end);
  }
  else
    ROS_INFO("The base failed to move to the dropoff location for some reason");
  return 0;
}