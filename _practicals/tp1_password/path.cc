#include "path.hh"
#include <iostream>
#include <ctime>
#include <random>
#include <chrono>

// Static random number generator for Path class
// std::default_random_engine: https://en.cppreference.com/w/cpp/numeric/random/default_random_engine
// std::chrono::system_clock::now(): https://en.cppreference.com/w/cpp/chrono/system_clock/now
// time_since_epoch(): https://en.cppreference.com/w/cpp/chrono/time_point/time_since_epoch
// count(): https://en.cppreference.com/w/cpp/chrono/duration/count
static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

// Constructor to initialize path with random directions and starting point
Path::Path(size_t n, size_t x_max, size_t y_max){
  size = n;
  
  // Allocate path array
  path = new Direction[size];
  
  // Random distributions
  // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::uniform_int_distribution<size_t> start_x_dist(0, x_max - 1);
  std::uniform_int_distribution<size_t> start_y_dist(0, y_max - 1);
  std::uniform_int_distribution<int> dir_dist(0, 7);
  start_x = start_x_dist(generator);
  start_y = start_y_dist(generator);
  
  // Generate random path
  // https://en.cppreference.com/w/cpp/language/static_cast
  for (size_t i = 0; i < size; i++) {
      path[i] = static_cast<Direction>(dir_dist(generator));
  }
}

// Destructor to free allocated memory
Path::~Path()
{
  delete[] path;
}

// Convert path to string representation
// https://en.cppreference.com/w/cpp/string/basic_string/to_string
std::string Path::toString() const
{
  std::string result = "(" + std::to_string(start_x) + "," + std::to_string(start_y) + ")";
  for (size_t i = 0; i < size; i++) {
      result += " ";
      switch (path[i]) {
          case N:  result += "N"; break;
          case NE: result += "NE"; break;
          case NW: result += "NW"; break;
          case S:  result += "S"; break;
          case SE: result += "SE"; break;
          case SW: result += "SW"; break;
          case E:  result += "E"; break;
          case W:  result += "W"; break;
      }
  }
  return result;
}

void Path::print() const
{
  std::cout << toString() << std::endl;
}