cmake_minimum_required(VERSION 2.8.3)
project(gazebo_sick_gpu)


find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  roscpp
  std_msgs
  tf
)

find_package(Boost REQUIRED COMPONENTS system)
find_package(tf REQUIRED)
find_package(gazebo REQUIRED)


link_directories(${GAZEBO_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS})

catkin_package(
  DEPENDS 
    roscpp 
    tf
    gazebo_ros 
)
 
add_library(sick_gpu src/sick.cpp)
target_link_libraries(sick_gpu ${GAZEBO_libraries} ${catkin_LIBRARIES})


