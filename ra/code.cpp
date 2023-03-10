#include "rational.h"

void Rational::Reduce() {
  int gcd_number = std::gcd(p_, q_);
  q_ /= gcd_number;
  p_ /= gcd_number;
}

Rational::Rational(int64_t other) {
  p_ = other;
  q_ = 1;
}

Rational::Rational() {
  p_ = 0;
  q_ = 1;
}

Rational::Rational(int64_t p, int64_t q) {
  if (q == 0) {
    throw RationalDivisionByZero{};
  }
  this->p_ = p;
  this->q_ = q;
  Reduce();
  if (q < 0) {
    this->q_ = -q;
    this->p_ = -p;
  }
}

Rational::Rational(const Rational& other) {
  p_ = other.p_;
  q_ = other.q_;
}

int Rational::GetNumerator() const {
  return p_;
}

int Rational::GetDenominator() const {
  return q_;
}

void Rational::SetNumerator(int64_t p) {
  this->p_ = p;
  Reduce();
}

void Rational::SetDenominator(int64_t q) {
  if (q == 0) {
    throw RationalDivisionByZero{};
  }
  this->q_ = q;
  Reduce();
}

Rational Rational::operator+() const {
  Rational copy = *this;
  return copy;
}

Rational Rational::operator-() const {
  Rational copy = *this;
  copy.p_ = -copy.p_;
  return copy;
}

Rational& Rational::operator=(const Rational& other) = default;

Rational& Rational::operator+=(const Rational& other) {
  p_ = other.p_ * q_ + p_ * other.q_;
  q_ = other.q_ * q_;
  Reduce();
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  p_ = p_ * other.q_ - other.p_ * q_;
  q_ = other.q_ * q_;
  Reduce();
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  p_ = p_ * other.p_;
  q_ = other.q_ * q_;
  Reduce();
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  if (other.GetNumerator() == 0 && other.GetDenominator() == 1) {
    throw RationalDivisionByZero{};
  }
  p_ = p_ * other.q_;
  q_ = other.p_ * q_;
  Reduce();
  return *this;
}

Rational& Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  ++*this;
  return copy;
}

Rational& Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}

bool operator<(const Rational& first, const Rational& other) {
  return first.GetNumerator() * other.GetDenominator() < other.GetNumerator() * first.GetDenominator();
}

bool operator<=(const Rational& first, const Rational& other) {
  return first.GetNumerator() * other.GetDenominator() <= other.GetNumerator() * first.GetDenominator();
}

bool operator>(const Rational& first, const Rational& other) {
  return other.GetNumerator() * first.GetDenominator() < first.GetNumerator() * other.GetDenominator();
}

bool operator>=(const Rational& first, const Rational& other) {
  return other.GetNumerator() * first.GetDenominator() <= first.GetNumerator() * other.GetDenominator();
}

bool operator==(const Rational& first, const Rational& other) {
  return first.GetNumerator() * other.GetDenominator() == other.GetNumerator() * first.GetDenominator();
}

bool operator!=(const Rational& first, const Rational& other) {
  return first.GetNumerator() * other.GetDenominator() != other.GetNumerator() * first.GetDenominator();
}

Rational operator+(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy += other;
  return copy;
}

Rational operator-(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy -= other;
  return copy;
}

Rational operator*(const Rational& first, const Rational& other) {
  Rational copy = first;
  copy *= other;
  return copy;
}

Rational operator/(const Rational& first, const Rational& other) {
  if (other.GetNumerator() == 0 && other.GetDenominator() == 1) {
    throw RationalDivisionByZero{};
  }
  Rational copy = first;
  copy /= other;
  return copy;
}

std::ostream& operator<<(std::ostream& os, const Rational& other) {
  if (other.GetDenominator() == 1) {
    os << other.GetNumerator();
  } else {
    os << other.GetNumerator() << "/" << other.GetDenominator();
  }
  return os;
}

std::istream& operator>>(std::istream& is, Rational& other) {
  bool f = false;
  char s[50];
  is >> s;
  int a = 0, b = 0, len = strlen(s), i;
  for (i = 0; i < len; ++i) {
    if (s[i] == '-') {
      f = !f;
    } else if (s[i] == '+') {
      continue;
    } else if (s[i] != '/') {
      a = a * 10 + s[i] - '0';
    } else {
      ++i;
      break;
    }
  }
  if (len == i) {
    b = 1;
  }
  for (; i < len; ++i) {
    if (s[i] == '-') {
      f = !f;
    } else if (s[i] != '+') {
      b = b * 10 + s[i] - '0';
    }
  }
  if (f) {
    a = -a;
  }
  other.SetDenominator(1);
  other.SetNumerator(a);
  other.SetDenominator(b);
  return is;
}
