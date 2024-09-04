#pragma once

#include <string>

namespace decode
{
	inline float decodeStatBoost(std::string encodedStat, float currentValue) 
	{
		int sign = encodedStat[0] == '+' ? 1 : -1;

		std::string numberPart = encodedStat.substr(1);

		if (numberPart.back() == '%')
		{
			currentValue = currentValue == 0 ? 1 : currentValue;
			numberPart.pop_back();
			float multiplier = std::stof(numberPart) / 100.0f;

			return sign * currentValue * multiplier;
		}
		else
		{
			float increase = std::stof(numberPart);
			
			return sign * increase;
		}
	}
}