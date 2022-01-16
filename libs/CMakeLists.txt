
#stb_image
#adding hashmap
#adding math lib

#adding libraries that will be added to the main program
add_subdirectory(SDL ${CMAKE_CURRENT_BINARY_DIR}/SDL2-build)

#flatbuffers
# Add FlatBuffers directly to our build. This defines the `flatbuffers` target.
add_subdirectory(flatbuffers
                 ${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build
                 EXCLUDE_FROM_ALL)

#adding dearimgui
file(GLOB IMGUI "imgui/*.cpp")
add_library(imgui SHARED ${IMGUI})
target_link_libraries(imgui SDL2main SDL2)



