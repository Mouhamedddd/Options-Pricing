#pragma once
#include "EuropeanDigitalOption.h"
#include "optionType.h"

class EuropeanDigitalCallOption :public EuropeanDigitalOption {
	public:
		EuropeanDigitalCallOption(double, double);
		double payoff(double) const override;
		optionType GetOptionType() const override;

};

