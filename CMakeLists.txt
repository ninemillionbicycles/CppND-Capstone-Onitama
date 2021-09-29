cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

project(Onitama)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

add_executable(Onitama ${project_SRCS})

# add_executable(Onitama src/main.cpp)
