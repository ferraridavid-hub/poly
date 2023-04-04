/*
 *  author: Davìd Ferrari
 *
 */

// Class implementing orthogonal polynomials using class Poly<double>
// Example of Poly.hpp usage

#ifndef ORTHOGONAL_POLY_HPP
#define ORTHOGONAL_POLY_HPP

#include "../Poly/Poly.hpp"
#include <vector>

class Orthogonal_Poly {
public:
  /*** Factory methods ***/
  static Poly<double> hermite(int n); // return hermite polynomials of degree n
  static Poly<double>
  laguerre(int n); // return laguerre polynomials of degree n
  static Poly<double>
  legendre(int n); // return legendre polynomials of degree n
  static Poly<double>
  chebyshev(int n); // return chebyshev polynomials of degree n

private:
  // containers that store polynomials from 0 to n degree when the corresponding
  // method is called. Future use
  static std ::vector<Poly<double>> _h_fam;
  static std ::vector<Poly<double>> _lag_fam;
  static std ::vector<Poly<double>> _leg_fam;
  static std ::vector<Poly<double>> _c_fam;
};

#endif