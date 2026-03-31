#pragma once

// European option prices under Black-Scholes
double bs_call(double S, double K, double r, double sigma, double T);
double bs_put(double S, double K, double r, double sigma, double T);
