#pragma once
#include <vector>
#include <cmath>
#include <stdexcept>
#include "Option.h"
#include "MT.h"
#include "Option.h"

class BlackScholesMCPricer {
private:
    Option* _option;           
    double _initial_price;     
    double _interest_rate;     
    double _volatility;        
    int _nb_paths;            
    double _sum_payoff;        
    double _sum_payoff_sq;    
    double asianpayoff;

public:
    // constructor
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);

    // getter to get nb oif path
    int getNbPaths() const;

    // it is made to generate nb_paths (Monte Carlo paths) and update the current price estimate
    void generate(int nb_paths);

    // to return current price estimatee
    double operator()() const;

    // we compute 95% confidence interval of the price
    std::vector<double> confidenceInterval() const;
};