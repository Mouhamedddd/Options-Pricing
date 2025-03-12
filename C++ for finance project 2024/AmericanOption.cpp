#include "AmericanOption.h"
//constructor for american option class
AmericanOption::AmericanOption(double _expiry):Option(_expiry){}
//returen true if its american option
bool AmericanOption::isAmericanOption() const
{
	return true;
}