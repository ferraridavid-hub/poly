/*
 * author: Davìd Ferrari
 *
 *
 */
#ifndef POLY_HPP
#define POLY_HPP

#include <vector>

#define NULL_POLY_DEG -1 // the 0 polynomial is defined to have a negative degree

template <typename T> class Poly {
  /* Class invariant:
      _elem.size() >= 0
      _elem.back() != 0 
  */

public:
  /*** constructors ***/
  Poly() = default; 
  Poly(Poly &&) = default;
  Poly& operator=(Poly &&) = default;
  Poly(Poly const &) = default;
  Poly& operator=(Poly const &) = default;
  ~Poly() = default;

  Poly(std ::initializer_list<T>); // build a polynomial from a brace-enclosed
                                   // list
  Poly &operator=(std ::initializer_list<T>); // assign a polynomial build from a
                                              // brace-enclosed list

  /*** access methods ***/
  int degree() const; // polynomial's degree
  const T& operator[](int i) const; // access i-th coefficient of the polynomial

  /*** arithmetic operators overload ***/
  Poly operator+(Poly const &);
  Poly operator-(Poly const &);
  Poly operator*(Poly const &);

private:
  std ::vector<T> _elem{}; // coefficients of the polynomial
};

#endif