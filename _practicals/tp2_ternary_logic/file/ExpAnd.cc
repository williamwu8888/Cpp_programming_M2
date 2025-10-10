#include "ExpAnd.hh"

std::string ExpAnd::toString() const {
    return "(" + _opd1.toString() + " & " + _opd2.toString() + ")";
}

ThreeVal::ThreeVal_t ExpAnd::evaluate() const {
    ThreeVal::ThreeVal_t val1 = _opd1.evaluate();
    ThreeVal::ThreeVal_t val2 = _opd2.evaluate();
    
    // Ternary AND logic
    if (val1 == ThreeVal::F || val2 == ThreeVal::F) return ThreeVal::F;
    if (val1 == ThreeVal::T && val2 == ThreeVal::T) return ThreeVal::T;
    return ThreeVal::U;
}