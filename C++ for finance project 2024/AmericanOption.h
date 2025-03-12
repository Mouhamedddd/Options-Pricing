#pragma once
#include "Option.h"
#include "OptionType.h"

class AmericanOption: public Option
{
	private:
		
	public:
		AmericanOption(double);
		bool isAmericanOption() const override;

};

