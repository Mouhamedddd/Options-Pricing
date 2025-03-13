#pragma once
#include "AmericanOption.h"

class AmericanPutOption :public AmericanOption
{
	private:
		double _strike;
	public:
		AmericanPutOption(double, double);
		double payoff(double) const override;
		double getStrike()const override;
		optionType GetOptionType() const override;
};

