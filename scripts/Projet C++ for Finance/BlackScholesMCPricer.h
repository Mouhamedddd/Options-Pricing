#pragma once
#include <vector>
#include <cmath>
#include <stdexcept>
#include "Option.h"
#include "MT.h"
#include "Option.h"

class BlackScholesMCPricer {
private:
    Option* _option;           // Pointer to the option being priced
    double _initial_price;     // Initial price of the underlying asset
    double _interest_rate;     // Risk-free interest rate
    double _volatility;        // Volatility of the underlying asset
    int _nb_paths;             // Number of paths generated so far
    double _sum_payoff;        // Cumulative payoff for all paths
    double _sum_payoff_sq;     // Cumulative squared payoff for variance calculation
    double asianpayoff;

public:
    // Constructor
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

    // Getter for the number of paths
    int getNbPaths() const;

    // Generate nb_paths Monte Carlo paths and update the current price estimate
    void generate(int nb_paths);

    // Operator to return the current price estimate
    double operator()() const;

    // Compute the 95% confidence interval of the price
    std::vector<double> confidenceInterval() const;
};