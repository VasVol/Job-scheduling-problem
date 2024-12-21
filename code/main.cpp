#include <bits/stdc++.h>

int64_t greedy(int64_t n, int64_t m, std::vector<int64_t> p) {
  std::sort(p.begin(), p.end(), std::greater<>());
  std::multiset<int64_t> machines;
  for (int64_t i = 0; i < m; ++i) {
    machines.insert(0);
  }
  for (int64_t i = 0; i < n; ++i) {
    auto iter = machines.begin();
    int64_t min_value = *iter;
    machines.erase(iter);
    machines.insert(min_value + p[i]);
  }
  auto iter = machines.rbegin();
  int64_t max_value = *iter;
  return max_value;
}

int64_t brute_force(int64_t n, int64_t m, const std::vector<int64_t>& p) {
  std::vector<int64_t> p_sorted = p;
  std::sort(p_sorted.begin(), p_sorted.end(), [](const int64_t &a, const int64_t &b) -> bool {
    return a > b;
  });

  int64_t min_max_sum = 0;
  for(const auto& num : p_sorted) {
    min_max_sum += num;
  }

  std::vector<int64_t> bins(m, 0);

  std::function<void(int64_t, int64_t)> backtrack = [&](int64_t index, int64_t current_max) {
    if (index == n) {
      if (current_max < min_max_sum) {
        min_max_sum = current_max;
      }
      return;
    }

    for(int64_t i = 0; i < m; ++i) {
      if (bins[i] + p_sorted[index] < min_max_sum) {
        bins[i] += p_sorted[index];
        int64_t next_max = std::max(current_max, bins[i]);
        backtrack(index + 1, next_max);
        bins[i] -= p_sorted[index];
      }

      if (bins[i] == 0) {
        break;
      }
    }
  };

  backtrack(0, 0);
  return min_max_sum;
}

int main() {
  int64_t is_greedy;
  std::cin >> is_greedy;
  int64_t n, m;
  std::cin >> n >> m;
  std::vector<int64_t> p(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> p[i];
  }

  int64_t ans;
  if (is_greedy == 1) {
    ans = greedy(n, m, p);
  } else {
    ans = brute_force(n, m, p);
  }
  std::cout << ans;
}
