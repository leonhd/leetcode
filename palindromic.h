#pragma once
#include <string>
#include <stdint.h>
#include <algorithm>
using namespace std;

class palindrome_finder_n2_impl_t
{
	static bool find_odd_pal(string &s, int32_t center_pos, int32_t & cur_max_len)
	{
		int32_t half_len = std::min<int32_t>(center_pos, s.length() - center_pos - 1);
		int32_t len_lim = half_len * 2 + 1;
		
		//limit of pal sub string less than current max length
		if (len_lim < cur_max_len)
			return false;

		//max length palindrome can not be true at current position
		if (cur_max_len > 0)
		{
			int32_t test_len = cur_max_len / 2;
			if (s[center_pos - test_len] != s[center_pos + test_len])
				return false;
		}

		int32_t left_idx = center_pos - 1, right_idx = center_pos + 1;
		for (int32_t i = 0; i < half_len; ++i)
		{
			if (s[left_idx] != s[right_idx])
				break;

			--left_idx;
			++right_idx;
		}

		int32_t cur_len = (right_idx - center_pos - 1) * 2 + 1;
		if (cur_len > cur_max_len)
		{
			cur_max_len = cur_len;
			return true;
		}

		return false;
	}
	static bool find_even_pal(string &s, int32_t left_pos, int32_t & cur_max_len)
	{
		int32_t half_len = std::min<int32_t>(left_pos + 1, s.length() - left_pos - 1);		
		int32_t len_lim = half_len * 2;

		//limit of pal sub string less than current max length
		if (len_lim < cur_max_len)
			return false;

		//max length palindrome can not be true at current position
		if (cur_max_len > 0)
		{
			int32_t test_len = (cur_max_len + 1) / 2;
			if (s[left_pos - test_len + 1] != s[left_pos + test_len])
				return false;
		}

		int32_t left_idx = left_pos, right_idx = left_pos + 1;
		for (int32_t i = 0; i < half_len; ++i)
		{
			if (s[left_idx] != s[right_idx])
				break;

			--left_idx;
			++right_idx;
		}

		int32_t cur_len = (right_idx - left_pos - 1) * 2;
		if (cur_len > cur_max_len)
		{
			cur_max_len = cur_len;
			return true;
		}

		return false;
	}
public:
	static string get_longest_palindrome(string &s)
	{
		int32_t len = s.length();
		int32_t max_len = 0;
		int32_t odd_pos = -1, even_pos = -1;

		//odd string
		for (int32_t cp = len / 2; cp < len; ++cp)
		{
			if (find_odd_pal(s, cp, max_len))
				odd_pos = cp;
		}
		for (int32_t cp = len / 2 - 1; cp > -1; --cp)
		{
			if (find_odd_pal(s, cp, max_len))
				odd_pos = cp;
		}
		int32_t odd_len = max_len;

		int32_t tmp = len - 1;
		for (int32_t lp = tmp / 2; lp < tmp; ++lp)
		{
			if (find_even_pal(s, lp, max_len))
				even_pos = lp;
		}

		for (int32_t lp = tmp / 2 - 1; lp > -1; --lp)
		{
			if (find_even_pal(s, lp, max_len))
				even_pos = lp;
		}

		if (odd_len == max_len)
			return s.substr(odd_pos - max_len / 2, max_len);
		else
			return s.substr(even_pos - max_len / 2 + 1, max_len);
	}
};

class Solution {
public:
	string longestPalindrome(string s) 
	{
		return palindrome_finder_n2_impl_t::get_longest_palindrome(s);
	}
};