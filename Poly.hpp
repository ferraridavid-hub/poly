/*
 * author: Davìd Ferrari
 * version: 1.0.0
 *
 */
#ifndef POLY_HPP
#define POLY_HPP

#include <iomanip>
#include <ostream>
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

  /*** access methods ***/
  int degree() const;               // polynomial's degree
  const T &operator[](int i) const; // access i-th coefficient of the polynomial

  /*** arithmetic operators overload ***/
  Poly operator+(Poly const &);
  Poly operator-(Poly const &);
  Poly operator*(Poly const &);
  Poly operator*(T const &);
  friend Poly<T> operator*(T alpha, Poly<T> const &p) {
    Poly scaled{p};
    for (auto &x : scaled._elem)
      x *= alpha;
    return scaled;
  }

  /*** output ***/
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

#endif