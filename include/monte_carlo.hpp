#pragma once

#include <vector>

// Price a European call/put via Monte Carlo using pre-simulated terminal values
double mc_call(const std::vector<std::vector<double>> &paths, double K, double r, double T);
double mc_put(const std::vector<std::vector<double>> &paths, double K, double r, double T);
