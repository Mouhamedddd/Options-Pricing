#pragma once
#include <iostream>
#include <vector>
#include "Option.h"

class AsianOption :public Option
{
private:
	std::vector<double> _timesteps;

protected:
	double getAveragePrice(const std::vector<double>& prices) const;

public:
	AsianOption(double, std::vector<double>);
	std::vector<double> getTimeSteps() const override;
	double payoffPath(const std::vector<double>& path) const override;
	bool isAsianOption() const override;


};

