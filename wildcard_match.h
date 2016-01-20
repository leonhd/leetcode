#pragma once
#include <string>
#include <iostream>
using namespace std;

class wildcard_matcher_t
{
public:
	static bool match(const char* src, const char *src_end, const char *pat, const char *pat_end)
	{
		const char *sptr = nullptr, *pptr = nullptr;
		while (src < src_end)
		{
			std::cout << src << " => " << pat << std::endl;
			if (pat < pat_end && (*pat == '?' || *pat == *src))
			{
				++src;
				++pat;
			}
			else if (pat < pat_end && *pat == '*')
			{
				sptr = src + 1;
				pptr = pat++;
			}
			else if (pptr)
			{
				src = sptr;
				pat = pptr;
				pptr = nullptr;
				sptr = nullptr;
			}
			else
				return false;
		}

		while (pat < pat_end)
		{
			if (*pat != '*')
				return false;
			++pat;
		}

		return (src == src_end && pat == pat_end);
	}
};

#if 0
class Solution {
public:
	bool isMatch(string s, string p) {
		const char *src = s.c_str();
		const char *pat = p.c_str();
		return wildcard_matcher_t::match(src, src + s.length(), pat, pat + p.length());
	}
};
#endif