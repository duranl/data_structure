/*
 * list_t.h
 *
 *  Created on: 2017年9月17日
 *      Author: duranl
 */

#ifndef LIST_LIST_T_H_
#define LIST_LIST_T_H_

#include <cstdlib>

template <typename _Object>
class list_t
{
private:
	struct node_t
	{
		_Object data;
		node_t *prev;
		node_t *next;

		node_t(const _Object &d = _Object(), node_t *p = NULL, node_t *n = NULL)
			: data(d), prev(p), next(n){ }
	};

public:
	class const_iterator
	{
	public:
		const_iterator() : current(NULL) {}

		const _Object &operator*() const
		{
			return retrieve();
		}

		const_iterator &operator++()
		{
			current = current->next;
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}

		bool operator==(const const_iterator &rhs) const
		{
			return current == rhs.current;
		}
		bool operator!=(const const_iterator &rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		node_t *current;

		_Object & retrieve() const
		{
			return current->data;
		}

		const_iterator(node_t *p) : current(p) {}

		friend class list_t<_Object>;
	};


	class iterator : public const_iterator
	{
	public:
		iterator() { }

		_Object &operator*()
		{
			return const_iterator::retrieve();
		}
		const _Object &operator*() const
		{
			return const_iterator::operator*();
		}

		iterator &operator++()
		{
			const_iterator::current = const_iterator::current->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

	protected:
		iterator(node_t *p) : const_iterator(p) { }

		friend class list_t<_Object>;
	};

public:
	list_t()
	{
		init();
	}

	list_t(const list_t &rhs)
	{
		init();
		*this = rhs;
	}

	~list_t()
	{
		clear();
		delete head;
		delete tail;
	}

	const list_t &operator=(const list_t &rhs)
	{
		if (this == &rhs)
			return *this;
		clear();
		for (const_iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
			push_back(*iter);
		return *this;
	}

	iterator begin()
	{
		return iterator(head->next);
	}
	const_iterator begin() const
	{
		return const_iterator(head->next);
	}
	iterator end()
	{
		return iterator(tail);
	}
	const_iterator end() const
	{
		return const_iterator(tail);
	}

	int size() const
	{
		return the_size;
	}
	bool empty() const
	{
		return size() == 0;
	}

	void clear()
	{
		while (!empty())
			pop_front();
	}

	_Object &front()
	{
		return *begin();
	}
	const _Object &front() const
	{
		return *begin();
	}
	_Object &back()
	{
		return *--end();
	}
	const _Object &back() const
	{
		return *--end();
	}
	void push_front(const _Object &x)
	{
		insert(begin(), x);
	}
	void push_back(const _Object &x)
	{
		insert(end(), x);
	}
	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		erase(--end());
	}

	iterator insert(iterator iter, const _Object &x)
	{
		node_t *p = iter.current;
		the_size++;
		return iterator(p->prev = p->prev->next = new node_t(x, p->prev, p));
	}

	iterator erase(iterator iter)
	{
		node_t *p = iter.current;
		iterator ret_val(p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		the_size--;
		return ret_val;
	}
	iterator erase(iterator start, iterator end)
	{
		for (iterator iter = start; iter != end;
				iter = erase(iter));
		return end;
	}

private:
	int the_size;
	node_t *head;
	node_t *tail;

	void init()
	{
		the_size = 0;
		head = new node_t;
		tail = new node_t;
		head->next = tail;
		tail->prev = head;
	}
};



#endif /* LIST_LIST_T_H_ */
