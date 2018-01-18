#pragma once

#include <string>
#include <vector>

namespace utilities
{
	std::vector<std::string> split(const std::string& source, const std::string& delimiter);
	std::vector<std::string> getLines(const std::string& filePath);
	std::string minutesTo24H(uint16_t minutes);
}