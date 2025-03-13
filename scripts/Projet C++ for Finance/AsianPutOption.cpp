#include "AsianPutOption.h"
#include <algorithm> // for std::max
#include <numeric>   // for std::accumulate

// Constructor
AsianPutOption::AsianPutOption(double _expiry, const std::vector<double>& _timesteps, double _strike) : AsianOption(_expiry, _timesteps), strike(_strike) {}
AsianPutOption::AsianPutOption(const std::vector<double>& _timesteps, double _strike) : AsianOption(1, _timesteps), strike(_strike) {}

// Payoff implementation
double AsianPutOption::payoff(double averagePrice) const {
    return std::max(strike - averagePrice, 0.0); // Put option payoff: max(strike - averagePrice, 0)
}
double  AsianPutOption::getStrike()const
{
	return strike;
}
optionType  AsianPutOption::GetOptionType() const
{
	return optionType::asianput;
}