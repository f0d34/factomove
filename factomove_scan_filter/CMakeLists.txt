cmake_minimum_required(VERSION 3.0.2)
project(factomove_scan_filter)


find_package(catkin REQUIRED)

catkin_package()

install(DIRECTORY launch maps param rviz
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
