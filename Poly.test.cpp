#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Poly.hpp"
#include "../doctest.h"

TEST_CASE("Testing Poly.hpp") {
  Poly<double> p{1, 2, 3, 0};
  CHECK(p.degree() == 2);
  CHECK(p[0] == 1);
  CHECK(p[1] == 2);
  CHECK(p[2] == 3);

  Poly<double> p2;
  CHECK(p2.degree() == 0);
  CHECK(p2[0] == 0);
  CHECK_THROWS(p2[3]);

  auto p3{p};
  CHECK(p3.degree() == 2);

  Poly<int> p4{1, 0, 2};
  Poly<int> p5{3, 3};
  auto p6{p4 + p5};
  CHECK(p6.degree() == p4.degree());
  CHECK(p6.degree() == 2);
  CHECK(p6[0] == 4);
  CHECK(p6[1] == 3);
  CHECK(p6[2] == 2);

  auto p7{p6 + p4 + p5};
  CHECK(p7.degree() == 2);
  CHECK(p7[0] == 8);
  CHECK(p7[1] == 6);
  CHECK(p7[2] == 4);

  auto p8{p7};
  CHECK(p8.degree() == 2);
  CHECK(p8[0] == 8);
  CHECK(p8[1] == 6);
  CHECK(p8[2] == 4);

  Poly<int> p9{1, 1, 1, 2};
  Poly<int> p10{2, 1, 2, -2};
  Poly<int> p11{p9 + p10};
  CHECK(p11.degree() == 2);
  CHECK(p11[0] == 3);
  CHECK(p11[1] == 2);
  CHECK(p11[2] == 3);
  CHECK_THROWS(p11[3]);
}
