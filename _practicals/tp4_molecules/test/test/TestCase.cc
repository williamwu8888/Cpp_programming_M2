
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "atome.hh"
#include "molecule.hh"
#include "reaction.hh"
#include <iostream>
TEST_SUITE("Molecule") {
  TEST_CASE("1: Atoms fromString") {
    atome a("BH");
    CHECK( a.to_string() == "BH");
  }
TEST_CASE("2: Molecule"){
    molecule m("A-C-BH");
    std::cout << m.to_string() << std::endl;
    CHECK(m.to_string() == "A-C-BH");
  }  
TEST_CASE("3: Normalise "){
    molecule m("C-A-Nb-A-O-O");
    CHECK(m.normalise() == "A2CNbO2");
  }
TEST_CASE("4: Reaction"){
    reaction r("A-B + B-O -> A-B-B-O");
    CHECK(r.to_string() == "AB + BO -> AB2O");

  }
}