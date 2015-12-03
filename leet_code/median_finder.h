#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <stdint.h>
#include <Windows.h>
#include <functional>

template<typename T>
class median_finder_impl_merge_ex2_t
{
	typedef T ele_typ;
	std::vector<ele_typ> vals_;
	int64_t unordered_count_;
public:
	median_finder_impl_merge_ex2_t() : unordered_count_(0) {}

	void add_num(ele_typ num)
	{
		vals_.push_back(num);
		++unordered_count_;
//		if (vals_.size() >= 2)
//			std::inplace_merge(vals_.begin(), --vals_.end(), vals_.end());
	}

	double find_median()
	{
		if (unordered_count_ > 0)
		{
			if (unordered_count_ == 1)
				std::inplace_merge(vals_.begin(), vals_.end() - 1, vals_.end());
			else
			{
				auto ite = vals_.end() - unordered_count_;
				std::sort(ite, vals_.end());

				std::inplace_merge(vals_.begin(), ite, vals_.end());
			}
			
			unordered_count_ = 0;
		}

		int64_t pos = vals_.size() >> 1;
		if (vals_.size() & 1)
			return vals_[pos];
		else
			return (vals_[pos - 1] + vals_[pos]) / 2.0;
	}
};

template<typename T>
class median_finder_impl_merge_t
{
	typedef T ele_typ;
	std::vector<ele_typ> vals_;
public:
	void add_num(ele_typ num)
	{
		vals_.push_back(num);
		if (vals_.size() >= 2)
			std::inplace_merge(vals_.begin(), --vals_.end(), vals_.end());
	}

	double find_median()
	{
		int64_t pos = vals_.size() >> 1;
		if (vals_.size() & 1)
			return vals_[pos];
		else
			return (vals_[pos - 1] + vals_[pos]) / 2.0;
	}
};

template<typename T>
class median_finder_impl_set_t
{
	typedef T ele_typ;
	std::set<ele_typ> vals_;
public:
	void add_num(ele_typ num)
	{
		vals_.insert(num);
	}

	double find_median()
	{
		int64_t pos = vals_.size() >> 1;
		auto ite = vals_.begin();
		if (vals_.size() & 1)
		{
			for (int64_t i = 0; i < pos; ++i)
				++ite;

			return *ite;
		}
		else
		{
			--pos;
			for (int64_t i = 0; i < pos; ++i)
				++ite;

			ele_typ val = *ite;
			ele_typ val_1 = *(++ite);
			return (val + val_1) / 2.0;
		}
	}
};

template<typename T>
class median_finder_impl_merge_ex_t {
	typedef T ele_typ;
	std::vector<ele_typ> vals_;
	std::vector<ele_typ> alt_;
public:
	// Adds a number into the data structure.
	void add_num(ele_typ num) {
		if (vals_.size() == 0)
			vals_.push_back(num);
		else
		{
			alt_.resize(0);

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

			int i = 0;
			for (; i <= cur; ++i)
				alt_.push_back(vals_[i]);

			alt_.push_back(num);

			for (; i < count; ++i)
				alt_.push_back(vals_[i]);

			std::swap(vals_, alt_);
		}
	}

	// Returns the median of current data stream
	double find_median() {
		int pos = vals_.size() >> 1;
		if (vals_.size() & 1)
			return vals_[pos];
		else
			return (vals_[pos - 1] + vals_[pos]) / 2.0;
	}
};

template<typename T>
class median_finder_impl_2heap_t 
{
	typedef T ele_typ;
	int count_;
	std::priority_queue<ele_typ, vector<ele_typ>, std::greater<ele_typ>> rhs_heap_;
	std::priority_queue<ele_typ, vector<ele_typ>, std::less<ele_typ>> lhs_heap_;
public:
	median_finder_impl_2heap_t() :count_(0){}

	// Adds a number into the data structure.
	void add_num(ele_typ num) 
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
	double find_median() {
		if (count_ & 1){
			return rhs_heap_.top();
		}
		else
		{
			return (lhs_heap_.top() + rhs_heap_.top()) / 2.0;
		}
	}
};

class MedianFinder
{
	//median_finder_impl_merge_t<int> impl_;
	//median_finder_impl_merge_ex_t<int> impl_;
	//median_finder_impl_merge_ex2_t<int> impl_;
	median_finder_impl_2heap_t<int> impl_;
	//median_finder_impl_set_t<int> impl_;
public:
	void addNum(int num)
	{
		impl_.add_num(num);
	}

	double findMedian()
	{
		return impl_.find_median();
	}
};