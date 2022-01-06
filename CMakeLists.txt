cmake_minimum_required(VERSION 3.18)
project(simple)

add_compile_options(
    -std=c++20 
    -fmodules-ts 
)

# order is important
add_executable(simple 
    sdlcontext.cxx
    main.cpp
)
