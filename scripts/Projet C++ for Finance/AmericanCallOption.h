#pragma once
#include "AmericanOption.h"

class AmericanCallOption:public AmericanOption
{
	private:
		double _strike;
	public:
		AmericanCallOption(double,double);
		double payoff(double) const override;
		double getStrike()const override;
		optionType GetOptionType() const override;
};

