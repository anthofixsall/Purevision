cmake_minimum_required(VERSION 3.0.2)
project(picar_vision)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)



## Declare ROS messages and services
#add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})


add_executable(listener_c src/listener_c.cpp)
target_link_libraries(listener_c ${catkin_LIBRARIES})
add_dependencies(listener_c beginner_tutorials_generate_messages_cpp)

add_executable(talker_c 
src/talker_c.cpp
src/panneau_video.cpp
src/follow_line.cpp
src/comptage.cpp
)

target_link_libraries(talker_c ${catkin_LIBRARIES} ${OpenCV_LIBS}  pthread)
add_dependencies(talker_c picar_vision_generate_messages_cpp)





# %EndTag(FULLTEXT)%
