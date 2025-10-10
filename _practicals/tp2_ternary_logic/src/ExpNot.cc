#include "ExpNot.hh"

std::string ExpNot::toString() const {
    return "!" + _opd.toString();
}

ThreeVal::ThreeVal_t ExpNot::evaluate() const {
    ThreeVal::ThreeVal_t val = _opd.evaluate();
    switch(val) {
        case ThreeVal::T: return ThreeVal::F;
        case ThreeVal::F: return ThreeVal::T;
        case ThreeVal::U: return ThreeVal::U;
    }
    return ThreeVal::U; // default
}

void ExpNot::truthTable() {
    // Just print the truth table for NOT operation
    std::cout << "NOT Truth Table:" << std::endl;
    std::cout << "!F = T" << std::endl;
    std::cout << "!T = F" << std::endl; 
    std::cout << "!U = U" << std::endl;
}