#ifndef PROJECT__RATIONAL_H_
#define PROJECT__RATIONAL_H_
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
  Rational(int64_t);           // NOLINT
  Rational();                  // NOLINT
  Rational(int64_t, int64_t);  // NOLINT
  Rational(const Rational&);   // NOLINT
  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int64_t);
  void SetDenominator(int64_t);
  Rational operator+() const;
  Rational operator-() const;
  Rational& operator=(const Rational&);
  Rational& operator+=(const Rational&);
  Rational& operator-=(const Rational&);
  Rational& operator*=(const Rational&);
  Rational& operator/=(const Rational&);
  Rational& operator++();
  Rational operator++(int);
  Rational& operator--();
  Rational operator--(int);
};
bool operator<(const Rational&, const Rational&);
bool operator<=(const Rational&, const Rational&);
bool operator>(const Rational&, const Rational&);
bool operator>=(const Rational&, const Rational&);
bool operator==(const Rational&, const Rational&);
bool operator!=(const Rational&, const Rational&);
Rational operator+(const Rational&, const Rational&);
Rational operator-(const Rational&, const Rational&);
Rational operator*(const Rational&, const Rational&);
Rational operator/(const Rational&, const Rational&);
std::istream& operator>>(std::istream&, Rational&);
std::ostream& operator<<(std::ostream& os, const Rational&);

#endif  // PROJECT__RATIONAL_H_
