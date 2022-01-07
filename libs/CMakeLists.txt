#adding libraries that will be added to the main program
add_subdirectory(SDL ${CMAKE_CURRENT_BINARY_DIR}/SDL2-build)
include_directories("SDL/include/")
link_libraries(SDL2main SDL2)
#adding hashmap
include_directories(parallel_hashmap)
#adding math lib
include_directories(glm)
#adding dearimgui
file(GLOB IMGUI "imgui/*.cpp")
add_library(imgui SHARED ${IMGUI})
link_libraries(imgui)
#flatbuffers

#stb_image


