#pragma once
#include <string>
using namespace std;

class wildcard_matcher_t
{
public:
	static bool match(const char* src, const char *src_end, const char *pat, const char *pat_end)
	{
		while (src < src_end && pat < pat_end)
		{
			char cur_pat = *pat;
			switch (cur_pat)
			{
			case '?':
				++pat;
				++src;
				break;
			case '*':
			{
				const char *pat_next = pat + 1;
				while (pat_next < pat_end && *pat_next == cur_pat)
					++pat_next;

				for (const char * ptr = src; ptr <= src_end; ++ptr)
				{
					if (match(ptr, src_end, pat_next, pat_end))
						return true;
				}
				return false;
			}
			default:
				if (cur_pat == *src)
				{
					++src;
					++pat;
				}
				else
					return false;
				break;
			}
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