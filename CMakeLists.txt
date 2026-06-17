cmake_minimum_required(VERSION 3.25)

# project name
project(snake_game)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add src folder in which the executable is defined
add_subdirectory(src)

# To improve Zed highlighting
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
