#pragma once
#include "AsianOption.h"
#include <vector>

//the derived class for asian option (call
class AsianCallOption : public AsianOption {
private:
    double strike;              // the strike price

public:
    // constructors
    AsianCallOption(double, const std::vector<double>&, double);
    AsianCallOption(const std::vector<double>&, double);

    //we override payoff method
    double payoff(double) const override;
    double getStrike()const override;
    optionType GetOptionType() const override;
};
