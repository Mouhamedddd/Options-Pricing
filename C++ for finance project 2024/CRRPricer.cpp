#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

// constructor
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
    : _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate), _tree() {

    // we need to check for arbitrage: D < R < U
    checkArbitrageCondition(_down, _interest_rate, _up);

    // we need to check if it is a asian option
    if (_option->isAsianOption()) {
        throw std::invalid_argument("Asian options are not supported by CRRPricer.");
    }

    // initialize tree structure
    _tree.setDepth(depth);
    exercise_policy.setDepth(depth);
    computed = false;
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility) :_option(option), _depth(depth), _asset_price(asset_price) {

    double h = option->getExpiry() / depth;
    U = exp((r + volatility * volatility / 2) * h + volatility * sqrt(h)) - 1;
    D = exp((r + volatility * volatility / 2) * h - volatility * sqrt(h)) - 1;
    R = exp(r * h) - 1;

    checkArbitrageCondition(D, R, U);
    _tree.setDepth(depth);
    exercise_policy.setDepth(depth);
    computed = false;
}






void CRRPricer::checkArbitrageCondition(double down, double interest_rate, double up) const {
    if (!(down < interest_rate && interest_rate < up)) {
        std::cout<<"Arbitrage condition violated: down < interest_rate < up"<<std::endl;
    }
}


// method to compute the option tree
void CRRPricer::compute() {
    double q = (_interest_rate - _down) / (_up - _down);  // Risk-neutral probability

    // set values at maturity (level N)
    for (int i = 0; i <= _depth; ++i) {
        double S_N_i = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
        _tree.setNode(_depth, i, _option->payoff(S_N_i));
    }

    // backward induction
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double future_value = (q * _tree.getNode(n + 1, i + 1) + (1 - q) * _tree.getNode(n + 1, i)) / (1 + _interest_rate);
            _tree.setNode(n, i, future_value);
        }
    }

    computed = true;
}

// getter for H(n, i)
double CRRPricer::get(int n, int i) const {
    return _tree.getNode(n, i);
}

// opeerator overload to return the option price
double CRRPricer::operator()(bool closed_form) {
    if (!_option->isAmericanOption())
    {
        if (closed_form) {
            // Closed form calculation given in the subject 
            double q = (_interest_rate - _down) / (_up - _down);
            double result = 0.0;
            for (int i = 0; i <= _depth; ++i) {
                double S_N_i = _asset_price * std::pow(1 + _up, i) * std::pow(1 + _down, _depth - i);
                double h_S_N_i = _option->payoff(S_N_i);
                double binomial_coeff = std::tgamma(_depth + 1) / (std::tgamma(i + 1) * std::tgamma(_depth - i + 1));
                result += binomial_coeff * std::pow(q, i) * std::pow(1 - q, _depth - i) * h_S_N_i;
            }
            return result / std::pow(1 + _interest_rate, _depth);
        }
        else {
            
            
            if (!computed) {
                compute();
            }
            return get(0, 0);  // Return h
        }
    }
    else
    {
        double q = (R - D) / (U - D);
        
        // we perform a backward induction to compute option prices
        for (int i = 0; i <= _depth; ++i) {
            double S_N_i = _asset_price * pow(1 + U, i) * pow(1 + D, _depth - i);
            _tree.setNode(_depth, i, _option->payoff(S_N_i));
       
        }

        for (int n = _depth - 1; n >= 0; --n) {
            for (int i = 0; i <= n; ++i) {
                double priceatnode = _asset_price * pow(1 + U, i) * pow(1 + D, n - i);
                double intrinsic_value = _option->payoff(priceatnode);
                double continuation_value = (_tree.getNode(n + 1, i + 1) * q + _tree.getNode(n + 1, i) * (1 - q)) / (1 + R);
                
                double H_n_i = std::max(continuation_value, intrinsic_value);
                
                bool exercise = intrinsic_value > continuation_value;
                exercise_policy.setNode(n, i, exercise);
                _tree.setNode(n, i, H_n_i);
                
            }
        }

        return _tree.getNode(0, 0);
    }
    
}

bool CRRPricer::getExercise(int n, int i)
{
    return exercise_policy.getNode(n, i);
}


