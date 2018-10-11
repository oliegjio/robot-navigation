cmake_minimum_required (VERSION 2.6)
project (robot-navigation)

add_executable(robot-navigation main.cpp)

target_sources(robot-navigation PUBLIC shape.cpp dijkstra.cpp text.cpp world.cpp random.cpp random_points.cpp grid.cpp)

target_link_libraries(robot-navigation GL)
target_link_libraries(robot-navigation GLU)
target_link_libraries(robot-navigation glut)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")