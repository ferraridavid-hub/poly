#include "Poly.hpp"
#include "iostream"
#include <stdexcept>

template <typename T>
Poly<T>::Poly(std ::initializer_list<T> list) : _elem{list} {

  // delete trailing 0s
  while (_elem.size() >= 0 && _elem.back() == 0)
    _elem.pop_back();
}

template <typename T>
Poly<T> &Poly<T>::operator=(std ::initializer_list<T> list) {
  _elem = list;

  // delete trailing 0s
  while (_elem.size() >= 0 && _elem.back() == 0)
    _elem.pop_back();
  return *this;
}

template <typename T> int Poly<T>::degree() const { return _elem.size() - 1; }

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

  // delete trailing 0s
  while (sum._elem.size() >= 0 && sum._elem.back() == 0)
    sum._elem.pop_back();

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

  // delete trailing 0s
  while (diff._elem.size() >= 0 && diff._elem.back() == 0)
    diff._elem.pop_back();

  return diff;
}

// implementation of multiplication between two polinomyals using convolution
// product
// template <typename T> Poly<T> Poly<T>::operator*(Poly<T> const &b) {}

/*** actual implementations for the linker ***/
template class Poly<float>;
template class Poly<double>;
template class Poly<int>;