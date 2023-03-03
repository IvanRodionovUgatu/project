#include <iostream>
#include <numeric>
using namespace std;

class RationalDivisionByZero: public std::exception {

};

class Rational {
 private:
  int p_ = 1;
  int q_ = 1;
  void Reduce() {
    int gcd_number = std::gcd(p_, q_);
    q_ /= gcd_number;
    p_ /= gcd_number;
  }
 public:
  void Reduce_public () {
    Reduce();
  }
  Rational(int other) { // NOLINT
    p_ = other;
    q_ = 1;
  }
  Rational() { // NOLINT
    p_ = 0;
    q_ = 0;
  }
  Rational(int p, int q) { // NOLINT
    this->p_ = p;
    this->q_ = q;

    Reduce();

    if (q < 0) {
      this->q_ = -q;
      this->p_ = -p;
    }
  }

  Rational(const Rational& other) {
    p_ = other.p_;
    q_ = other.q_;
  }

  int GetNumerator() {
    return p_;
  }

  int GetDenominator() {
    return q_;
  }

  void SetNumerator(int p) {
    this->p_ = p;
  }

  void SetDenominator(int q) {
    if (q == 0) {
      throw RationalDivisionByZero();
    }
    this->q_ = q;
  }

  Rational& operator+=(const Rational& other) {
    p_ = other.p_ * q_ + p_ * other.q_;
    q_ =  other.q_ * q_;
    Reduce();
    return *this;
  }

  Rational& operator-=(const Rational& other) {
    p_ = p_ * other.q_ -  other.p_ * q_;
    q_ =  other.q_ * q_;
    Reduce();
    return *this;
  }


  Rational& operator*=(const Rational& other) {
    p_ = p_ * other.p_;
    q_ = other.q_ * q_;
    Reduce();
    return *this;
  }

  Rational& operator/=(const Rational& other) {
    p_ = p_ * other.q_;
    q_ = other.p_ * q_;
    Reduce();
    return *this;
  }

  Rational& operator++() {
    *this += 1;
    return *this;
  }

  Rational operator++(int) {
    Rational copy = *this;
    ++*this;
    return copy;
  }

  Rational& operator--() {
    *this -= 1;
    return *this;
  }

  Rational operator--(int) {
    Rational copy = *this;
    --*this;
    return copy;
  }


  bool operator<(const Rational& r) const {
    return p_ * r.q_ < r.p_ * q_;
  }
  bool operator>(const Rational& r) const {
    return r < *this;
  }

  bool operator==(const Rational& r) const {
    return p_ * r.q_ == r.p_ * q_;
  }
};

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
  Rational copy = first;
  copy /= other;
  return copy;
}

istream& operator>>(istream& in, Rational& other) {
  int  p, q;
  char s;
  in >> p >> s >> q;
  if (q < 0) {
    q = -q;
    p = -p;
  }
  other.SetNumerator(p);
  other.SetDenominator(q);
  other.Reduce_public();
  return in;
}

ostream& operator<<(ostream& os, Rational other) {
  return (other.GetNumerator() == 1 && other.GetDenominator() == 1) ? (os << other.GetNumerator()) : (os << other.GetNumerator() << "/" << other.GetDenominator());

}

int main() {
  Rational x;
  cin >> x;
  cout << ++x;
}