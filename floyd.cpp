#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  int max = 101;
  std::vector<std::vector<int>> d(n, std::vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> d[i][j];
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (d[i][j] == max) {
        std::cout << "100 ";
      } else {
        std::cout << d[i][j] << " ";
      }
    }
    std::cout << std::endl;
  }
}