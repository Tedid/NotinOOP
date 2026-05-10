cmake_minimum_required(VERSION 3.15)
project(NotinOOP VERSION 1.0.0 LANGUAGES CXX)

# Force C++17 as it is the standard for FMI OOP projects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Modern CMake: Define include directories for the target
# This prevents having to use absolute paths in your #include statements
add_executable(NotinOOP main.cpp)

# Automatically find all .cpp files in src/ and its subdirectories
file(GLOB_RECURSE SOURCES "src/*.cpp")
target_sources(NotinOOP PRIVATE ${SOURCES})

# Tell CMake where to look for headers
target_include_directories(NotinOOP PUBLIC 
    include
    include/File
    include/Logic
    include/Objects
    include/util
)

# Enable warnings to help catch bugs early (Intellectual Sparring: don't ignore these!)
if(MSVC)
    target_compile_options(NotinOOP PRIVATE /W4)
else()
    target_compile_options(NotinOOP PRIVATE -Wall -Wextra -Wpedantic)
endif()