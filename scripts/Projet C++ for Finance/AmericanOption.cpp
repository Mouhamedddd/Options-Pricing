#include "AmericanOption.h"

AmericanOption::AmericanOption(double _expiry):Option(_expiry){}
bool AmericanOption::isAmericanOption() const
{
	return true;
}