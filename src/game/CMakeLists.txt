# Link with CFML
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_library(game STATIC game.cpp)
target_include_directories(
    game
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(game PUBLIC SFML::Graphics SFML::Window SFML::System)
