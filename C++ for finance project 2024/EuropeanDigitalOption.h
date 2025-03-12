#pragma once
#include "Option.h"
#include "optionType.h"

class EuropeanDigitalOption :public Option {
private:
	double _strike;
public:
	EuropeanDigitalOption(double, double);
	double getStrike() const override;
	virtual optionType GetOptionType() const override =0;

};

