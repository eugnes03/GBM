#include "gbm.hpp"
#include <cmath>

// Internal helper (not exposed)
static double gbm_step(double S, double mu, double sigma, double dt,
                       std::mt19937 &gen) {
  static std::normal_distribution<> dist(0.0, 1.0);
  double Z = dist(gen);

  return S *
         std::exp((mu - 0.5 * sigma * sigma) * dt + sigma * std::sqrt(dt) * Z);
}

std::vector<double> simulate_gbm(int steps, double dt, double S0, double mu,
                                 double sigma, std::mt19937 &gen) {
  std::vector<double> path(steps);
  path[0] = S0;

  for (int i = 1; i < steps; i++) {
    path[i] = gbm_step(path[i - 1], mu, sigma, dt, gen);
  }

  return path;
}

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
