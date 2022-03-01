#pragma once

#include <vector>
#include <string>

namespace Utility
{
	std::vector<std::string> SplitString(std::string& input, const std::string& delimiter);
	void StringToUpper(std::string& input);
}
