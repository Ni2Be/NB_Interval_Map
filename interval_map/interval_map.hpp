#pragma once
#include <map>
#include <limits>

#ifdef IMPLEMENTATION_DEBUG
#include <iostream>
#include <string>
#endif
/*
Interval Map

Assosiates intervals (from K min to K max) with given values (V).
like:
K-min                              K-max
  |                                  |
  |------V1------|--V2--|-----V3-----|

Must be initialized with a value that represents the whole 
interval (std::numeric_limits<K>::lowest() to std::numeric_limits<K>::max()).

assing(K begin, K end, V val) will assing the value to the interval (excluding end).

assing_max(V val) is used to reassing the max value.

reset(V val) assings val to the whole map
*/
template<typename K, typename V>
class interval_map
{
public:
	std::map<K, V> m_map;

	interval_map(V const& val)
	{
		m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	void assign(K const& begin, K const& end, V const& val) {
		if (!(begin < end))
			return;

		auto upper = --m_map.upper_bound(end);
		auto oldVal = upper->second;
		if (oldVal == val)
			upper++;
		else
			upper = m_map.emplace_hint(upper, std::make_pair(end, oldVal));

		auto lower = m_map.lower_bound(begin);
		if (lower->first == begin)
		{
			lower = m_map.erase(lower);
			if (!((--lower)->second == val))
				lower = m_map.emplace_hint(lower, std::make_pair(begin, val));
		}
		else
		{
			lower = m_map.emplace_hint(lower, std::make_pair(begin, val));
			if (!((--lower)->second == val))
				lower++;
		}
		m_map.erase(++lower, upper);
	}


	void assign_max(V const& val) 
	{
		auto last = --m_map.end();
		if ((last)->first == std::numeric_limits<K>::max())
		{
			last = m_map.erase(last);
			if((--last)->second != val)
				m_map.emplace_hint(m_map.end(), std::make_pair(std::numeric_limits<K>::max(), val));
		}
		else
		{
			if (last->second == val)
				return;
			else
				m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::max(), val));
		}
	}

	void reset(V const& val)
	{
		m_map.clear();
		m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}
#ifdef IMPLEMENTATION_DEBUG
	bool check_ranges()
	{
		auto prev = m_map.begin();
		for (auto next = ++m_map.begin(); next != m_map.end(); prev++, next++)
			if (prev->second == next->second)
				return false;
		return true;
	}
	void print_ranges()
	{
		for (auto i : m_map)
			std::cout << "key: " << i.first << ", " << i.second << "\n";
	}
#endif
	V const& operator[](K const& key) const
	{
		return (--m_map.upper_bound(key))->second;
	}
};
