/*
 * author: Davìd Ferrari
 * version: 1.0.0
 *
 */
#ifndef POLY_HPP
#define POLY_HPP

#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

#define NULL_POLY_DEG                                                          \
  -1 // the 0 polynomial is defined to have a negative degree

template <typename T> class Poly {
  /* Class invariant:
      _elem.size() >= 0
      _elem.back() != 0
  */

public:
  /*** constructors ***/
  Poly();
  Poly(Poly &&) = default;
  Poly &operator=(Poly &&) = default;
  Poly(Poly const &) = default;
  Poly &operator=(Poly const &) = default;
  ~Poly() = default;

  Poly(std ::initializer_list<T>); // build a polynomial from a brace-enclosed
                                   // list
  Poly &operator=(std ::initializer_list<T>); // assign a polynomial build from
                                              // a brace-enclosed list

  Poly(std ::vector<T> const &);
  /*** access methods ***/
  int degree() const;               // polynomial's degree
  const T &operator[](int i) const; // access i-th coefficient of the polynomial

  /*** arithmetic operators overload ***/
  Poly operator+(Poly const &);
  Poly operator-(Poly const &);
  Poly operator*(Poly const &);
  Poly operator*(T const &);
  // this function is defined here to fix the g++ warning: friend define a non
  // template function ...
  template <typename U> friend Poly<T> operator*(U alpha, Poly<T> const &p) {
    Poly scaled{p};
    for (auto &x : scaled._elem)
      x *= alpha;
    return scaled;
  }

  /*** Analysis ***/
  // collection of analytics operations
  T operator()(T);
  Poly operator>>(int); // operator >> is used for derivation

  /*** output ***/
  // this function is defined here to fix the g++ warning: friend define a non
  // template function ...
  friend std ::ostream &operator<<(std ::ostream &o, Poly<T> const &p) {
    for (size_t i = 0; i < p._elem.size(); i++) {
      o << std ::setw(15) << p._elem[i];
      if (i == 1)
        o << " x";
      if (i > 1)
        o << " x^" << i;
    }
    o << '\n';
    return o;
  }

private:
  std ::vector<T> _elem{}; // coefficients of the polynomial
  void aling_coef();
};

/*******************************/
/******* IMPLEMENTATION ********/
/*******************************/

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

template <typename T> Poly<T>::Poly(std ::vector<T> const &v) : _elem{v} {
  while (_elem.size() > 1 && _elem.back() == 0)
    _elem.pop_back();
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

// operator(): evaluate polynomial function in the given point
//  calculation is performed with horner rule
template <typename T> T Poly<T>::operator()(T x) {
  T sum{};
  for (int i = degree(); i >= 0; i--)
    sum = sum * x + _elem[i];
  return sum;
}

template <typename T> Poly<T> Poly<T>::operator>>(int n) {
  if (n == 0)
    return *this;
  if (n == 1) {
    Poly d{*this};
    for (int i = 0; i <= degree(); i++) {
      if (i == degree())
        d._elem[i] = 0;
      else {
        d._elem[i] = d._elem[i+1] * (i + 1);
      }
    }
    d.aling_coef();
    return d;
  }
  return ((operator>>(1)).operator>>(n - 1));
}
// align_coef: util function for removing trailing 0 from the coefficients
// vector
template <typename T> void Poly<T>::aling_coef() {
  while (_elem.size() > 1 && _elem.back() == 0)
    _elem.pop_back();
}

#endif