#!/bin/sh
xterm  -e  " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find map)/world1" &
sleep 5
xterm  -e  " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find map)/map.yaml" &
sleep 5
xterm  -e  " source /home/workspace/catkin_ws/devel/setup.bash; rosrun add_markers add_markers" &
sleep 5
xterm  -e  " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch rvizConfig rviz.launch" &
sleep 5
xterm  -e  " source /home/workspace/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects" 