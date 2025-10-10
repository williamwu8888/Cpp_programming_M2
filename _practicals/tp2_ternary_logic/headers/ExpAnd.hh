#pragma once

#include "ExpBin.hh"
#include <string>
#include <iostream>

class ExpAnd : public ExpBin{
public:
  ExpAnd(ExpLog& log1,ExpLog& log2):ExpBin(log1,log2){};
  std::string toString() const;
  ThreeVal::ThreeVal_t evaluate() const;  
};
