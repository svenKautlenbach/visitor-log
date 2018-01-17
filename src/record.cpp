#include "record.h"

#include <fstream>

#include "utilities.h"

namespace
{
	record::minute_mark recordEntryToMinuteMark(const std::string& entry)
	{
		auto timeSplit = utilities::split(entry, ":");
		auto hm = std::stoul(timeSplit.at(0), nullptr, 10) * 60;

		return hm + std::stoul(timeSplit.at(1), nullptr, 10);
	}

	record::Interval convertToInterval(const std::string& line)
	{
		const auto& t = utilities::split(line, ",");
		return {recordEntryToMinuteMark(t.at(0)), recordEntryToMinuteMark(t.at(1))};
	}
}

namespace record
{
	std::vector<Interval> parse(const std::string& recordsFile)
	{
		std::vector<Interval> intervals;

		const auto& ls = utilities::getLines(recordsFile);
		for (const auto& l : ls)
			intervals.push_back(convertToInterval(l));

		return intervals;
	}

	bool isPresent(const Interval& data, minute_mark time)
	{
		return time >= data.entry && time <= data.exit;
	}
}