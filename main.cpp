#include <iostream>

#include "record.h"
#include "statistics.h"
#include "utilities.h"

namespace
{
	void printUsage(const std::string& me)
	{
		std::cout << "Usage: " << me << " <record file>" << std::endl;
	}

	void print1b(const statistics::attendance& intervals, uint32_t visitors)
	{
		std::cout << "Periods where the maximum attendance of " << visitors << " occurred." << std::endl;
		for (const auto& i : intervals)
			if (i.first == visitors)
				std::cout << utilities::minutesTo24H(i.second.entry) << "-"
						  << utilities::minutesTo24H(i.second.exit) << std::endl;
	}

	void print1c(const statistics::attendance& intervals)
	{
		std::cout << "Periods where attendance remained static." << std::endl;
		for (const auto& i : intervals)
			std::cout << utilities::minutesTo24H(i.second.entry) << "-" << utilities::minutesTo24H(i.second.exit)
					  << ";" << i.first << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printUsage(std::string(argv[0]));
		exit(1);
	}

	try
	{
		const auto& records = record::parse(std::string(argv[1]));
		const auto& histogram = statistics::createHistogram(records);
		const auto maxAttendance = statistics::findMaxAttendance(histogram);
		for (const auto& u : histogram)
		{
			std::cout << utilities::minutesTo24H(u.first) << " " << u.second << std::endl;
		}
		const auto& attendanceIntervals = statistics::aggregate(histogram);
		print1b(attendanceIntervals, maxAttendance);
		print1c(attendanceIntervals);
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "An exception was caught - " << e.what() << std::endl
				  << "Tool terminates." << std::endl;
		exit(2);
	}
	catch (...)
	{
		std::cerr << "Unknown object was caught. Tool terminates." << std::endl;
		exit(3);
	}

	return 0;
}