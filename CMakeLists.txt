cmake_minimum_required(VERSION 3.18.0)

project(shurukaro)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
if(APPLE)
   include_directories(AFTER "/opt/X11/include")
endif()

