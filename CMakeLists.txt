cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(codereview VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_executable(codereview src/codereview.cpp)

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT codereview)
