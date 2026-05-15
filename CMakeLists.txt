cmake_minimum_required(VERSION 3.15)
project(NotinOOP VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(NotinOOP main.cpp)

file(GLOB_RECURSE SOURCES "src/*.cpp")
target_sources(NotinOOP PRIVATE ${SOURCES})

target_include_directories(NotinOOP PUBLIC include)
