#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <cstring>

class RationalDivisionByZero : public std::exception {};

class Rational {
 private:

  int p_ = 1;
  int q_ = 1;
  void Reduce();

 public:
  Rational(int p = 0, int q = 1);  // NOLINT
  Rational(const Rational& r);

  int GetNumerator() const;
  int GetDenominator() const;

  void SetNumerator(int p);
  void SetDenominator(int q);
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);

  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);

  Rational operator+() const;
  Rational operator-() const;

  void ReducePublic();
};

Rational operator+(const Rational& first, const Rational& other);
Rational operator-(const Rational& first, const Rational& other);
Rational operator*(const Rational& first, const Rational& other);
Rational operator/(const Rational& first, const Rational& other);

bool operator==(const Rational& first, const Rational& second);
bool operator!=(const Rational& first, const Rational& second);
bool operator<(const Rational& first, const Rational& second);
bool operator<=(const Rational& first, const Rational& second);
bool operator>(const Rational& first, const Rational& second);
bool operator>=(const Rational& first, const Rational& second);

std::ostream& operator<<(std::ostream& out, const Rational& first);
std::istream& operator>>(std::istream& in, Rational& first);

#endif
