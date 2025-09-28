#pragma once

#include<string>
#include<iostream>
namespace ThreeVal
{
  typedef enum {F,T,U} ThreeVal_t ;
  std::string to_string(ThreeVal_t val);
}

std::ostream& operator<<(std::ostream & out,ThreeVal::ThreeVal_t val);

class ExpLog{
public:

  virtual std::string toString() const  = 0;
  virtual ThreeVal::ThreeVal_t evaluate()const = 0;
};


bool operator==(const ExpLog& exp1, const ExpLog& exp2);
bool operator==(const ExpLog& exp1, ThreeVal::ThreeVal_t exp2);
