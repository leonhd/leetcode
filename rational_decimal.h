#pragma once
#include <stdint.h>
#include <algorithm>
#include <string>

class rational_decimal_calculator_t
{
	static int32_t gcd(int32_t a, int32_t b)
	{
		int32_t c = 0;
		do
		{
			if (a < b)
				std::swap(a, b);

			c = a % b;

			a = b;
			b = c;
		} while (c);

		return a;
	}
public:
	static std::string calc(int32_t numerator, int32_t denominator)
	{
		if (numerator == 0)
			return "0";

		int32_t divisor = gcd(numerator, denominator);
		numerator /= divisor;
		denominator /= divisor;

		int32_t tmp = denominator;
		int32_t count_2 = 0, count_5 = 0;
		while (!(tmp & 1))
		{
			tmp >>= 1;
			++count_2;
		}
		while (tmp % 5 == 0)
		{
			tmp /= 5;
			++count_5;
		}

		int32_t integer_part = numerator / denominator;
		numerator %= denominator;
		char buf[1024];
		if (numerator == 0)
		{
			sprintf_s(buf, "%d\0", integer_part);
		}
		else
		{
			int32_t decimal_part = -1;
			if (tmp == 1)
			{
				//get integer representation of decimal part
				for (int32_t i = count_2; i < count_5; ++i)
					numerator <<= 1;
				for (int32_t i = count_5; i < count_2; ++i)
					numerator *= 5;

				decimal_part = numerator;
			}
			else
			{
				int32_t init_val = 9;
				while (init_val % denominator)
				{
					init_val *= 10;
					init_val += 9;
				}

				decimal_part = init_val / denominator;
			}

			//convert decimal part to string
			char buf1[128];
			sprintf_s(buf1, "%d\0", decimal_part);

			//convert integer part plus . to string
			sprintf_s(buf, "%d.\0", integer_part);

			int32_t buf_str_len = strlen(buf);
			if (tmp > 1)
				buf[buf_str_len++] = '(';
			
			//align decimal part with denominator
			int32_t decimal_width = strlen(buf1);
			int32_t width = std::max<int32_t>(count_2, count_5);
			for (int32_t i = decimal_width; i < width; ++i)
			{
				buf[buf_str_len++] = '0';
			}

			//append decimal part to integer part
			strcpy(buf + buf_str_len, buf1);
			buf_str_len += decimal_width;

			if (tmp > 1)
			{
				buf[buf_str_len++] = ')';
				buf[buf_str_len] = '\0';
			}
		}

		return buf;
	}
};

#if 0
class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {

	}
}; 
#endif