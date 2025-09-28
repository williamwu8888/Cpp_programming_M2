#pragma once

#include <iostream>
#include "ExpLog.hh"
#include <string>

class Atom : public ExpLog{
public:
  Atom():_id(unique_id++),_val( ThreeVal::U){};
  Atom(ThreeVal::ThreeVal_t val):_id(unique_id++),_val(val){};
  Atom(const Atom& a):_id(unique_id++),_val( a._val){};

  std::size_t id() const{return _id;}
  std::string toString() const;
  ThreeVal::ThreeVal_t evaluate() const {return _val;};
  Atom& operator=(const Atom& a);
  Atom& operator=(bool b);
  Atom& operator=(ThreeVal::ThreeVal_t v);

private:
  std::size_t _id;
   ThreeVal::ThreeVal_t _val;
  static std::size_t unique_id;

};

