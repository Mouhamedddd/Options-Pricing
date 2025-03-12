#pragma once
#include <iostream>
#include <vector>
#include "AsianOption.h"

class AsianPutOption : public AsianOption {
private:
    double strike;

public:
    AsianPutOption(double, const std::vector<double>&, double);
    AsianPutOption(const std::vector<double>&, double);

    double payoff(double) const override;
    double getStrike()const override;
    optionType GetOptionType() const override;
};