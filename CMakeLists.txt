cmake_minimum_required(VERSION 3.18.0)

project(shurukaro)
set(CMAKE_CXX_STANDARD 20)

if(APPLE)
   include_directories(AFTER "/opt/X11/include")
endif()

#contains sdl2 flatbuffers ImGui glm stb_image
add_subdirectory(libs)
#link libraries

add_executable(${PROJECT_NAME} main.cpp)

