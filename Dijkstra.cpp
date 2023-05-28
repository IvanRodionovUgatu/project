#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Edge {
  int to;
  int weight;

  Edge(int to, int weight) : to(to), weight(weight) {
  }
};

using Graph = std::vector<std::vector<Edge>>;

std::vector<int> Dijkstra(const Graph& graph, int start) {
  int n = graph.size();
  std::vector<int> distance(n, std::numeric_limits<int>::max());
  distance[start] = 0;

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
  pq.push(std::make_pair(0, start));

  while (!pq.empty()) {
    int u = pq.top().second;
    int dist = pq.top().first;
    pq.pop();

    if (dist > distance[u]) {
      continue;
    }

    for (const Edge& edge : graph[u]) {
      int v = edge.to;
      int weight = edge.weight;

      if (distance[u] + weight < distance[v]) {
        distance[v] = distance[u] + weight;
        pq.push(std::make_pair(distance[v], v));
      }
    }
  }

  return distance;
}

int main() {
  int k;
  std::cin >> k;

  for (int i = 0; i < k; ++i) {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);
    for (int j = 0; j < m; ++j) {
      int u, v, w;
      std::cin >> u >> v >> w;
      graph[u].emplace_back(v, w);
      graph[v].emplace_back(u, w);
    }

    int start;
    std::cin >> start;

    std::vector<int> distances = Dijkstra(graph, start);

    for (int j = 0; j < n; ++j) {
      if (distances[j] == std::numeric_limits<int>::max()) {
        distances[j] = 2009000999;
      }
      std::cout << distances[j] << ' ';
    }

    std::cout << '\n';
  }

  return 0;
}