#include "BlackScholesMCPricer.h"

#include <stdexcept>

//the cstructor
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)
    : _option(option), _initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility),
    _nb_paths(0), _sum_payoff(0.0), _sum_payoff_sq(0.0),asianpayoff(0) {}

// getter to have nber of path
int BlackScholesMCPricer::getNbPaths() const {
    return _nb_paths;
}

// to generate nb mc path
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
                // to ggenerate standard normal random numbers
                Z = MT::getInstance()->rand_norm();

                // to simulate the asset price at maturity using BS 
                St = prices.back() * std::exp((_interest_rate - 0.5 * _volatility * _volatility) * step + _volatility * std::sqrt(step) * Z);
                prices.push_back(St);

            }
            // we compute payoff of the option
            asianpayoff = _option->payoffPath(prices);

            _sum_payoff += asianpayoff;
            
            _sum_payoff_sq += asianpayoff * asianpayoff;
        }
        

        // to update the number of path
        _nb_paths += nb_paths;
    }
    else
    {
        for (int i = 0; i < nb_paths; ++i) {
           
            Z = MT::getInstance()->rand_norm();

            
            St = _initial_price * std::exp((_interest_rate - 0.5 * _volatility * _volatility) * T + _volatility * std::sqrt(T) * Z);

            // it computes the payoff of the option
            double payoff = _option->payoff(St);

            // we update cimulative payoff
            _sum_payoff += payoff;
            _sum_payoff_sq += payoff * payoff;
        }

        // the we updte nb path
        _nb_paths += nb_paths;
    }
    
}

//  to return the current price estimate::
double BlackScholesMCPricer::operator()() const {
    if (_nb_paths == 0) {
        throw std::runtime_error("Price is undefined: no paths have been generated.");
    }
    //discounted average payoff
    return (_sum_payoff / _nb_paths) * std::exp(-_interest_rate * _option->getExpiry());

}

//to cpute 95% cfidence interval
std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (_nb_paths == 0) {
        throw std::runtime_error("Confidence interval is undefined: no paths have been generated.");
    }

    // Mean andd variance
    double mean = _sum_payoff / _nb_paths;
    double variance = (_sum_payoff_sq / _nb_paths) - (mean * mean);

    // error
    double std_error = std::sqrt(variance / _nb_paths);

    
    double margin = 1.96 * std_error; // well know for gaussia
    double lower_bound = mean * std::exp(-_interest_rate * _option->getExpiry()) - margin;
    double upper_bound = mean * std::exp(-_interest_rate * _option->getExpiry()) + margin;

    return { lower_bound, upper_bound };
}