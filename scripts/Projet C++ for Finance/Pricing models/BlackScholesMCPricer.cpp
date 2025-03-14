#include "BlackScholesMCPricer.h"

#include <stdexcept>

// Constructor
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)
    : _option(option), _initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility),
    _nb_paths(0), _sum_payoff(0.0), _sum_payoff_sq(0.0),asianpayoff(0) {}

// Getter for the number of paths
int BlackScholesMCPricer::getNbPaths() const {
    return _nb_paths;
}

// Generate nb_paths Monte Carlo paths
void BlackScholesMCPricer::generate(int nb_paths) {
    double T = _option->getExpiry(); // Option maturity
    double step;
    double Z;
    double St;
    double sumSt=0;
    std::vector<double> prices;
    if (_option->isAsianOption())
    {
        for (int j = 0; j < nb_paths; j++)
        {
            prices.clear();
            prices.push_back(_initial_price);
            for (int i = 0; i < _option->getTimeSteps().size(); i++) {
                step =T / _option->getTimeSteps().size();
                // Generate a standard normal random number
                Z = MT::getInstance()->rand_norm();

                // Simulate the asset price at maturity using Black-Scholes dynamics
                St = prices.back() * std::exp((_interest_rate - 0.5 * _volatility * _volatility) * step + _volatility * std::sqrt(step) * Z);
                prices.push_back(St);

            }
            // Compute the payoff of the option
            asianpayoff = _option->payoffPath(prices);

            _sum_payoff += asianpayoff;
            
            _sum_payoff_sq += asianpayoff * asianpayoff;
        }
        

        // Update the number of paths
        _nb_paths += nb_paths;
    }
    else
    {
        for (int i = 0; i < nb_paths; ++i) {
            // Generate a standard normal random number
            Z = MT::getInstance()->rand_norm();

            // Simulate the asset price at maturity using Black-Scholes dynamics
            St = _initial_price * std::exp((_interest_rate - 0.5 * _volatility * _volatility) * T + _volatility * std::sqrt(T) * Z);

            // Compute the payoff of the option
            double payoff = _option->payoff(St);

            // Update cumulative payoff and its square
            _sum_payoff += payoff;
            _sum_payoff_sq += payoff * payoff;
        }

        // Update the number of paths
        _nb_paths += nb_paths;
    }
    
}

// Operator () to return the current price estimate
double BlackScholesMCPricer::operator()() const {
    if (_nb_paths == 0) {
        throw std::runtime_error("Price is undefined: no paths have been generated.");
    }
    // Discounted average payoff
    return (_sum_payoff / _nb_paths) * std::exp(-_interest_rate * _option->getExpiry());

}

// Compute the 95% confidence interval
std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (_nb_paths == 0) {
        throw std::runtime_error("Confidence interval is undefined: no paths have been generated.");
    }

    // Mean and variance of the payoff
    double mean = _sum_payoff / _nb_paths;
    double variance = (_sum_payoff_sq / _nb_paths) - (mean * mean);

    // Standard error
    double std_error = std::sqrt(variance / _nb_paths);

    // Confidence interval (95% CI)
    double margin = 1.96 * std_error; // 1.96 corresponds to 95% confidence level
    double lower_bound = mean * std::exp(-_interest_rate * _option->getExpiry()) - margin;
    double upper_bound = mean * std::exp(-_interest_rate * _option->getExpiry()) + margin;

    return { lower_bound, upper_bound };
}