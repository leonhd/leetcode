#pragma once
#include <cstdint>
#include <vector>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}	
};


class linked_queue_t
{
	int32_t count_;
	int32_t left_;
	ListNode *head_;

	typedef linked_queue_t self_t;
public:
	linked_queue_t(ListNode *linked_list = nullptr) : head_(linked_list), count_(0), left_(0)
	{
		ListNode *ptr = head_;
		int32_t count = 0;
		while (ptr != nullptr)
		{
			++count;
			ptr = ptr->next;
		}

		count_ = count;
		left_ = count;
	}

	int32_t count()
	{
		return count_;
	}

	int32_t left()
	{
		return left_;
	}

	ListNode *head()
	{
		return head_;
	}

	void pop()
	{
		if (left_ > 0)
		{
			head_ = head_->next;
			--left_;
		}
	}

	static bool cmp(const self_t& lhs, const self_t& rhs)
	{
		return lhs.head_->val < rhs.head_->val;
	}
};

template<typename WAY>
class pq_t
{
	typedef	WAY way_t;
	std::vector<way_t> ways_;
	int32_t pos_;
	int32_t end_;
public:
	pq_t(int32_t max_ways) : pos_(0), end_(max_ways)
	{
		//int32_t tmp = 1;
		//while (tmp < max_ways)
		//	tmp <<= 1;

		ways_.reserve(max_ways + 1);
		ways_.resize(end_);
	}

	int32_t count()
	{
		return pos_;
	}

	void bubble_up(int32_t p)
	{
		int pp = p >> 1;
		while (p > 1 && way_t::cmp(ways_[p], ways_[pp]))
		{
			std::swap(ways_[p], ways_[pp]);

			p = pp;
			pp = p >> 1;
		}
	}

	void push(const way_t&& way)
	{
		if (pos_ < end_)
		{
			++pos_;
			ways_[pos_] = std::move(way);

			bubble_up(pos_);
		}
	}

	void bubble_down(int32_t p)
	{
		while (true)
		{
			int lhs = p << 1;
			int rhs = lhs + 1;
			int dst = p;

			if (lhs <= pos_ && way_t::cmp(ways_[lhs], ways_[dst]))
				dst = lhs;
			if (rhs <= pos_ && way_t::cmp(ways_[rhs], ways_[dst]))
				dst = rhs;

			if (dst == p)
				break;

			std::swap(ways_[p], ways_[dst]);

			p = dst;
		};
	}

	way_t& get_root()
	{
		if (pos_ < 1)
			throw std::exception("priority queue has no content");

		return ways_[1];
	}

	void adjust_root()
	{
		if (pos_ <= 1)
			return;
		
		bubble_down(1);
	}

	void del_root()
	{
		if (pos_ < 1)
			return;

		if (pos_ > 1)
			ways_[1] = std::move(ways_[pos_]);

		if (pos_ > 0)
			--pos_;

		if (pos_ > 1)
			bubble_down(1);
	}
};

class list_merger_t
{

};
