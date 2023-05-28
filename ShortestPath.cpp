#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

void Bfs(int start, int end, const std::vector<std::vector<int>>& gr) {
  int n = gr.size();
  std::vector<int> dist(n, -1);
  std::vector<int> parent(n, -1);
  dist[start] = 0;
  std::queue<int> q;
  q.push(start);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (u == end) {
      break;
    }

    for (int v : gr[u]) {

      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        parent[v] = u;
        q.push(v);
      }
    }
  }

  if (dist[end] == -1) {
    std::cout << -1;
    return;
  }

  std::vector<int> path;
  int current = end;

  while (current != -1) {
    path.push_back(current);
    current = parent[current];
  }

  reverse(path.begin(), path.end());
  std::cout << path.size() - 1 << std::endl;

  for (int v : path) {
    std::cout << v << " ";
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  int start_vertex, end_vertex;
  std::cin >> start_vertex >> end_vertex;
  std::vector<std::vector<int>> gr(n + 1);

  for (int i = 0; i < m; ++i) {
    int u, v;
    std::cin >> u >> v;
    gr[u].push_back(v);
    gr[v].push_back(u);
  }

  Bfs(start_vertex, end_vertex, gr);
}