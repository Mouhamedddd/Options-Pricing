#include "CallOption.h"
#include "EuropeanVanillaOption.h"

CallOption::CallOption(double _expiry, double _strike) :EuropeanVanillaOption(_expiry, _strike) {}

double CallOption::payoff(double z) const
{
	if (z >= getStrike())
	{
		return z - getStrike();
	}
	else
	{
		return 0.0;
	}

};

optionType CallOption::GetOptionType() const
{
	return optionType::call;
}