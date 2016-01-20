#pragma once
#include <stdint.h>
#include <limits.h>

class integer_div_t
{
public:
	static int32_t calc(int64_t dividend, int64_t divisor)
	{
		if (dividend == 0)
			return 0;

		if (divisor == 0)
			return INT_MAX;

		bool neg_divisor = divisor < 0;
		bool neg_dividend = dividend < 0;
		bool neg_ret = neg_dividend != neg_divisor;

		if (neg_divisor)
			divisor = -divisor;
		if (neg_dividend)
			dividend = -dividend;

		if (dividend < divisor)
			return 0;

		int64_t tmp = dividend, result = 0;
		int64_t tmp_div = divisor;
		int32_t shift = 0;
		while (tmp_div <= tmp)
		{
			tmp_div <<= 1;
			++shift;
		}
		--shift;
		tmp_div >>= 1;
		result += ((int64_t)1 << shift);
		tmp -= tmp_div;

		while (tmp >= divisor)
		{
			while (tmp_div > tmp)
			{
				tmp_div >>= 1;
				--shift;
			}

			tmp -= tmp_div;
			result += ((int64_t)1 << shift);
		}

		if (neg_ret)
			result = -result;

		if (result > INT_MAX || result < INT_MIN)
			result = INT_MAX;

		return result;
	}
};

#if 0
class Solution {
public:
	int divide(int dividend, int divisor) {
		return integer_div_t::calc(dividend, divisor);
	}
}; 
#endif