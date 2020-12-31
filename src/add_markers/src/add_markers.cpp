#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "std_msgs/Bool.h"

visualization_msgs::Marker marker;
bool pickedUp = false;
bool droppedOff = false;
void add_markers_callback(const std_msgs::Bool state){
  if(state.data == false) pickedUp = true;
  else droppedOff = true;
}
int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Rate r(0.1);
  ros::Subscriber sub = n.subscribe("markerLocation", 1, add_markers_callback);
  uint32_t shape = visualization_msgs::Marker::CUBE;
  while(ros::ok()){
    ros::spinOnce();
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    if(!pickedUp || droppedOff)marker.action = visualization_msgs::Marker::ADD;
	else marker.action = visualization_msgs::Marker::DELETE;
    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    if(!pickedUp){
      marker.pose.position.x = -4.5;
      marker.pose.position.y = -1;
      marker.pose.orientation.w = 1.0;
    }
    else{
      marker.pose.position.x = 5.6;
      marker.pose.position.y = 2.6;
      marker.pose.orientation.w = 1.0;
    }
    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    marker_pub.publish(marker);
  	r.sleep();
  }
  //ros::spin();
  //ROS_INFO("Initialized");
  
  
  
}