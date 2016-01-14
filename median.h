#pragma once
#include <vector>
#include <algorithm>
#include <stdint.h>
using std::vector;

template<typename T, typename IDX_TYP>
class median_finder_impl_t
{
public:
	typedef T src_typ;
	typedef IDX_TYP idx_typ;

private:
	static double median(src_typ *beg, idx_typ count)
	{
		idx_typ pos = count >> 1;
		if (count & 1)
			return beg[pos];
		else
			return (beg[pos - 1] + beg[pos]) / 2.0;
	}

	static double find_median(src_typ s1, src_typ *s2_beg, idx_typ count2)
	{
		//outside the range
		if (s1 < s2_beg[0] || s1 > s2_beg[count2 - 1])
		{
			idx_typ count = count2 + 1;
			idx_typ pos = count >> 1;

			if (s1 > s2_beg[count2 - 1])
			{
				if (count & 1)
					return s2_beg[pos];
				else
					return (s2_beg[pos - 1] + s2_beg[pos]) / 2.0;
			}
			else
			{
				if (count & 1)
					return s2_beg[pos - 1];
				else
					return (s2_beg[pos - 2] + s2_beg[pos - 1]) / 2.0;
			}
		}

		//inside the range
		idx_typ cur = 0, stop = count2;
		while (stop - cur > 1)
		{
			idx_typ pos = (cur + stop) >> 1;

			if (s2_beg[pos] > s1)
			{
				stop = pos;
			}
			else
			{
				cur = pos;
			}
		}

		//get the result
		idx_typ pos = count2 >> 1;
		if (count2 & 1)
		{
			if (cur < pos - 1)
				return (s2_beg[pos - 1] + s2_beg[pos]) / 2.0;
			else if (cur >= pos + 1)
				return (s2_beg[pos] + s2_beg[pos + 1]) / 2.0;
			else
				return (s1 + s2_beg[pos]) / 2.0;
		}
		else
		{
			if (cur < pos - 1)
				return s2_beg[pos - 1];
			else if (cur >= pos)
				return s2_beg[pos];
			else
				return s1;
		}
	}

	static double find_median(src_typ s10, src_typ s11, src_typ *s2_beg, idx_typ count2)
	{
		if (s11 <= s2_beg[0])
		{
			if (count2 == 2)
				return (s11 + s2_beg[0]) / 2.0;
			else if (count2 & 1)
				return s2_beg[(count2 >> 1) - 1];
			else
			{
				idx_typ pos = (count2 >> 1) - 1;
				return (s2_beg[pos - 1] + s2_beg[pos]) / 2.0;
			}
		}
		else if (s10 >= s2_beg[count2 - 1])
		{
			if (count2 == 2)
				return (s10 + s2_beg[1]) / 2.0;
			else if (count2 & 1)
				return s2_beg[(count2 >> 1) + 1];
			else
			{
				idx_typ pos = (count2 >> 1) + 1;
				return (s2_beg[pos - 1] + s2_beg[pos]) / 2.0;
			}
		}

		idx_typ cur0 = 0, stop = count2;
		while (stop - cur0 > 1)
		{
			idx_typ pos = (cur0 + stop) >> 1;

			if (s2_beg[pos] > s10)
			{
				stop = pos;
			}
			else
			{
				cur0 = pos;
			}
		}
		if (s10 < s2_beg[0])
			cur0 = -1;

		stop = count2;
		idx_typ cur1 = 0;
		while (stop - cur1 > 1)
		{
			idx_typ pos = (cur1 + stop) >> 1;

			if (s2_beg[pos] > s11)
			{
				stop = pos;
			}
			else
			{
				cur1 = pos;
			}
		}

		idx_typ pos = (count2 >> 1);
		if (count2 & 1)
		{
			if (cur0 >= pos)
			{
				if (cur0 == pos)
					return s10;
				else
					return s2_beg[pos + 1];
			}
			else if (cur1 < pos)
			{
				if (cur1 == pos - 1)
					return s11;
				else
					return s2_beg[pos - 1];
			}
			else
				return s2_beg[pos];
		}
		else
		{
			if (cur0 >= pos)
			{
				if (cur0 == pos)
					return (s10 + s2_beg[pos]) / 2.0;
				else
					return (s2_beg[pos] + s2_beg[pos + 1]) / 2.0;
			}
			else if (cur1 < pos - 1)
			{
				if (cur1 == pos - 2)
					return (s11 + s2_beg[pos - 1]) / 2.0;
				else
					return (s2_beg[pos - 2] + s2_beg[pos - 1]) / 2.0;
			}
			else
			{
				if (cur0 == pos - 1 && cur1 == pos - 1)
					return (s10 + s11) / 2.0;
				else if (cur0 == pos - 1 && cur1 >= pos)
					return (s10 + s2_beg[pos]) / 2.0;
				else if (cur0 < pos - 1 && cur1 == pos - 1)
					return (s11 + s2_beg[pos - 1]) / 2.0;
				return (s2_beg[pos - 1] + s2_beg[pos]) / 2.0;
			}
		}
	}
public:
	static double find_median(src_typ *s1_beg, idx_typ count1, src_typ *s2_beg, idx_typ count2)
	{
		if (!count1)
			return median(s2_beg, count2);

		if (!count2)
			return median(s1_beg, count1);

		if (count1 == 1 && count2 == 1)
			return (s1_beg[0] + s2_beg[0]) / 2.0;

		if (count1 == 1)
			return find_median(s1_beg[0], s2_beg, count2);

		if (count2 == 1)
			return find_median(s2_beg[0], s1_beg, count1);

		if (count1 == 2)
			return find_median(s1_beg[0], s1_beg[1], s2_beg, count2);

		if (count2 == 2)
			return find_median(s2_beg[0], s2_beg[1], s1_beg, count1);

		double m1 = median(s1_beg, count1), m2 = median(s2_beg, count2);
		if (m1 == m2)
			return m1;

		if (m1 > m2)
		{
			std::swap(s1_beg, s2_beg);
			std::swap(count1, count2);
		}

		idx_typ cut_len1 = (count1 & 1) ? (count1 >> 1) : (count1 >> 1) - 1;
		idx_typ cut_len2 = (count2 & 1) ? (count2 >> 1) : (count2 >> 1) - 1;
		idx_typ cut_len = std::min<idx_typ>(cut_len1, cut_len2);

		return find_median(s1_beg + cut_len, count1 - cut_len, s2_beg, count2 - cut_len);
	}
};

template<typename T, typename IDX_TYP>
class median_finder_impl_1_t
{
public:
	typedef T src_typ;
	typedef IDX_TYP idx_typ;

private:
	static double median(src_typ *beg, idx_typ count)
	{
		idx_typ pos = count >> 1;
		if (count & 1)
			return beg[pos];
		else
			return (beg[pos - 1] + beg[pos]) / 2.0;
	}

	static double find_median(src_typ s1, src_typ *s2_beg, idx_typ count2)
	{
		idx_typ pos = count2 >> 1;
		if (count2 & 1)
		{
			if (s1 < s2_beg[pos - 1])
				return (s2_beg[pos - 1] + s2_beg[pos]) / 2.0;
			else if (s1 >= s2_beg[pos + 1])
				return (s2_beg[pos] + s2_beg[pos + 1]) / 2.0;
			else
				return (s1 + s2_beg[pos]) / 2.0;
		}
		else
		{
			if (s1 < s2_beg[pos - 1])
				return s2_beg[pos - 1];
			else if (s1 >= s2_beg[pos])
				return s2_beg[pos];
			else
				return s1;
		}
	}

	static double find_median(src_typ s10, src_typ s11, src_typ *s2_beg, idx_typ count2)
	{
		idx_typ pos = (count2 >> 1);
		if (count2 & 1)
		{
			if (s10 >= s2_beg[pos])
			{
				if (s10 < s2_beg[pos + 1])
					return s10;
				else
					return s2_beg[pos + 1];
			}
			else if (s11 < s2_beg[pos])
			{
				if (s11 >= s2_beg[pos - 1])
					return s11;
				else
					return s2_beg[pos - 1];
			}
			else
				return s2_beg[pos];
		}
		else
		{
			if (count2 == 2)
			{
				if (s10 >= s2_beg[1])
					return (s2_beg[1] + s10) / 2.0;
				else if (s11 < s2_beg[0])
					return (s11 + s2_beg[0]) / 2.0;
				else
				{
					if (s10 >= s2_beg[0] && s11 < s2_beg[1])
						return (s10 + s11) / 2.0;
					else if (s10 < s2_beg[0] && s11 >= s2_beg[1])
						return (s2_beg[0] + s2_beg[1]) / 2.0;
					else if (s10 < s2_beg[0] && s11 < s2_beg[1])
						return (s2_beg[0] + s11) / 2.0;
					else
						return (s10 + s2_beg[1]) / 2.0;
				}
			}
			else
			{
				if (s10 >= s2_beg[pos])
				{
					if (s10 <= s2_beg[pos + 1])
						return (s10 + s2_beg[pos]) / 2.0;
					else
						return (s2_beg[pos] + s2_beg[pos + 1]) / 2.0;
				}
				else if (s11 < s2_beg[pos - 1])
				{
					if (s11 > s2_beg[pos - 2])
						return (s11 + s2_beg[pos - 1]) / 2.0;
					else
						return (s2_beg[pos - 2] + s2_beg[pos - 1]) / 2.0;
				}
				else
				{
					if (s10 >= s2_beg[pos - 1] && s11 < s2_beg[pos])
						return (s10 + s11) / 2.0;
					else if (s10 >= s2_beg[pos - 1] && s11 >= s2_beg[pos])
						return (s10 + s2_beg[pos]) / 2.0;
					else if (s10 < s2_beg[pos - 1] && s11 < s2_beg[pos])
						return (s11 + s2_beg[pos - 1]) / 2.0;
					return (s2_beg[pos - 1] + s2_beg[pos]) / 2.0;
				}
			}
		}
	}
public:
	static double find_median(src_typ *s1_beg, idx_typ count1, src_typ *s2_beg, idx_typ count2)
	{
		if (!count1)
			return median(s2_beg, count2);

		if (!count2)
			return median(s1_beg, count1);

		if (count1 == 1 && count2 == 1)
			return (s1_beg[0] + s2_beg[0]) / 2.0;

		if (count1 == 1)
			return find_median(s1_beg[0], s2_beg, count2);

		if (count2 == 1)
			return find_median(s2_beg[0], s1_beg, count1);

		if (count1 == 2)
			return find_median(s1_beg[0], s1_beg[1], s2_beg, count2);

		if (count2 == 2)
			return find_median(s2_beg[0], s2_beg[1], s1_beg, count1);

		double m1 = median(s1_beg, count1), m2 = median(s2_beg, count2);
		if (m1 == m2)
			return m1;

		if (m1 > m2)
		{
			std::swap(s1_beg, s2_beg);
			std::swap(count1, count2);
		}

		idx_typ cut_len1 = (count1 & 1) ? (count1 >> 1) : (count1 >> 1) - 1;
		idx_typ cut_len2 = (count2 & 1) ? (count2 >> 1) : (count2 >> 1) - 1;
		idx_typ cut_len = std::min<idx_typ>(cut_len1, cut_len2);

		return find_median(s1_beg + cut_len, count1 - cut_len, s2_beg, count2 - cut_len);
	}
};

class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		return median_finder_impl_1_t<int32_t, size_t>::find_median(&nums1[0], nums1.size(), &nums2[0], nums2.size());
	}
};