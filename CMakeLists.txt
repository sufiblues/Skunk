cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)

project(shurukaro)
if(APPLE)
   include_directories(AFTER "/opt/X11/include")
endif()

#=== INCLUDE dir
include_directories(include)

#=== LIBRARIES 
#  = SDL
add_subdirectory(libs/SDL ${CMAKE_CURRENT_BINARY_DIR}/SDL2-build)
link_libraries(SDL2main SDL2)

#  = IMGUI
file(GLOB IMGUI "libs/imgui/*.cpp")
add_library(imgui SHARED ${IMGUI})
include_directories("libs/imgui")

#  = FLATBUFFERS
add_subdirectory(libs/flatbuffers
                ${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build
               EXCLUDE_FROM_ALL)
include_directories("libs/flatbuffers/include")

#  = STB
include_directories("libs/stb")

#  = parallel hashmap 
include_directories("libs/parallel_hashmap")

#=== Building src
file(GLOB SOURCE "src/*.cpp")
add_library(engine SHARED ${SOURCE})

#=== EXECUTABLE: shurukaro
add_executable(${PROJECT_NAME} main.cpp)

#=== FINAL_LINK: shurukaro
target_link_libraries(${PROJECT_NAME} engine imgui flatbuffers)