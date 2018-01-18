#include "statistics.h"

namespace statistics
{
	histogram createHistogram(const std::vector<record::Interval>& intervals)
	{
		histogram hg;
		for (record::minute_mark i = 0; i < record::MINUTES_IN_24HR; i++)
		{
			size_t visitors = 0;
			for (const auto& r : intervals)
			{
				if (record::isPresent(r, i))
					visitors++;
			}

			hg.emplace(i, visitors);
		}

		return hg;
	}

	uint32_t findMaxAttendance(const histogram& data)
	{
		auto m = std::max_element(data.cbegin(), data.cend(),
				[](const std::pair<record::minute_mark, uint32_t>& a, const std::pair<record::minute_mark, uint32_t>& b) {
					return a.second < b.second;
				});

		return m->second;
	}

	attendance aggregate(const histogram& data)
	{
		attendance a;

		auto dataIter = data.cbegin();
		auto end = data.cend();
		while (dataIter != end)
		{
			auto visitors = dataIter->second;
			auto m = std::find_if(dataIter, end, [&](const std::pair<record::minute_mark, uint32_t>& d) { return d.second != visitors; });
			a.emplace_back(visitors, record::Interval{dataIter->first, std::prev(m)->first});
			dataIter = m;
		}

		return a;
	}
}