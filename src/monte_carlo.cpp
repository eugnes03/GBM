#include "monte_carlo.hpp"
#include <algorithm>
#include <cmath>

// Terminal value of each path is the last element
static std::vector<double> terminal_values(const std::vector<std::vector<double>> &paths) {
    std::vector<double> vals;
    vals.reserve(paths.size());
    for (const auto &p : paths)
        vals.push_back(p.back());
    return vals;
}

double mc_call(const std::vector<std::vector<double>> &paths, double K, double r, double T) {
    auto ST = terminal_values(paths);
    double sum = 0.0;
    for (double s : ST)
        sum += std::max(s - K, 0.0);
    return std::exp(-r * T) * sum / static_cast<double>(ST.size());
}

double mc_put(const std::vector<std::vector<double>> &paths, double K, double r, double T) {
    auto ST = terminal_values(paths);
    double sum = 0.0;
    for (double s : ST)
        sum += std::max(K - s, 0.0);
    return std::exp(-r * T) * sum / static_cast<double>(ST.size());
}
