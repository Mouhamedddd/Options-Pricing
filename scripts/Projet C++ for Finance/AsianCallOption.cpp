#include "AsianCallOption.h"
#include <algorithm> // for std::max
#include <numeric>   // for std::accumulate

// Constructor
AsianCallOption::AsianCallOption(double _expiry, const std::vector<double>& _timesteps, double _strike): AsianOption(_expiry,_timesteps), strike(_strike) {}
AsianCallOption::AsianCallOption(const std::vector<double>& _timesteps, double _strike) : AsianOption(1, _timesteps), strike(_strike) {}

// Payoff implementation for Asian Call Option
double AsianCallOption::payoff(double averagePrice) const {
    return std::max(averagePrice - strike, 0.0); // Call option payoff: max(averagePrice - strike, 0)
}

double  AsianCallOption::getStrike()const
{
	return strike;
}
optionType  AsianCallOption::GetOptionType() const
{
	return optionType::americancall;
}