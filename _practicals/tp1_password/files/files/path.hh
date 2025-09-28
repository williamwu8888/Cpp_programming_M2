#pragma once

#include<iostream>
#include<cstdlib>
#include <string>

typedef enum  Direction {N, NE, NW , S, SE, SW, E,W}  Direction;
// A Path is build with a size and 2 Bounds
class Path{
 public:
  Path(size_t n, size_t x_max, size_t y_max);
  ~Path();
  std::size_t getSize() const { std::cerr << "Path::getSize(): Not yet Implemented" << std::endl;
return 1;}
  std::size_t getStartX()const{ std::cerr << "Path::getStartX(): Not yet Implemented" << std::endl;
return 1;}
  std::size_t getStartY()const{ std::cerr << "Path::getStartY(): Not yet Implemented" << std::endl;
return 1;}
  std::string toString() const;
  void print()const;
  Direction  operator()(size_t i) const{std::cout << "Path::operator(): Not yet Implemented" << std::endl; return N;}
 private:
  std::size_t size;
  Direction * path; 
  std::size_t start_x;
  std::size_t start_y;
  
};

