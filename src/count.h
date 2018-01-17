#pragma once

#include <cstdint>
#include <map>

#include "record.h"

namespace count
{
	std::map<record::minute_mark, uint32_t>	createHistogram(const std::vector<record::Interval>& intervals);
	uint32_t findMaxAttendance(const std::map<record::minute_mark, uint32_t>& histogram);
}