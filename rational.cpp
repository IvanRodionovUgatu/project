#include "rational.h"

void Rational::Reduce() {
  int gcd = std::gcd(p_, q_);
  p_ /= gcd;
  q_ /= gcd;

  if (q_ < 0) {
    p_ = -p_;
    q_ = -q_;
  }
}

Rational::Rational(int p, int q) {  // NOLINT
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

int Rational::GetNumerator() const {
  return p_;
}

int Rational::GetDenominator() const {
  return q_;
}

void Rational::SetNumerator(int p) {
  this->p_ = p;
  Reduce();
}

void Rational::SetDenominator(int q) {
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

std::istream& operator>>(std::istream& in, Rational& first) {
  char s[50];
  in >> s;
  int p = 0, q = 0;
  int len = strlen(s);
  bool checking_number_for_fraction = false;
  bool fl_checking_number_for_sign = false;
  int i = 0;

  if (s[0] == '+') {
    ++i;
  } else if (s[0] == '-') {
    ++i;
    fl_checking_number_for_sign = true;
  }

  while (i < len) {
    if (s[i] == '/') {
      checking_number_for_fraction = true;

      if (s[i + 1] == '+') {
        i += 2;
      } else if (s[i + 1] == '-') {
        i += 2;
        p = -p;
      } else {
        ++i;
      }
    }

    if (!checking_number_for_fraction) {
      p = p * 10 + int(s[i]) - 48;
    } else {
      q = q * 10 + int(s[i]) - 48;
    }

    ++i;
  }

  if (fl_checking_number_for_sign) {
    p = -p;
  }

  if (!checking_number_for_fraction) {
    first.SetNumerator(p);
    first.SetDenominator(1);
  } else {
    first.SetNumerator(p);
    first.SetDenominator(q);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& first) {
  int q = first.GetDenominator();

  if (q == 1) {
    out << first.GetNumerator();
    return out;
  }

  out << first.GetNumerator() << "/" << first.GetDenominator();
  return out;
}