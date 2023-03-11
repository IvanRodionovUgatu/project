#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <cstring>

class RationalDivisionByZero : public std::exception {};

class Rational {
 private:
  int64_t p_ = 1;
  int64_t q_ = 1;

 public:
  void Reduce();
  Rational(int64_t p = 0, int64_t q = 1);  // NOLINT
  Rational(const Rational& r);
  int64_t GetNumerator() const;
  int64_t GetDenominator() const;
  void SetNumerator(int64_t p);
  void SetDenominator(int64_t q);
  Rational& operator+=(const Rational& other);
  Rational& operator++();
  Rational& operator-=(const Rational& other);
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);
  Rational operator+() const;
  Rational operator-() const;
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
