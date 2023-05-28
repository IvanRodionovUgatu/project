#include <iostream>
#include <cstring>
#include <vector>

std::vector<int> ZFunc(std::string& s) {
  int n = s.size();
  std::vector<int> z(n, 0);
  int left = 0;
  int right = 0;
  z[0] = s.size();

  for (int i = 1; i < n; ++i) {

    if (i <= right) {
      z[i] = std::min(z[i - left], right - i);
    }

    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }

    if (right < i + z[i]) {
      right = i + z[i];
      left = i;
    }
  }

  return z;
}

int main() {
  std::string s;
  std::cin >> s;

  for (auto el : ZFunc(s)) {
    std::cout << el << " ";
  }
}