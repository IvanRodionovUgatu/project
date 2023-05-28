#include <iostream>
#include <vector>
#include <string>

std::vector<int> PrefixFunction(std::string s) {
  int n = s.size();
  std::vector<int> pi(n);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = pi[j - 1];
    }
    if (s[i] == s[j]) {
      j++;
    }
    pi[i] = j;
  }
  return pi;
}

int main() {
  std::string s;
  std::cin >> s;
  int n = s.size();
  std::vector<int> pi = PrefixFunction(s);
  for (int i = 0; i < n; ++i) {
    std::cout << pi[i] << " ";
  }
}