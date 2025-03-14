#pragma once
#include "Option.h"
#include "optionType.h"

class EuropeanVanillaOption :public Option {
private:
	double _strike;
public:
	EuropeanVanillaOption(double, double);
	double getStrike() const override;
	optionType GetOptionType() const override =0;

};

