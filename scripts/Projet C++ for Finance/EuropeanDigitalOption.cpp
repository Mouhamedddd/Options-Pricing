#include "EuropeanDigitalOption.h"
#include <stdexcept>

EuropeanDigitalOption::EuropeanDigitalOption(double _expiry, double _strike)
    : Option(_expiry), _strike(_strike) {
    if (_expiry < 0 || _strike < 0) {
        throw std::invalid_argument("Expiry and strike must be non-negative.");
    }
}

double EuropeanDigitalOption::getStrike() const
{
    return _strike;
}

