cmake_minimum_required (VERSION 2.6)
project (robot-navigation)

add_executable(robot-navigation main.cpp)
target_link_libraries(robot-navigation GL)
target_link_libraries(robot-navigation GLU)
target_link_libraries(robot-navigation glut)