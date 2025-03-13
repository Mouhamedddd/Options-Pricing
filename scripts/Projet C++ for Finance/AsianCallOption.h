#pragma once
#include "AsianOption.h"
#include <vector>

// Derived class for Asian call option
class AsianCallOption : public AsianOption {
private:
    double strike;              // Strike price

public:
    // Constructor
    AsianCallOption(double, const std::vector<double>&, double);
    AsianCallOption(const std::vector<double>&, double);

    // Override payoff() method
    double payoff(double) const override;
    double getStrike()const override;
    optionType GetOptionType() const override;
};
