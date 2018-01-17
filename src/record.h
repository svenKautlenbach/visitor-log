#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace record
{
	using minute_mark = uint16_t;
	constexpr uint16_t MINUTES_IN_24HR = 1440;

	struct Interval
	{
		minute_mark entry;
		minute_mark exit;
	};

	std::vector<Interval> parse(const std::string& recordsFile);
	bool isPresent(const Interval& data, minute_mark time);
}