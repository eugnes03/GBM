#include "black_scholes.hpp"
#include "csv.hpp"
#include "gbm.hpp"
#include "monte_carlo.hpp"
#include <iomanip>
#include <iostream>
#include <random>

int main() {
  std::mt19937 gen(13);

  int steps = 1000;
  int n_paths = 1000;
  double dt = 0.01;

  double S0    = 100.0;
  double mu    = 0.05;   // used as risk-neutral drift r
  double sigma = 0.2;
  double K     = 100.0;  // at-the-money strike
  double r     = mu;
  double T     = steps * dt;

  auto paths = simulate_many(n_paths, steps, dt, S0, r, sigma, gen);

  write_paths_to_csv("data/paths.csv", paths, dt);
  std::cout << "Saved to data/paths.csv\n\n";

  double bs_c  = bs_call(S0, K, r, sigma, T);
  double bs_p  = bs_put(S0, K, r, sigma, T);
  double mc_c  = mc_call(paths, K, r, T);
  double mc_p  = mc_put(paths, K, r, T);

  std::cout << std::fixed << std::setprecision(4);
  std::cout << "Option pricing  (S0=" << S0 << ", K=" << K
            << ", r=" << r << ", sigma=" << sigma << ", T=" << T << ")\n";
  std::cout << "               Black-Scholes     Monte Carlo\n";
  std::cout << "  Call:         " << std::setw(10) << bs_c
            << "        " << std::setw(10) << mc_c << "\n";
  std::cout << "  Put:          " << std::setw(10) << bs_p
            << "        " << std::setw(10) << mc_p << "\n";

  return 0;
}
