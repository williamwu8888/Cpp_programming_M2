#pragma once

#include "ExpLog.hh"
#include <string>
#include <iostream>

class ExpBin : public ExpLog{
protected:
  ExpLog & _opd1;
  ExpLog & _opd2;
public:
  ExpBin(ExpLog& log1,ExpLog& log2):_opd1(log1),_opd2(log2){};
  std::string toString() const = 0;
  ThreeVal::ThreeVal_t evaluate() const = 0;
};
