#pragma once
#if 0
#include <cstdint>
#include <vector>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}	
};


class linked_queue_ex_t
{
	int32_t count_;
	int32_t left_;
	ListNode *head_;

	typedef linked_queue_ex_t self_t;
public:
	typedef ListNode* ele_t;
	linked_queue_ex_t(ListNode *linked_list = nullptr) : head_(linked_list), count_(0), left_(0)
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

	ele_t head()
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

class linked_queue_t
{
public:
	typedef ListNode* ele_t;
private:
	int32_t count_;
	ele_t head_, tail_;
public:
	linked_queue_t() : count_(0), head_(nullptr), tail_(nullptr) {}

	int32_t count()
	{
		return count_;
	}

	ele_t head()
	{
		return head_;
	}

	void append(ele_t ele)
	{
		ele->next = nullptr;

		if (count_ == 0)
			head_ = ele;
		else
			tail_->next = ele;

		tail_ = ele;
		++count_;
	}
};

template<typename WAY, typename O_QUEUE>
class pq_t
{
	typedef	WAY way_t;
	typedef O_QUEUE queue_t;
	std::vector<way_t> ways_;
	queue_t queue_;
	int32_t pos_;
	int32_t end_;
public:
	pq_t(int32_t max_ways) : pos_(0), end_(max_ways)
	{
		//int32_t tmp = 1;
		//while (tmp < max_ways)
		//	tmp <<= 1;

		ways_.reserve(end_ + 1);
		ways_.resize(end_ + 1);
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

	void merge()
	{

	}
};

class list_merger_t
{

};

#endif

#include <vector>
#include <queue>

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};
struct node_cmp_t
{	// functor for operator>
	typedef ListNode* _Ty;
	typedef _Ty first_argument_type;
	typedef _Ty second_argument_type;
	typedef bool result_type;

	constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const
	{	// apply operator> to operands
		return (_Left->val > _Right->val);
	}
};

class linked_queue_t
{
public:
	typedef ListNode* ele_t;
private:
	int32_t count_;
	ele_t head_, tail_;
public:
	linked_queue_t() : count_(0), head_(nullptr), tail_(nullptr) {}

	int32_t count()
	{
		return count_;
	}

	ele_t head()
	{
		return head_;
	}

	void append(ele_t ele)
	{
		ele->next = nullptr;

		if (count_ == 0)
			head_ = ele;
		else
			tail_->next = ele;

		tail_ = ele;
		++count_;
	}
};

class Merge_Solution {
	typedef ListNode* ele_t;
public:
	static ListNode* mergeKLists(std::vector<ele_t>& lists) {
		std::priority_queue<ele_t, std::vector<ele_t>, node_cmp_t> pq;
		for (auto ele: lists)
		{
			if (ele)
				pq.push(ele);
		}

		ele_t head = nullptr;
		ele_t *pp_cur = &head;
		while (pq.size())
		{
			ele_t ele = pq.top();
			pq.pop();

			ele_t next = ele->next;
			if (next != nullptr)
				pq.push(next);

			*pp_cur = ele;
			pp_cur = &ele->next;
		}

		return head;
	}
};

void test_merge(int way_count, int way_max_len)
{
	std::vector<ListNode*> ways;
	for (int i = 0; i < way_count; ++i)
	{
		int len = rand() % way_max_len;
		int val = rand() % 1024;
		linked_queue_t queue;
		for (int j = 0; j < len; ++j)
		{
			ListNode *node = new ListNode(val++);
			queue.append(node);
		}

		ways.push_back(queue.head());
	}

	ListNode* ret = Merge_Solution::mergeKLists(ways);
	ListNode* ptr = ret;
	while (ptr != nullptr)
	{
		std::cout << ptr->val << std::endl;
		ptr = ptr->next;
	}
}

