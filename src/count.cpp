#include "count.h"

#include <iostream>

namespace count
{
	std::map<record::minute_mark, uint32_t>	createHistogram(const std::vector<record::Interval>& intervals)
	{
		std::map<record::minute_mark, uint32_t> vc;
		for (record::minute_mark i = 0; i < record::MINUTES_IN_24HR; i++)
		{
			size_t visitors = 0;
			for (const auto& r : intervals)
			{
				if (record::isPresent(r, i))
					visitors++;
			}

			vc.emplace(i, visitors);
		}

		return vc;
	}

	uint32_t findMaxAttendance(const std::map<record::minute_mark, uint32_t>& histogram)
	{
		auto m = std::max_element(histogram.cbegin(), histogram.cend(),
				[](const std::pair<record::minute_mark, uint32_t>& a, const std::pair<record::minute_mark, uint32_t>& b) {
					return a.second < b.second;
				});

		return m->second;
	}
}