#include <fstream>
#include <sstream>

#include "utilities.h"

namespace utilities
{
	std::vector<std::string> split(const std::string& source, const std::string& delimiter)
	{
		std::vector<std::string> elements;
		std::stringstream sourceStream(source);

		std::string splitString;
		while (std::getline(sourceStream, splitString, delimiter.c_str()[0]))
			elements.push_back(splitString);

		return elements;
	}

	std::vector<std::string> getLines(const std::string& filePath)
	{
		std::ifstream in(filePath);

		if (in.bad() || !in.is_open())
			throw std::runtime_error("Cannot open a file " + filePath + ".");

		std::vector<std::string> ls;
		std::string l;
		while (std::getline(in, l))
			ls.push_back(l);

		in.close();

		return ls;
	}

	std::string minutesTo24H(uint16_t minutes)
	{
		auto h = minutes / 60;

		return std::to_string(h) + ":" + std::to_string(minutes - h * 60);
	}
}