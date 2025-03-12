#include "AsianOption.h"
#include <iostream>
#include <vector>
#include <numeric>

AsianOption::AsianOption(double _expiry, std::vector<double> _timesteps) :Option(_expiry), _timesteps(_timesteps) {}
//reurn the vector of time steps associated with the otpion
std::vector<double> AsianOption::getTimeSteps() const
{
	return _timesteps;
}
//compite avrage price from a vctor of price
double AsianOption::getAveragePrice(const std::vector<double>& prices) const {
	return std::accumulate(prices.begin(), prices.end(), 0.0) / prices.size();
}


//calculates the payoff of option bsed on a given path prices
double AsianOption::payoffPath(const std::vector<double>& path) const
{
	double averagePrice = getAveragePrice(path);
	
	return payoff(averagePrice);
}


//always return true of its asian otpion
bool AsianOption::isAsianOption() const
{
	return true;
}

