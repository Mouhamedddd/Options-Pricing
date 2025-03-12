#include "BlackScholesPricer.h"

//constructor
BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility) :option(option), asset_price(asset_price), interest_rate(interest_rate), volatility(volatility) {}

double BlackScholesPricer::operator()() const
{
	double d1;
	double d2;
	double Nd1;
	double Nd2;
	double Nminusd1;
	double Nminusd2;
	double T = option->getExpiry();
	double K = option->getStrike();

	double digitald2;
	double Ndigitald2;
	double Ndigitalminusd2;
	//we calculate d1 and d2
	//we find firmulas on google 

	d1 = (std::log(asset_price / K) + (interest_rate + 0.5 * volatility * volatility) * T) / (volatility * std::sqrt(T));
	d2 = d2 = d1 - volatility * std::sqrt(T);
	digitald2 = (std::log(asset_price / K) + (interest_rate - 0.5 * volatility * volatility) * T) / (volatility * std::sqrt(T));

	Nd1 = 0.5 * (1.0 + std::erf(d1 / std::sqrt(2.0)));
	Nd2 = 0.5 * (1.0 + std::erf(d2 / std::sqrt(2.0)));
	Nminusd1 = 0.5 * (1.0 + std::erf(-d1 / std::sqrt(2.0)));
	Nminusd2 = 0.5 * (1.0 + std::erf(-d2 / std::sqrt(2.0)));
	Ndigitald2 = 0.5 * (1.0 + std::erf(digitald2 / std::sqrt(2.0)));
	Ndigitalminusd2 = 0.5 * (1.0 + std::erf(-digitald2 / std::sqrt(2.0)));


	//we determine option type and calculate the correspondinf price
	if (option->GetOptionType() == optionType::call) {
		return asset_price * Nd1 - K * std::exp(-interest_rate * T) * Nd2;
	}
	else if (option->GetOptionType() == optionType::put) {
		return K * std::exp(-interest_rate * T) * Nminusd2 - asset_price * Nminusd1;
	}
	else if (option->GetOptionType() == optionType::digitalcall) {
		return std::exp(-interest_rate * T) * Ndigitald2;
	}
	else {
		return std::exp(-interest_rate * T) * Ndigitalminusd2;
	}

}
//method to caulcate delta using bs formulas
double BlackScholesPricer::delta()
{
	double d1;
	double Nd1;
	double T;
	double K;

	double digitald2;
	double ndigitald2;
	double PI = 3.14159265358979323846;  // value exacrt of pi



	T = option->getExpiry();
	K = option->getStrike();

	d1 = (std::log(asset_price / K) + (interest_rate + 0.5 * volatility * volatility) * T) / (volatility * std::sqrt(T));

	Nd1 = 0.5 * (1.0 + std::erf(d1 / std::sqrt(2.0)));

	digitald2 = digitald2 = (std::log(asset_price / K) + (interest_rate - 0.5 * volatility * volatility) * T) / (volatility * std::sqrt(T));
	ndigitald2 = (1.0 / std::sqrt(2 * PI)) * std::exp(-0.5 * digitald2 * digitald2);
	//determine delta based on option type
	if (option->GetOptionType() == optionType::call) {
		return Nd1;
	}
	else if (option->GetOptionType() == optionType::put) {
		return Nd1 - 1;
	}
	else if (option->GetOptionType() == optionType::digitalcall) {
		return (std::exp(-interest_rate * T) * ndigitald2) / (asset_price * volatility * std::sqrt(T));
	}
	else {
		return -(std::exp(-interest_rate * T) * ndigitald2) / (asset_price * volatility * std::sqrt(T));
	}
}