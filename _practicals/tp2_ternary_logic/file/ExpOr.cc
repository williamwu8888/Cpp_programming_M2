#include "ExpOr.hh"

std::string ExpOr::toString() const {
    return "(" + _opd1.toString() + " | " + _opd2.toString() + ")";
}

ThreeVal::ThreeVal_t ExpOr::evaluate() const {
    ThreeVal::ThreeVal_t val1 = _opd1.evaluate();
    ThreeVal::ThreeVal_t val2 = _opd2.evaluate();
    
    // Ternary OR logic
    if (val1 == ThreeVal::T || val2 == ThreeVal::T) return ThreeVal::T;
    if (val1 == ThreeVal::F && val2 == ThreeVal::F) return ThreeVal::F;
    return ThreeVal::U;
}
