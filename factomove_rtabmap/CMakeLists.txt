cmake_minimum_required(VERSION 3.0.2)
project(factomove_rtabmap)
find_package(catkin REQUIRED COMPONENTS
    rtabmap_ros
)


link_directories(${GAZEBO_LIBRARY_DIRS})

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
)
