#ifndef POLY_HPP
#define POLY_HPP

#include <vector>

template <typename T> class Poly {
public:
  Poly();
  Poly(Poly &&) = default;
  Poly &operator=(Poly &&) = default;
  Poly(Poly const &) = default;
  Poly &operator=(Poly const &) = default;
  ~Poly() = default;

  Poly(std ::initializer_list<T>);
  Poly &operator=(std ::initializer_list<T>);

  int degree() const;
  const T &operator[](int i) const;

  Poly operator+(Poly const &);
  Poly operator-(Poly const &);
  Poly operator*(Poly const &);

private:
  std ::vector<T> _elem{};
};

#endif