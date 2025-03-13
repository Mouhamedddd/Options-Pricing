#include "AmericanCallOption.h"

AmericanCallOption::AmericanCallOption(double _expiry, double _strike):AmericanOption(_expiry),_strike(_strike){}

double AmericanCallOption::payoff(double _assetprice) const
{
	return std::max(_assetprice - _strike, 0.0);
}

double  AmericanCallOption::getStrike()const
{
	return _strike;
}
optionType  AmericanCallOption::GetOptionType() const
{
	return optionType::americancall;
}