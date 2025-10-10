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
    // Implementation for truth table if needed
}