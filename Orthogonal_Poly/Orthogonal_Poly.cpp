#include "Orthogonal_Poly.hpp"
#include <stdexcept>

/*** static members definitions ***/
std ::vector<Poly<double>> Orthogonal_Poly ::_h_fam;
std ::vector<Poly<double>> Orthogonal_Poly ::_lag_fam;
std ::vector<Poly<double>> Orthogonal_Poly ::_leg_fam;
std ::vector<Poly<double>> Orthogonal_Poly ::_c_fam;

// hermite: return the n-degree hermite polynomials
// store polynomials from 0 to n degree in _h_fam
Poly<double> Orthogonal_Poly::hermite(int n) {
  if (n < 0)
    throw std ::invalid_argument{"hermite:degree must be positive\n"};

  _h_fam.clear();

  if (n == 0)
    return {1};
  if (n == 1)
    return {0, 2};

  // two-step recursive formula
  _h_fam.push_back(Poly<double>{1});
  _h_fam.push_back(Poly<double>{0, 2});

  for (int i = 2; i <= n; i++) {
    auto H_n{(Poly<double>{0, 2} * _h_fam[i - 1]) -
             2 * (i - 1) * (_h_fam[i - 2])};
    _h_fam.push_back(H_n);
  }

  return _h_fam.back();
}

// laguerre: return the n-degree laguerre polynomials
//  stroe polynomials from 0 to n degree in _lag_fam
Poly<double> Orthogonal_Poly::laguerre(int n) {
  if (n < 0)
    throw std ::invalid_argument("laguerre: degree must be positive\n");

  _lag_fam.clear();

  if (n == 0)
    return {1};
  if (n == 1)
    return {1, 1};

  // two-step recursive formula
  _lag_fam.push_back({1});
  _lag_fam.push_back({1, -1});

  for (int i = 2; i <= n; i++) {
    auto l_1{Poly<double>{(2 * i - 1) / (double)(i), -1 / (double)(i)} *
             _lag_fam[i - 1]};
    auto l_2{(-(i - 1) / (double)(i)) * _lag_fam[i - 2]};
    _lag_fam.push_back(l_1 + l_2);
  }

  return _lag_fam.back();
}

// legendre: return the n-degree legendre polynomials
//  store polynomials from 0 to n degree in _leg_fam
Poly<double> Orthogonal_Poly::legendre(int n) {
  if (n < 0)
    throw std ::invalid_argument{"legendre: degree must be positive\n"};

  _leg_fam.clear();

  if (n == 0)
    return {1};
  if (n == 1)
    return {0, 1};

  _leg_fam.push_back({1});
  _leg_fam.push_back({0, 1});

  for (int i = 2; i <= n; i++) {
    auto l1{Poly<double>{0, (2 * i - 1) / (double)(i)} * _leg_fam[i - 1]};
    auto l2{-(i - 1) / (double)(i)*_leg_fam[i - 2]};
    _leg_fam.push_back(l1 + l2);
  }

  return _leg_fam.back();
}

// chebyshev: return the n-degree chebyshev polynomials
// store polynomials from 0 to n degree in _h_fam
Poly<double> Orthogonal_Poly ::chebyshev(int n) {
  if (n < 0)
    throw std ::invalid_argument{"hermite:degree must be positive\n"};

  _c_fam.clear();

  if (n == 0)
    return {1};
  if (n == 1)
    return {0, 1};

  // two-step recursive formula
  _c_fam.push_back({1});
  _c_fam.push_back({0, 1});

  for (int i = 2; i <= n; i++) {
    auto C_n{Poly<double>{0, 2} * _c_fam[i - 1] - _c_fam[i - 2]};
    _c_fam.push_back(C_n);
  }

  return _c_fam.back();
}