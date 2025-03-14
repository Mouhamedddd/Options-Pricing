#include "AsianOption.h"
#include <iostream>
#include <vector>
#include <numeric>

AsianOption::AsianOption(double _expiry, std::vector<double> _timesteps) :Option(_expiry), _timesteps(_timesteps) {}

std::vector<double> AsianOption::getTimeSteps() const
{
	return _timesteps;
}

double AsianOption::getAveragePrice(const std::vector<double>& prices) const {
	return std::accumulate(prices.begin(), prices.end(), 0.0) / prices.size();
}

double AsianOption::payoffPath(const std::vector<double>& path) const
{
	double averagePrice = getAveragePrice(path);
	
	return payoff(averagePrice);
}



bool AsianOption::isAsianOption() const
{
	return true;
}

