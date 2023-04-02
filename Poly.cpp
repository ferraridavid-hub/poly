#include "Poly.hpp"
#include "iostream"
#include <stdexcept>

template <typename T> Poly<T>::Poly() : _elem{0} {}

template <typename T>
Poly<T>::Poly(std ::initializer_list<T> list) : _elem{list} {

  // delete trailing 0s
  while (_elem.size() > 1 && _elem.back() == 0)
    _elem.pop_back();
}

template <typename T>
Poly<T> &Poly<T>::operator=(std ::initializer_list<T> list) {
  _elem = list;

  // delete trailing 0s
  while (_elem.size() > 1 && _elem.back() == 0)
    _elem.pop_back();
  return *this;
}

template <typename T> int Poly<T>::degree() const {
  if (_elem.size() == 1 && _elem.back() == 0)
    return NULL_POLY_DEG;
  return _elem.size() - 1;
}

template <typename T> const T &Poly<T>::operator[](int i) const {
  if (i < 0 || (size_t)i >= _elem.size())
    throw std ::out_of_range{"Poly: operator[]"};
  return _elem[i];
}

template <typename T> Poly<T> Poly<T>::operator+(Poly<T> const &b) {
  Poly sum;
  sum._elem = std ::vector<T>(std ::max(degree(), b.degree()) + 1);
  int i{0};

  while (i <= degree() && i <= b.degree()) {
    sum._elem[i] = _elem[i] + b._elem[i];
    i++;
  }

  while (i <= degree()) {
    sum._elem[i] = _elem[i];
    i++;
  }

  while (i <= b.degree()) {
    sum._elem[i] = b._elem[i];
    i++;
  }

  // delete trailing 0
  sum.aling_coef();

  return sum;
}

template <typename T> Poly<T> Poly<T>::operator-(Poly<T> const &b) {
  Poly diff;
  diff._elem = std ::vector<T>(std ::max(degree(), b.degree()) + 1);
  int i{0};

  while (i <= degree() && i <= b.degree()) {
    diff._elem[i] = _elem[i] - b._elem[i];
    i++;
  }

  while (i <= degree()) {
    diff._elem[i] = _elem[i];
    i++;
  }

  while (i <= b.degree()) {
    diff._elem[i] = -b._elem[i];
    i++;
  }

  // delete trailing 0
  diff.aling_coef();

  return diff;
}

// implementation of multiplication between two polinomyals using convolution
// product between {this}_n and {b}_n coefficients sequences
template <typename T> Poly<T> Poly<T>::operator*(Poly<T> const &b) {
  if (degree() == NULL_POLY_DEG || b.degree() == NULL_POLY_DEG)
    return Poly{};
  Poly mult;
  int mdeg = degree() + b.degree();
  mult._elem = std ::vector<T>(mdeg + 1);

  // convolution product
  for (int i = 0; i <= mdeg; i++) {
    auto c{0};
    for (int j = 0; j <= i; j++) {
      auto p = (j <= degree()) ? _elem[j] : 0;
      auto q = (i - j <= b.degree()) ? b._elem[i - j] : 0;
      c += p * q;
    }
    mult._elem[i] = c;
  }

  // delete trailing 0
  mult.aling_coef();

  return mult;
}

template <typename T> Poly<T> Poly<T>::operator*(T const &alpha) {
  Poly scaled{*this};
  for (auto &x : scaled._elem)
    x *= alpha;
  return scaled;
}

// align_coef: util function for removing trailing 0 from the coefficients
// vector
template <typename T> void Poly<T>::aling_coef() {
  while (_elem.size() > 1 && _elem.back() == 0)
    _elem.pop_back();
}

/*** actual implementations for the linker ***/
template class Poly<float>;
template class Poly<double>;
template class Poly<int>;