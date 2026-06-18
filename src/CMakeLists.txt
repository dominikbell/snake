add_subdirectory(config)
add_subdirectory(food)
add_subdirectory(game)
add_subdirectory(snake)
add_subdirectory(utils)

add_executable(snake_game main.cpp)

target_link_libraries(snake_game PRIVATE config)
target_link_libraries(snake_game PRIVATE food)
target_link_libraries(snake_game PRIVATE game)
# target_link_libraries(snake_game PRIVATE snake)

# Then finally add the directory to the target
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
