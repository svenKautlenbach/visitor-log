#pragma once

#include <cstdint>
#include <map>

#include "record.h"

namespace statistics
{
	using histogram = std::map<record::minute_mark, uint32_t>;
	using attendance = std::vector<std::pair<uint32_t, record::Interval>>;

	histogram createHistogram(const std::vector<record::Interval>& intervals);
	uint32_t findMaxAttendance(const histogram& data);
	attendance aggregate(const histogram& data);
}