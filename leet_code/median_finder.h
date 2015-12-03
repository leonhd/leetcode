#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <stdint.h>
#include <Windows.h>
#include <functional>

class MedianFinder {
	std::vector<int> vals_;
	std::vector<int> alt_;
	std::set<int> val_set_;
	std::set<int>::iterator ite_;
	int ite_pos_;
	int64_t t_locate_, t_copy_;
public:
	MedianFinder() : t_locate_(0), t_copy_(0) {}

	// Adds a number into the data structure.
	void addNum1(int num)
	{
		vals_.push_back(num);
		if (vals_.size() >= 2)
			std::inplace_merge(vals_.begin(), --vals_.end(), vals_.end());
	}
	void addNum2(int num) {
		if (vals_.size() == 0)
			vals_.push_back(num);
		else
		{
			alt_.resize(0);

			int64_t t0, t1, t2;
			QueryPerformanceCounter((LARGE_INTEGER*)&t0);
			int count = vals_.size();
			int cur = 0, stop = vals_.size();
			if (num < vals_[0])
				cur = -1;
			else if (num > vals_[count - 1])
				cur = count - 1;
			else
			{
				while (stop - cur > 1)
				{
					int pos = (stop + cur) >> 1;
					if (vals_[pos] > num)
						stop = pos;
					else
						cur = pos;
				}
			}
			QueryPerformanceCounter((LARGE_INTEGER*)&t1);

			int i = 0;
			for (; i <= cur; ++i)
				alt_.push_back(vals_[i]);

			alt_.push_back(num);

			for (; i < count; ++i)
				alt_.push_back(vals_[i]);

			std::swap(vals_, alt_);
			QueryPerformanceCounter((LARGE_INTEGER*)&t2);
			t_locate_ += t1 - t0;
			t_copy_ += t2 - t1;
		}
	}

	void addNum(int num)
	{
		val_set_.insert(num);
		if (val_set_.size() == 1)
		{
			ite_ = val_set_.begin();
			ite_pos_ = 0;
		}
		else
		{
			if (num < *ite_)
				++ite_pos_;
		}
	}

	// Returns the median of current data stream
	double findMedian1() {
		int pos = vals_.size() >> 1;
		if (vals_.size() & 1)
			return vals_[pos];
		else
			return (vals_[pos - 1] + vals_[pos]) / 2.0;
	}

	double findMedian()
	{
		int count = val_set_.size();
		int pos = count >> 1;
		if (count & 1)
		{
			for (int i = ite_pos_; i < pos; ++i)
				++ite_;

			return *ite_;
		}
		else
		{
			--pos;
			
			for (int i = ite_pos_; i < pos; ++i)
				++ite_;

			int val = *ite_;
			int val1 = *(++ite_);
			return (val + val1) / 2.0;
		}
	}
	void profile()
	{
		int64_t freq;
		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
		fprintf(stdout, "locating costs %I64dms, copying costs %I64dms\n", t_locate_ * 1000 / freq, t_copy_ * 1000 / freq);
	}
};

class MedianFinderEx {
public:
	MedianFinderEx() :count_(0){}

	// Adds a number into the data structure.
	void addNum(int num) 
	{
		if (count_ & 1)
		{
			//adjust
			if (!rhs_heap_.empty() && num > rhs_heap_.top())
			{
				rhs_heap_.push(num);
				num = rhs_heap_.top();
				rhs_heap_.pop();
			}

			//put to left
			lhs_heap_.push(num);
		}
		else
		{
			//adjust
			if (!lhs_heap_.empty() && num < lhs_heap_.top())
			{
				lhs_heap_.push(num);
				num = lhs_heap_.top();
				lhs_heap_.pop();
			}
			
			//put to right
			rhs_heap_.push(num);
		}

		++count_;
	}

	// Returns the median of current data stream
	double findMedian() {
		if (count_ & 1){
			return rhs_heap_.top();
		}
		else
		{
			return (lhs_heap_.top() + rhs_heap_.top()) / 2.0;
		}
	}

private:
	int count_;
	std::priority_queue<int, vector<int>, std::greater<int>> rhs_heap_;
	std::priority_queue<int, vector<int>, std::less<int>> lhs_heap_;
};