#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double _expiry, double _strike) :EuropeanDigitalOption(_expiry, _strike) {}

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

optionType EuropeanDigitalPutOption::GetOptionType() const
{
	return optionType::digitalput;
}