#pragma once
#include <math.h>
#include <stdint.h>
#include <vector>
using namespace std;

class perfect_square_solver_t
{
public:
	static int32_t get_least_squares(int32_t num)
	{
		//init all
		vector<int32_t> least_squares(num + 1, -1);

		//init squares
		int32_t sqrt_num = sqrt(num);
		least_squares[0] = 0;
		for (int32_t i = 1; i <= sqrt_num; ++i)
		{
			int32_t tmp_sqr = i * i;
			least_squares[tmp_sqr] = 1;
		}
		
		//calc
		for (int32_t i = 1; i < sqrt_num; ++i)
		{
			int32_t sqr_cur = i * i;
			int32_t sqr_next = sqr_cur + 2 * i + 1;

			for (int32_t j = sqr_cur + 1; j < sqr_next; ++j)
			{
				int32_t min_sqrs = j;
				for (int32_t k = 1; k <= i; ++k)
				{
					int32_t tmp_sqrs = least_squares[j - k * k] + 1;
					if (min_sqrs > tmp_sqrs)
						min_sqrs = tmp_sqrs;
				}

				least_squares[j] = min_sqrs;
			}
		}

		for (int32_t j = sqrt_num * sqrt_num; j <= num; ++j)
		{
			int32_t min_sqrs = j;
			for (int32_t k = 1; k <= sqrt_num; ++k)
			{
				int32_t tmp_sqrs = least_squares[j - k * k] + 1;
				if (min_sqrs > tmp_sqrs)
					min_sqrs = tmp_sqrs;
			}
			least_squares[j] = min_sqrs;
		}

		return least_squares[num];
	}
};

#if 0
class Solution {
public:
	int numSquares(int n) {
		return perfect_square_solver_t::get_least_squares(n);
	}
};
#endif