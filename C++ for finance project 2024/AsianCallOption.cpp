#include "AsianCallOption.h"
#include <algorithm> // for std::max
#include <numeric>   // for std::accumulate

//we make different constructors 
AsianCallOption::AsianCallOption(double _expiry, const std::vector<double>& _timesteps, double _strike): AsianOption(_expiry,_timesteps), strike(_strike) {}
AsianCallOption::AsianCallOption(const std::vector<double>& _timesteps, double _strike) : AsianOption(_timesteps.back(), _timesteps), strike(_strike) {}

//payoff implmentation for asian call option
double AsianCallOption::payoff(double averagePrice) const {
    return std::max(averagePrice - strike, 0.0); // the call option payoff: max(averagePrice - strike, 0)
}
//gett for the strike price option
double  AsianCallOption::getStrike()const
{
	return strike;
}
//reutn type of option
optionType  AsianCallOption::GetOptionType() const
{
	return optionType::asiancall;
}