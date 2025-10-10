#pragma once

#include "ExpLog.hh"
#include <string>
#include <iostream>

class ExpNot : public ExpLog{
private:
  const ExpLog & _opd;
public:
  ExpNot(const ExpLog & log):_opd(log){};
  ExpNot(ExpNot & log):_opd(log){};
  std::string toString() const;
  ThreeVal::ThreeVal_t evaluate() const;  
  static void truthTable();
};
