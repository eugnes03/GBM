#include "black_scholes.hpp"
#include <cmath>

// Standard normal CDF via erfc
static double N(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

static void d1d2(double S, double K, double r, double sigma, double T,
                 double &d1, double &d2) {
    d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    d2 = d1 - sigma * std::sqrt(T);
}

double bs_call(double S, double K, double r, double sigma, double T) {
    double d1, d2;
    d1d2(S, K, r, sigma, T, d1, d2);
    return S * N(d1) - K * std::exp(-r * T) * N(d2);
}

double bs_put(double S, double K, double r, double sigma, double T) {
    double d1, d2;
    d1d2(S, K, r, sigma, T, d1, d2);
    return K * std::exp(-r * T) * N(-d2) - S * N(-d1);
}
