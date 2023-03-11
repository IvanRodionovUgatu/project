#include "rational.h"

void Rational::Reduce() {
  int64_t gcd = std::gcd(p_, q_);
  p_ /= gcd;
  q_ /= gcd;

  if (q_ < 0) {
    p_ = -p_;
    q_ = -q_;
  }
}

Rational::Rational(int64_t p, int64_t q) {  // NOLINT
  if (q == 0) {
    throw RationalDivisionByZero();
  }

  p_ = p;
  q_ = q;

  Reduce();
}

Rational::Rational(const Rational& r) {
  p_ = r.p_;
  q_ = r.q_;
}

int64_t Rational::GetNumerator() const {
  return p_;
}

int64_t Rational::GetDenominator() const {
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

Rational& Rational::operator+=(const Rational& other) {
  p_ = p_ * other.q_ + q_ * other.p_;
  q_ = q_ * other.q_;
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

Rational& Rational::operator-=(const Rational& other) {
  p_ = p_ * other.q_ - q_ * other.p_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
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

Rational& Rational::operator*=(const Rational& other) {
  p_ = p_ * other.p_;
  q_ = q_ * other.q_;
  Reduce();
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  if (other.p_ == 0) {
    throw RationalDivisionByZero();
  }
  p_ = p_ * other.q_;
  q_ = q_ * other.p_;
  Reduce();
  return *this;
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
  if (other.GetNumerator() == 0) {
    throw RationalDivisionByZero();
  }
  Rational copy = first;
  copy /= other;
  return copy;
}

bool operator==(const Rational& first, const Rational& second) {
  return (first.GetNumerator() == second.GetNumerator() && first.GetDenominator() == second.GetDenominator());
}

bool operator!=(const Rational& first, const Rational& second) {
  return !(first == second);
}

bool operator<(const Rational& first, const Rational& second) {
  return first.GetNumerator() * second.GetDenominator() < first.GetDenominator() * second.GetNumerator();
}

bool operator<=(const Rational& first, const Rational& second) {
  return (first < second || first == second);
}

bool operator>(const Rational& first, const Rational& second) {
  return !(first <= second);
}

bool operator>=(const Rational& first, const Rational& second) {
  return !(first < second);
}

std::ostream& operator<<(std::ostream& out, const Rational& first) {
  int64_t q = first.GetDenominator();
  if (q == 1) {
    out << first.GetNumerator();
    return out;
  }
  out << first.GetNumerator() << "/" << first.GetDenominator();
  return out;
}

std::istream& operator>>(std::istream& in, Rational& first) {
  char s[100];
  bool flag = false;
  in >> s;
  int len = strlen(s);
  int p = 0, q = 0, index;
  for (index = 0; index < len; ++index) {
    if (s[index] == '-') {
      flag = !flag;
    } else if (s[index] == '+') {
      continue;
    } else if (s[index] != '/') {
      p = p * 10 + s[index] - '0';
    } else {
      ++index;
      break;
    }
  }

  if (index == len) {
    q = 1;
  }

  while (index < len) {
    if (s[index] == '-') {
      flag = !flag;
    } else if (s[index] != '+') {
      q = q * 10 + s[index] - '0';
    }
    ++index;
  }

  if (flag) {
    p *= -1;
  }

  first.SetDenominator(1);
  first.SetNumerator(p);
  first.SetDenominator(q);
  first.Reduce();
  return in;
}