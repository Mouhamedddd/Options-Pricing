#include "PutOption.h"
#include "EuropeanVanillaOption.h"


PutOption::PutOption(double _expiry, double _strike) :EuropeanVanillaOption(_expiry, _strike) {}
//return payoff for putoption
double PutOption::payoff(double z) const
{
	if (z <= getStrike())
	{
		return getStrike() - z;
	}
	else
	{
		return 0.0;
	}

};
//fgetter for type
optionType PutOption::GetOptionType() const
{
	return optionType::put;
}