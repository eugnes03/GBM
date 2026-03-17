#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>

// Start with the Brownian Increment
double dW(double dt, std::mt19937 &gen) {
  static std::normal_distribution<> dist(0.0, 1.0);
  return std::sqrt(dt) * dist(gen);
}
// Exact GBM step
double gbm_step(double S, double mu, double sigma, double dt,
                std::mt19937 &gen) {
  static std::normal_distribution<> dist(0.0, 1.0);
  double Z = dist(gen);

  return S *
         std::exp((mu - 0.5 * sigma * sigma) * dt + sigma * std::sqrt(dt) * Z);
}
// Now lets consider a Weiner Process
std::vector<double> simulate_gbm(int steps, double dt, double S0, double mu,
                                 double sigma, std::mt19937 &gen) {
  std::vector<double> path(steps);
  path[0] = S0;

  for (int i = 1; i < steps; i++) {
    path[i] = gbm_step(path[i - 1], mu, sigma, dt, gen);
  }

  return path;
}
// Many Paths
std::vector<std::vector<double>> simulate_many(int n_paths, int steps,
                                               double dt, double S0, double mu,
                                               double sigma,
                                               std::mt19937 &gen) {

  std::vector<std::vector<double>> paths;

  for (int i = 0; i < n_paths; i++) {
    paths.push_back(simulate_gbm(steps, dt, S0, mu, sigma, gen));
  }

  return paths;
}

int main() {
  std::mt19937 gen(42);
  int steps = 10;
  double dt = 0.01;

  double S0 = 100.0;
  double mu = 0.05;
  double sigma = 0.2;

  int n_paths = 10;
  auto path = simulate_gbm(steps, dt, S0, mu, sigma, gen);

  auto paths = simulate_many(n_paths, steps, dt, S0, mu, sigma, gen);

  std::cout << "GBM Path: \n" << std::endl;
  for (double x : path) {
    std::cout << x << std::endl;
  }
  std::cout << "Sampling from Distribution: \n";
  for (int i = 0; i < 5; i++) {
    std::cout << dW(dt, gen) << std::endl;
  }

  for (int i = 0; i < n_paths; i++) {
    std::cout << "Path " << i << ":\n";
    for (double x : paths[i]) {
      std::cout << x << std::endl;
    }
    std::cout << "----\n";
  }
  return 0;
}
