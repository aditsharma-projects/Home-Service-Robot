cmake_minimum_required(VERSION 2.8.3)
project(turtlebot_stdr)

find_package(catkin REQUIRED)

catkin_package()

catkin_add_env_hooks(25.turtlebot-stdr SHELLS sh DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/env-hooks)

install(DIRECTORY launch 
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(DIRECTORY maps 
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(DIRECTORY rviz 
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(DIRECTORY robot
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(
  PROGRAMS
    nodes/tf_connector.py    
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
