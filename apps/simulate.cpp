#include "csv.hpp"
#include "gbm.hpp"
#include <iostream>
#include <random>
int main() {
  std::mt19937 gen(42);

  int steps = 10;
  int n_paths = 2;
  double dt = 0.01;

  double S0 = 100.0;
  double mu = 0.05;
  double sigma = 0.2;

  auto paths = simulate_many(n_paths, steps, dt, S0, mu, sigma, gen);

  for (int i = 0; i < n_paths; i++) {
    std::cout << "Path " << i << ":\n";
    for (double x : paths[i]) {
      std::cout << x << std::endl;
    }
    std::cout << "----\n";
  }
  write_paths_to_csv("build/paths.csv", paths, dt);

  std::cout << "Saved to build/paths.csv\n";
  return 0;
}
