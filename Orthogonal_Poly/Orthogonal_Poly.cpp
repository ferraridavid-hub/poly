#include "Orthogonal_Poly.hpp"

/*** static members definitions ***/
std ::vector<Poly<double>> Orthogonal_Poly ::_h_fam;
std ::vector<Poly<double>> Orthogonal_Poly ::_lag_fam;
std ::vector<Poly<double>> Orthogonal_Poly ::_leg_fam;
std ::vector<Poly<double>> Orthogonal_Poly ::_c_fam;

// hermite: return the n-degree hermite polynomials
// store polynomials from 0 to n degree in _h_fam
Poly<double> Orthogonal_Poly::hermite(int n) {
  _h_fam.clear();

  if (n == 0)
    return {1};
  if (n == 1)
    return {0, 2};

  _h_fam.push_back(Poly<double>{1});
  _h_fam.push_back(Poly<double>{0, 2});

  for (int i = 2; i <= n; i++) {
    auto H_n{(Poly<double>{0, 2} * _h_fam[i - 1]) -
             2 * (i - 1) * (_h_fam[i - 2])};
    _h_fam.push_back(H_n);
  }

  return _h_fam.back();
}
// chebyshev: return the n-degree chebyshev polynomials
// store polynomials from 0 to n degree in _h_fam
Poly<double> Orthogonal_Poly ::chebyshev(int n) {
  _c_fam.clear();

  if (n == 0)
    return {1};
  if (n == 1)
    return {0, 1};

  _c_fam.push_back({1});
  _c_fam.push_back({0, 1});

  for (int i = 2; i <= n; i++) {
    auto C_n{Poly<double>{0, 2} * _c_fam[i - 1] - _c_fam[i - 2]};
    _c_fam.push_back(C_n);
  }

  return _c_fam.back();
}