#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double _expiry, double _strike) :AmericanOption(_expiry), _strike(_strike) {}

double AmericanPutOption::payoff(double _assetprice) const
{
	return std::max(_strike- _assetprice, 0.0);
}

double  AmericanPutOption::getStrike()const
{
	return _strike;
}
optionType  AmericanPutOption::GetOptionType() const
{
	return optionType::americanput;
}