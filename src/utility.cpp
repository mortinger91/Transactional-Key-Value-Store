#include "utility.h"

#include <algorithm> 

namespace Utility
{
	std::vector<std::string> SplitString(std::string& input, const std::string& delimiter)
	{
		std::vector<std::string> output;
		char *pch;
		pch = strtok(&input[0], delimiter.c_str());
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
