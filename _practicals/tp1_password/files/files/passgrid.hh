#pragma once
#include <cstdlib>
#include <string>
#include <iostream>
#include <random>
#include "path.hh"

class PassGrid{
 public:
  PassGrid(size_t w, size_t h);
  PassGrid(const PassGrid & p);
  ~PassGrid();
  //getter
  std::size_t getW() const {std::cerr << "getW(): Not yet Implemented" << std::endl; return 1;}
  std::size_t getH() const {std::cerr << "getH(): Not yet Implemented" << std::endl; return 1;}
  char operator()(size_t i, size_t j) const {std::cerr << "operator(): Not yet Implemented" << std::endl; return 1;}
  //Operation
  void reset();
  void save(std::ostream&) const;
  void load(std::istream&) ;
  void print() const;
  std::string generate(const Path& p)const ;
 private:
  char ** grid;
  std::size_t _w;
  std::size_t _h;
  static std::default_random_engine _generator;
  static std::uniform_int_distribution<int> _distribution;
  void fillPG();

};
