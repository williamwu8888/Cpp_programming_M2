#include "ExpLog.hh"
#include <map>

namespace ThreeVal {
    std::string to_string(ThreeVal_t val) {
        static std::map<ThreeVal_t, std::string> valToString = {
            {F, "F"},
            {T, "T"}, 
            {U, "U"}
        };
        return valToString[val];
    }
}

std::ostream& operator<<(std::ostream& out, ThreeVal::ThreeVal_t val) {
    out << ThreeVal::to_string(val);
    return out;
}

bool operator==(const ExpLog& exp1, const ExpLog& exp2) {
    return exp1.evaluate() == exp2.evaluate();
}

bool operator==(const ExpLog& exp1, ThreeVal::ThreeVal_t exp2) {
    return exp1.evaluate() == exp2;
}