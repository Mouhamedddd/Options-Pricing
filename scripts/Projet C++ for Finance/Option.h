#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "OptionType.h"

class Option
{
private:
	double _expiry;
public:
	Option(double);
	double getExpiry() const;
	virtual double payoff(double) const = 0;
	virtual double getStrike()const = 0;
	virtual optionType GetOptionType() const = 0;
	virtual double payoffPath(const std::vector<double>& path) const;
	virtual bool isAsianOption() const;
	virtual bool isAmericanOption() const;
	virtual std::vector<double> getTimeSteps() const
	{
		std::vector<double> ts;
		return ts;
	}
};

