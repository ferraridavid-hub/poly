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
  CHECK(p2.degree() == NULL_POLY_DEG);
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

  Poly<int> p0;
  auto p12{p0 + p9};
  CHECK(p12.degree() == p9.degree());
  CHECK(p0.degree() == NULL_POLY_DEG);

  // (1 + x)(1 + x^2) = 1 + x^2 + x + x^3 =
  Poly<int> pp0{1, 1};
  Poly<int> pp1{1, 0, 1};
  Poly<int> pp2{pp0 * pp1};
  CHECK(pp2.degree() == 3);
  CHECK(pp2[0] == 1);
  CHECK(pp2[1] == 1);
  CHECK(pp2[2] == 1);
  CHECK(pp2[3] == 1);

  pp2 = p0 * pp1;
  CHECK(pp2.degree() == NULL_POLY_DEG);

  // (3 + x + 2x^2)(2)
  Poly<double> pp4{3, 1, 2};
  Poly<double> pp5{2};
  auto pp6{pp5 * pp4};
  CHECK(pp6.degree() == 2);
  CHECK(pp6[0] == 6);
  CHECK(pp6[1] == 2);
  CHECK(pp6[2] == 4);

  Poly<int> i4{4};
  Poly<int> i6{6};
  CHECK((i4 * i6).degree() == 0);
  CHECK((i4 * i6)[0] == 24);

  Poly<double> mp0{1, 2, 1, 2};
  mp0 = mp0 * 3;
  CHECK(mp0.degree() == 3);
  CHECK(mp0[0] == 3);
  CHECK(mp0[1] == 6);
  CHECK(mp0[2] == 3);
  CHECK(mp0[3] == 6);

  Poly<double> mp1{5 * mp0};
  CHECK(mp1.degree() == 3);
  CHECK(mp1[0] == 15);
  CHECK(mp1[1] == 30);
  CHECK(mp1[2] == 15);
  CHECK(mp1[3] == 30);

  std ::vector<Poly<int>> pv{
      {1, 1}, {2, 2, 32}, {2, 3, 0, 23}, {}, {0, 0, 0, 0}};
  for (auto p : pv) {
    std ::cout << p;
  }
  CHECK(pv[3].degree() == pv[4].degree());

  std ::vector<int> v{1, 0, 2, 3, 4};
  Poly<int> ppv{v};
  CHECK(ppv.degree() == 4);
  CHECK(ppv[4] == 4);
  std :: cout << ppv;

}
