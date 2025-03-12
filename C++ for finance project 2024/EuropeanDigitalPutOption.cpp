#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double _expiry, double _strike) :EuropeanDigitalOption(_expiry, _strike) {}
//payoff
double EuropeanDigitalPutOption::payoff(double z) const
{
	if (z <= getStrike())
	{
		return 1.0;
	}
	else
	{
		return 0.0;
	}

};
//type of the option
optionType EuropeanDigitalPutOption::GetOptionType() const
{
	return optionType::digitalput;
}