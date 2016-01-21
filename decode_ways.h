#pragma once
#include <string>
#include <stdint.h>
using namespace std;

class str_decode_counter_t
{
public:
	static int32_t calc(const string & str)
	{
		if (str.length() == 0 || str[0] == '0')
			return 0;

		int32_t p2 = 1, p1 = 1;
		for (int32_t i = 1; i < str.length(); ++i)
		{
			int32_t cur = 0;
			if (str[i] != '0')
				cur += p1;

			int32_t tmp = (str[i - 1] - '0') * 10 + str[i] - '0';
			if (tmp >= 10 && tmp <= 26)
				cur += p2;

			p2 = p1;
			p1 = cur;
		}

		return p1;
	}
};

#if 0
class Solution {
public:
	int numDecodings(string s) {
		return str_decode_counter_t::calc(s);
	}
}; 
#endif