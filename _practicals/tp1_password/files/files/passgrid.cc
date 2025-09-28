#include "passgrid.hh"
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>

// obtain a seed from the system clock:
std::default_random_engine PassGrid::_generator(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> PassGrid::_distribution(33,94);


PassGrid::PassGrid(const PassGrid & p)
{
  std::cerr << "PassGrid(const PassGrid & p): Not yet Implemented" << std::endl;
}

PassGrid::PassGrid(std::size_t w, std::size_t h)
{
  std::cerr << "PassGrid(size_t w, size_t h): Not yet Implemented" << std::endl;
}

PassGrid::~PassGrid()
{
  std::cerr << "~PassGrid(): Not yet Implemented" << std::endl;
}


void PassGrid::save(std::ostream& out) const
{
  std::cerr << "save: Not yet Implemented" << std::endl;
}
void PassGrid::print() const
{
  std::cerr << "Not yet Implemented" << std::endl;
}

void PassGrid::load(std::istream& in)
{
  std::cerr << "load: Not yet Implemented" << std::endl;
}
void PassGrid::reset()
{
  std::cerr << "reset(): Not yet Implemented" << std::endl;
}


std::string PassGrid::generate(const Path& p)const
{
  std::cerr << "generate: Not yet Implemented" << std::endl;return "";
}
