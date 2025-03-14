#include "Option.h"

Option::Option(double _expiry) :_expiry(_expiry) {};

double Option::getExpiry() const {
	return _expiry;
}


double Option::payoffPath(const std::vector<double>& path) const
{
	return payoff(path.back());
}

bool Option::isAsianOption() const
{
	return false;
}

bool Option::isAmericanOption() const
{
	return false;
}