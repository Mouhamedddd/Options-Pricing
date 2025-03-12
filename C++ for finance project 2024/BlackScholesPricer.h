#pragma once
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#include <iostream>



class BlackScholesPricer
{
private:
	Option* option;
	double asset_price;
	double interest_rate;
	double volatility;
public:
	BlackScholesPricer(Option*, double, double, double);
	friend class EuropeanVanillaOption;
	double operator()() const;
	double delta();
};

