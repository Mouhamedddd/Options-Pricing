#include "AmericanPutOption.h"


//construvtor
AmericanPutOption::AmericanPutOption(double _expiry, double _strike) :AmericanOption(_expiry), _strike(_strike) {}


//fction to compute the payoff of put american option
double AmericanPutOption::payoff(double _assetprice) const
{
	return std::max(_strike- _assetprice, 0.0);
}
//retun strike price of the option
double  AmericanPutOption::getStrike()const
{
	return _strike;
}
//to identify americanoption as put
optionType  AmericanPutOption::GetOptionType() const
{
	return optionType::americanput;
}