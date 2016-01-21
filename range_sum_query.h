#pragma once
#include <vector>
#include <unordered_map>
#include <stdint.h>
#include <memory>
using namespace std;

class NumArray {
	vector<int> & nums_;
	int32_t buf_len_;
	unique_ptr<int64_t>  ptr_;
public:
	NumArray(vector<int> &nums) : nums_(nums), buf_len_(nums_.size() * nums_.size()), ptr_(new int64_t[buf_len_]){
		int64_t *vals = ptr_.get();
		for (int32_t i = 0; i < buf_len_; ++i)
			vals[i] = INT_MIN - 1;
	}

	void update(int i, int val) {
		if (i >= 0 && i < nums_.size())
		{
			if (nums_[i] != val)
			{
				int32_t tmp = nums_[i];
				nums_[i] = val;

				int64_t delta = val;
				delta -= tmp;
				int64_t *vals = ptr_.get();
				for (int j = 0; j <= i; ++j)
				{
					for (int32_t k = j; k < nums_.size(); ++k)
					{
						int64_t *target = vals + j * nums_.size() + k;
						if (*target != INT_MIN - 1)
							*target += delta;
					}
				}
			}
		}
	}

	int sumRange(int i, int j) {
		int64_t ret = 0;

		if (i < 0)
			i = 0;

		int32_t stop = j + 1;
		if (stop > nums_.size())
			stop = nums_.size();

		int64_t *vals = ptr_.get();
		if (vals[i * nums_.size() + j] == INT_MIN - 1)
		{
			for (; i < stop; ++i)
				ret += nums_[i];

			vals[i * nums_.size() + j] = ret;
		}
		else
			ret = vals[i * nums_.size() + j];

		if (ret >= INT_MAX)
			return INT_MAX;

		if (ret <= INT_MIN)
			return INT_MIN;

		return ret;
	}
};
