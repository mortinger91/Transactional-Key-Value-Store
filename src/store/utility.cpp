#include "utility.h"

#include <algorithm>
#include <string.h>

namespace Utility
{
	std::vector<std::string> SplitString(const std::string& input, const std::string& delimiter)
	{
		std::string inputCopy = input;
		std::vector<std::string> output;
		char *pch;
		pch = strtok(&inputCopy[0], delimiter.c_str());
		while (pch != NULL)
		{
			output.push_back(pch);
			pch = strtok(NULL, delimiter.c_str());
		}
		return output;
	}

	void StringToUpper(std::string& input)
	{
		std::transform(input.begin(), input.end(), input.begin(), toupper);
	}
}
