#include "passgrid.hh"
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>

// obtain a seed from the system clock:
std::default_random_engine PassGrid::_generator(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> PassGrid::_distribution(33,94);

// Added a private method to fill the grid with random characters
// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution/operator()
// https://en.cppreference.com/w/cpp/language/static_cast
void PassGrid::fillPG() {
    for (size_t i = 0; i < _h; i++) {
        for (size_t j = 0; j < _w; j++) {
            grid[i][j] = static_cast<char>(_distribution(_generator));
        }
    }
}

// Copy constructor
PassGrid::PassGrid(const PassGrid & p)
{
  _w = p._w;
  _h = p._h;
  
  // Allocate 2D array
  grid = new char*[_h];
  for (size_t i = 0; i < _h; i++) {
      grid[i] = new char[_w];
      for (size_t j = 0; j < _w; j++) {
          grid[i][j] = p.grid[i][j];
      }
  }
}

// Constructor to initialize the grid with random characters
PassGrid::PassGrid(std::size_t w, std::size_t h)
{
  _w = w;
  _h = h;
  
  grid = new char*[_h];
  for (size_t i = 0; i < _h; i++) {
      grid[i] = new char[_w];
  }
  fillPG();
}

// Destructor to free allocated memory
PassGrid::~PassGrid()
{
  for (size_t i = 0; i < _h; i++) {
      delete[] grid[i];
  }
  delete[] grid;
}


// Save the grid to output stream
void PassGrid::save(std::ostream& out) const
{
  for (size_t i = 0; i < _h; i++) {
      for (size_t j = 0; j < _w; j++) {
          out << grid[i][j];
      }
      out << std::endl;
  }
}

// Print the grid to standard output
void PassGrid::print() const
{
  for (size_t i = 0; i < _h; i++) {
      for (size_t j = 0; j < _w; j++) {
          std::cout << grid[i][j];
      }
      std::cout << std::endl;
  }
}

// Load grid from input stream
void PassGrid::load(std::istream& in)
{
  for (size_t i = 0; i < _h; i++) {
      std::string line;
      if (std::getline(in, line)) {
          for (size_t j = 0; j < _w && j < line.length(); j++) {
              grid[i][j] = line[j];
          }
      }
  }
}

// Reset the grid with new random characters
void PassGrid::reset()
{
  fillPG();
}


// Generate password based on the provided path
// https://en.cppreference.com/w/cpp/language/member_functions#const-member_functions
std::string PassGrid::generate(const Path& p)const
{
  std::string password;
  size_t x = p.getStartX();
  size_t y = p.getStartY();
  
  password += grid[y][x];
  
  for (size_t i = 0; i < p.getSize(); i++) {
      Direction dir = p(i);
      switch (dir) {
          case N:  if (y > 0) y--; break;
          case NE: if (y > 0 && x < _w - 1) { y--; x++; } break;
          case NW: if (y > 0 && x > 0) { y--; x--; } break;
          case S:  if (y < _h - 1) y++; break;
          case SE: if (y < _h - 1 && x < _w - 1) { y++; x++; } break;
          case SW: if (y < _h - 1 && x > 0) { y++; x--; } break;
          case E:  if (x < _w - 1) x++; break;
          case W:  if (x > 0) x--; break;
      }
      
      password += grid[y][x];
  }
  
  return password;
}
