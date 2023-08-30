cmake_minimum_required(VERSION 3.5)

project(Command)

add_executable(bulk main.cpp)

set_target_properties(bulk PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)