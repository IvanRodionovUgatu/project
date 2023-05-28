#include <iostream>
#include <vector>

bool Dfs(int start, std::vector<int>& color, std::vector<int>& prev, std::vector<std::vector<int>>& gr,
         std::vector<int>& cycle) {
  color[start] = 1;
  for (auto& u : gr[start]) {
    if (color[u] == 0) {
      prev[u] = start;
      if (Dfs(u, color, prev, gr, cycle)) {
        return true;
      }
    } else if (color[u] == 1) {
      prev[u] = start;
      int cur = start;
      while (cur != u) {
        cycle.push_back(cur + 1);
        cur = prev[cur];
      }
      cycle.push_back(u + 1);
      return true;
    }
  }
  color[start] = 2;
  return false;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> prev(n, -1);
  std::vector<std::vector<int>> gr(n);
  std::vector<int> color(n, 0);
  std::vector<int> cycle;
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u;
    --v;
    gr[u].push_back(v);
  }
  bool has_cycle = false;
  for (int i = 0; i < n; ++i) {
    if (color[i] == 0 && Dfs(i, color, prev, gr, cycle)) {
      has_cycle = true;
      break;
    }
  }
  if (has_cycle) {
    std::cout << "YES" << std::endl;
    for (int i = cycle.size() - 1; i >= 0; --i) {
      std::cout << cycle[i] << " ";
    }
  } else {
    std::cout << "NO" << std::endl;
  }
}