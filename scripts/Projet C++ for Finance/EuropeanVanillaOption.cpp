#include "EuropeanVanillaOption.h"
#include <stdexcept>

EuropeanVanillaOption::EuropeanVanillaOption(double _expiry, double _strike)
    : Option(_expiry), _strike(_strike) {
    if (_expiry < 0 || _strike < 0) {
        throw std::invalid_argument("Expiry and strike must be non-negative.");
    }
}

double EuropeanVanillaOption::getStrike() const
{
	return _strike;
}