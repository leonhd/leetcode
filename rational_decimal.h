#pragma once
#include <stdint.h>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class rational_decimal_calculator_t
{
	static int32_t gcd(int64_t a, int64_t b)
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
	static std::string calc(int64_t numerator, int64_t denominator)
	{
		if (numerator == 0)
			return "0";

		//sign handling
		bool neg_num = numerator < 0;
		bool neg_den = denominator < 0;
		bool neg_ret = neg_den != neg_num;
		if (neg_num)
			numerator = -numerator;
		if (neg_den)
			denominator = -denominator;

		//gcd
		int32_t divisor = gcd(numerator, denominator);
		numerator /= divisor;
		denominator /= divisor;

		//first step
		int64_t quocient = numerator / denominator;
		numerator %= denominator;

		//loop
		unordered_map<int32_t, int32_t> remain2pos;
		vector<int8_t> decimal_vec;
		decimal_vec.reserve(1024);
		int32_t pos = 0;
		int64_t r = numerator;
		while (r)
		{
			if (remain2pos.find(r) != remain2pos.end())
				break;
			remain2pos[r] = pos++;
			
			r *= 10;
			decimal_vec.push_back(r / denominator);
			
			r %= denominator;
		}

		char buf[64];
		if (neg_ret)
			sprintf_s(buf, "-%lld\0", quocient);
		else
			sprintf_s(buf, "%lld\0", quocient);

		if (!decimal_vec.size())
			return buf;

		int32_t buf_str_len = strlen(buf);
		vector<char> str_builder;
		str_builder.reserve(sizeof(buf) + decimal_vec.size() + 16);
		str_builder.resize(buf_str_len);
		std::copy(buf, buf + buf_str_len, str_builder.begin());

		str_builder.push_back('.');

		int32_t loop_start = r ? remain2pos[r] : 0;
		for (int32_t i = 0; i < loop_start; ++i)
			str_builder.push_back('0' + decimal_vec[i]);

		if (r)
			str_builder.push_back('(');

		for (int32_t i = loop_start; i < decimal_vec.size(); ++i)
			str_builder.push_back('0' + decimal_vec[i]);

		if (r)
			str_builder.push_back(')');
		
		str_builder.push_back('\0');

		return &str_builder[0];
	}
};

#if 0
class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {

	}
}; 
#endif