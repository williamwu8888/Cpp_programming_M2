#include "Atom.hh"

// Static member initialization - START FROM 0
std::size_t Atom::unique_id = 0;

// Implementation of toString() method
std::string Atom::toString() const {
    return "(a_" + std::to_string(_id) + " = " + ThreeVal::to_string(_val) + ")";
}

// Assignment operators implementation
Atom& Atom::operator=(const Atom& a) {
    if (this != &a) {
        _val = a._val;
        // Note: _id is NOT copied - it keeps its original value
    }
    return *this;
}

Atom& Atom::operator=(bool b) {
    _val = b ? ThreeVal::T : ThreeVal::F;
    return *this;
}

Atom& Atom::operator=(ThreeVal::ThreeVal_t v) {
    _val = v;
    return *this;
}