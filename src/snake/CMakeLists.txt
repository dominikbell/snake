add_library(snake STATIC snake.cpp)
target_include_directories(
    snake
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
