add_library(food STATIC food.cpp)
target_include_directories(
    food
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
