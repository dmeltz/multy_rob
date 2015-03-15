cmake_minimum_required(VERSION 2.8.3)
project(bobTeam)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  roscpp
  rospy
  std_msgs
  gazebo_msgs
  tf
)

find_package(Boost REQUIRED COMPONENTS system thread filesystem)

find_package(TinyXML REQUIRED)



## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(Gazebo REQUIRED)

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()



###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES srvss_bobcat
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
   DEPENDS
     TinyXML
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS} ${TinyXML_INCLUDE_DIRS}
)



add_library(TeamMission src/TeamMission.cpp)
target_link_libraries(TeamMission 
  ${catkin_LIBRARIES}
  ${TinyXML_LIBRARIES}
)


add_executable(MissionController src/MissionController.cpp)
target_link_libraries(MissionController
  ${catkin_LIBRARIES}  
  ${Boost_LIBRARIES} 
  TeamMission
)

