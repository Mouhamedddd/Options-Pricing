#include "AmericanCallOption.h"



//Intalise an american call option with a given expiry a,d strike price
AmericanCallOption::AmericanCallOption(double _expiry, double _strike):AmericanOption(_expiry),_strike(_strike){}


//compute the payoff
double AmericanCallOption::payoff(double _assetprice) const
{
	return std::max(_assetprice - _strike, 0.0);
}
//retun the strike price of the option
double  AmericanCallOption::getStrike()const
{
	return _strike;
}
//in this case, it identifies as american call option
optionType  AmericanCallOption::GetOptionType() const
{
	return optionType::americancall;
}