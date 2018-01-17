#include <iostream>

#include "count.h"
#include "record.h"

namespace
{
	void printUsage(const std::string& me)
	{
		std::cout << "Usage: " << me << " <record file>" << std::endl;
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
		/*for (const auto& r : records)
			std::cout << "Entry - " << r.entry << " Exit - " << r.exit << std::endl;
		*/
		const auto& visitCount = count::createHistogram(records);

		for (const auto& v : visitCount)
		{
			std::cout << v.first << " " << v.second << std::endl;
		}

		std::cout << count::findMaxAttendance(visitCount) << std::endl;

		uint32_t huhuu = visitCount.begin()->second;
		auto jejee = std::find_if_not(visitCount.cbegin(), visitCount.cend(), [&](const std::pair<record::minute_mark , uint32_t >& a){return a.second == huhuu;});
		std::cout << jejee->first << " " << jejee->second << std::endl;
		huhuu = jejee->second;
		auto jejeee = std::find_if_not(jejee, visitCount.cend(), [&](const std::pair<record::minute_mark , uint32_t >& a){return a.second == huhuu;});
		std::cout << jejeee->first << " " << jejeee->second << std::endl;

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