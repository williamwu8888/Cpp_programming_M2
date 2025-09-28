// Let Catch provide main():
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
// include your classes here

TEST_SUITE("threeval") {
  TEST_CASE("1: Atoms toString") {

    Atom a(U), b, d(F);
    Atom c(b);
    CHECK(a.toString() == "(a_0 = U)");
    CHECK(b.toString() == "(a_1 = U)");
    CHECK(c.toString() == "(a_3 = U)");
    CHECK(d.toString() == "(a_2 = F)");
  }

  TEST_CASE("2: Create Atoms and evaluate Atoms") {
    Atom a(U), b, c(T), d(F);
    CHECK(a.evaluate() == U);
    CHECK(b.evaluate() == U);
    CHECK(c.evaluate() == T);
    CHECK(d.evaluate() == F);
    Atom e(a);
    CHECK(e.evaluate() == U);
    CHECK((a.id() != e.id() && b.id() != a.id() && a.id() != c.id()));
  }

  TEST_CASE("3: Assign Atoms ") {
    Atom a, b;
    a = T;
    CHECK(a.evaluate() == T);
    a = false;
    CHECK(a.evaluate() == F);
    a = b = T;
    CHECK((a.evaluate() == T && b.evaluate() == T));
  }

  TEST_CASE("4: Create and Evaluate NOT operator") {
    Atom a(U), b, c(T), d(F);
    ExpNot not1(c);

    CHECK(not1.evaluate() == F);
    CHECK(not1.toString() == "!(a_13 = T)");
    CHECK(ExpNot(not1).evaluate() == T);
    CHECK(ExpNot(not1).toString() == "!!(a_13 = T)");
  }

  TEST_CASE("5: Create and Evaluate AND et OR operator") {
    Atom a(T);
    Atom b;
    Atom c(F);
    ExpNot not1(a);
    ExpAnd and1(not1, b);
    ExpAnd and2(a, b);
    ExpOr or1(and1, and2);
    CHECK(and1.evaluate() == F);
    CHECK(and2.evaluate() == U);
    CHECK(or1.evaluate() == U);
  }

  TEST_CASE("6: Equal operation") {
    Atom a(U), b(U), c(U);
    ExpNot nota(a);
    ExpAnd and1(a, b);
    ExpAnd and2(nota, c);
    ExpAnd and3(b, c);
    ExpOr or1(and1, and2);
    ExpOr or2(or1, and3);
    CHECK(or2 == U);
    a = T;
    b = T;
    CHECK(a == T);
    CHECK(or2 == T);
  }
}
