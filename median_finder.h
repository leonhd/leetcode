#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <stdint.h>
#include <Windows.h>
#include <functional>

template<typename T>
class median_finder_impl_merge_t
{
	typedef T ele_typ;
	std::vector<ele_typ> vals_;
	int64_t unordered_count_;
public:
	median_finder_impl_merge_t() : unordered_count_(0) {}

	void add_num(ele_typ num)
	{
		vals_.push_back(num);
		++unordered_count_;
	}

	double find_median()
	{
		if (unordered_count_ > 0)
		{
			auto mid_ite = vals_.end() - unordered_count_;

			if (unordered_count_ > 1)
				std::sort(mid_ite, vals_.end());

			std::inplace_merge(vals_.begin(), mid_ite, vals_.end());

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
class median_finder_impl_set_t
{
	typedef T ele_typ;
	std::multiset<ele_typ> vals_;
	int64_t lhs_count_, rhs_count_;
	typename std::multiset<ele_typ>::iterator mid_ite_;
public:
	void add_num(ele_typ num)
	{
		vals_.insert(num);

		if (vals_.size() == 1)
		{
			mid_ite_ = vals_.begin();
			lhs_count_ = 0;
			rhs_count_ = 0;
		}
		else
		{
			lhs_count_ += (num < *mid_ite_);
			rhs_count_ += (num > *mid_ite_);
		}
	}

	double find_median()
	{
		int64_t eq_count = vals_.size() - lhs_count_ - rhs_count_;
		//jump to 0 pos in eq area
		auto ite = mid_ite_;
		if (eq_count > 1)
		{
			ele_typ tmp_mid_val = *ite;
			while (ite != vals_.begin() && *ite == tmp_mid_val)
				--ite;

			if (*ite != tmp_mid_val)
				++ite;
		}

		//adjust mid post
		int64_t pos = vals_.size() >> 1;
		//jump to calculated mid pos
		int64_t pos_rel_eq = (vals_.size() & 1) ? pos - lhs_count_ : pos - 1 - lhs_count_;
		ele_typ mid_val = *ite;
		if (pos_rel_eq > 0)
		{
			int64_t range_count = 0;
			for (int64_t i = 0; i < pos_rel_eq; ++i)
			{
				auto tmp_ite = ite;
				++ite;
				++range_count;

				if (*tmp_ite != *ite)
				{
					lhs_count_ += range_count;
					if (*tmp_ite != mid_val)
						rhs_count_ -= range_count;
					range_count = 0;
				}
			}

			if (*ite != mid_val)
			{
				mid_val = *ite;
				auto tmp_ite = ite;
				while (tmp_ite != vals_.end() && *tmp_ite == mid_val)
				{
					++tmp_ite;
					++range_count;
				}

				rhs_count_ -= range_count;
			}

		}
		else if (pos_rel_eq < 0)
		{
			int64_t range_count = eq_count - 1;
			for (int64_t i = pos_rel_eq; i < 0; ++i)
			{
				auto tmp_ite = ite;
				--ite;
				++range_count;

				if (*tmp_ite != *ite)
				{
					rhs_count_ += range_count;
					if (*tmp_ite != mid_val)
						lhs_count_ -= range_count;
					range_count = 0;
				}
			}

			if (*ite != mid_val)
			{
				mid_val = *ite;
				auto tmp_ite = ite;
				range_count = tmp_ite == vals_.begin() ? 1 : 0;
				while (tmp_ite != vals_.begin() && *tmp_ite == mid_val)
				{
					--tmp_ite;
					++range_count;
				}

				lhs_count_ -= range_count;
			}
		}			
		mid_ite_ = ite;

		if (vals_.size() & 1)
			return *ite;
		else
		{
			ele_typ val = *ite;
			ele_typ val_1 = *(++ite);
			return (val + val_1) / 2.0;
		}
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

template<typename T>
class median_finder_impl_2set_t
{
	typedef T ele_typ;
	int count_;
	std::multiset<ele_typ> rhs_set_;
	std::multiset<ele_typ> lhs_set_;
public:
	median_finder_impl_2set_t() :count_(0){}

	// Adds a number into the data structure.
	void add_num(ele_typ num)
	{
		if (count_ & 1)
		{
			//adjust
			if (!rhs_set_.empty() && num > *rhs_set_.begin())
			{
				rhs_set_.insert(num);
				num = *rhs_set_.begin();
				rhs_set_.erase(rhs_set_.begin());
			}

			//put to left
			lhs_set_.insert(num);
		}
		else
		{
			//adjust
			if (!lhs_set_.empty() && num < *lhs_set_.rbegin())
			{
				lhs_set_.insert(num);
				num = *lhs_set_.rbegin();
				lhs_set_.erase(--lhs_set_.end());
			}

			//put to right
			rhs_set_.insert(num);
		}

		++count_;
	}

	// Returns the median of current data stream
	double find_median() {
		if (count_ & 1){
			return *rhs_set_.begin();
		}
		else
		{
			return (*lhs_set_.rbegin() + *rhs_set_.begin()) / 2.0;
		}
	}
};

class MedianFinder
{
	//median_finder_impl_merge_t<int> impl_;
	median_finder_impl_2heap_t<int> impl_;
	//median_finder_impl_set_t<int> impl_;
	//median_finder_impl_2set_t<int> impl_;
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