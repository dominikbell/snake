#include "config.hpp"

#include <iostream>
#include <fstream>

[[noreturn]]
void exit_with_failure() {
  std::exit(EXIT_FAILURE);
}

json open_file() {
  // Get the file path and open the stream
  std::ifstream fileStream("../config/config.json");

  // Check if file is being edited right now
  if (!fileStream.is_open()) {
    std::cerr << "Error: Could not open config file.\n";
  }

  try {
    json data = json::parse(fileStream);
    return data;

  } catch (const json::parse_error& e) {
    std::cerr << "JSON Parse Error: " << e.what() << " at byte " << e.byte << '\n';
    exit_with_failure();
  }
}

Configuration get_configuration() {
  json file {open_file()};

  unsigned int grid_height {10};
  if (file.count("grid_height")) {
    grid_height = file["grid_height"];
  }

  unsigned int grid_width {15};
  if (file.count("grid_width")) {
    grid_width = file["grid_width"];
  }

  unsigned int game_speed {1000};
  if (file.count("game_speed")) {
    double speed_factor {file["game_speed"]};
    game_speed = static_cast<unsigned int>(speed_factor * 1000.0);
  }

  float pixels_per_cell {40.0f};
  if (file.count("pixels_per_cell")) {
    pixels_per_cell = file["pixels_per_cell"];
  }
  bool reflective {false};

  return {grid_height, grid_width, pixels_per_cell, game_speed, reflective};
}
