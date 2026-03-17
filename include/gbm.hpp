#pragma once

#include <vector>
#include <random>

// Simulate one GBM path
std::vector<double> simulate_gbm(
    int steps,
    double dt,
    double S0,
    double mu,
    double sigma,
    std::mt19937 &gen
);

// Simulate multiple GBM paths
std::vector<std::vector<double>> simulate_many(
    int n_paths,
    int steps,
    double dt,
    double S0,
    double mu,
    double sigma,
    std::mt19937 &gen
);
