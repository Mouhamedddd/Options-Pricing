#include "EuropeanDigitalOption.h"
#include <stdexcept>

//construcot for euopean digital option
EuropeanDigitalOption::EuropeanDigitalOption(double _expiry, double _strike)
    : Option(_expiry), _strike(_strike) {
    if (_expiry < 0 || _strike < 0) {
        throw std::invalid_argument("Expiry and strike must be non-negative.");
    }
}
//ti return the strike
double EuropeanDigitalOption::getStrike() const
{
    return _strike;
}

