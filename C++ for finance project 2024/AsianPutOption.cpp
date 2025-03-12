#include "AsianPutOption.h"
#include <algorithm> // for std::max
#include <numeric>   // for std::accumulate

// two constructors
AsianPutOption::AsianPutOption(double _expiry, const std::vector<double>& _timesteps, double _strike) : AsianOption(_expiry, _timesteps), strike(_strike) {}
AsianPutOption::AsianPutOption(const std::vector<double>& _timesteps, double _strike) : AsianOption(_timesteps.back(), _timesteps), strike(_strike) {}

// payoff implementation for asian put
double AsianPutOption::payoff(double averagePrice) const {
    return std::max(strike - averagePrice, 0.0); // puut option payoff: max(strike - averagePrice, 0)
}

//gett for strike price
double  AsianPutOption::getStrike()const
{
	return strike;
}

//returns the type of the option
optionType  AsianPutOption::GetOptionType() const
{
	return optionType::asianput;
}