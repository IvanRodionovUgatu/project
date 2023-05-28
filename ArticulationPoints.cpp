#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

enum color { white, grey, black };

class Graph {
 private:
  std::vector<std::unordered_set<int>> adjacency_list_;
  std::vector<color> color_vec_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::set<int> articulation_points_;
  int time_ = 0;

 public:
  explicit Graph(int n) {
    adjacency_list_.resize(n);
    color_vec_.resize(n, white);
    time_in_.resize(n);
    time_up_.resize(n);
  }

  void Dfs(int start, int parent) {
    color_vec_[start] = grey;
    time_in_[start] = time_up_[start] = ++time_;
    int n_child = 0;

    for (int u : adjacency_list_[start]) {
      if (color_vec_[u] == grey && u != parent) {
        time_up_[start] = std::min(time_up_[start], time_in_[u]);
      } else if (color_vec_[u] == white) {
        ++n_child;
        Dfs(u, start);
        time_up_[start] = std::min(time_up_[start], time_up_[u]);
        if (time_in_[start] <= time_up_[u] && parent != -1) {
          articulation_points_.insert(start + 1);
        }
      }
    }

    if (parent == -1 && n_child >= 2) {
      articulation_points_.insert(start + 1);
    }

    color_vec_[start] = black;
  }

  void FindArticulationPoints() {
    int n = adjacency_list_.size();
    for (int i = 0; i < n; ++i) {
      if (color_vec_[i] == white) {
        Dfs(i, -1);
      }
    }
  }

  void PrintArticulationPoints() {
    std::cout << articulation_points_.size() << std::endl;
    for (auto& point : articulation_points_) {
      std::cout << point << std::endl;
    }
  }

  friend std::istream& operator>>(std::istream& is, Graph& g);
};

std::istream& operator>>(std::istream& is, Graph& g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;
  g.adjacency_list_[begin].insert(end);
  g.adjacency_list_[end].insert(begin);
  return is;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph gr(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> gr;
  }
  gr.FindArticulationPoints();
  gr.PrintArticulationPoints();

  return 0;
}