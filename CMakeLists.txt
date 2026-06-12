cmake_minimum_required(VERSION 3.25)

# project name
project(snake_game)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add src folder in which the executable is defined
add_subdirectory(src)

# Link with CFML
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
target_link_libraries(snake_game PRIVATE SFML::Graphics SFML::Window SFML::System)

# To improve Zed highlighting
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
