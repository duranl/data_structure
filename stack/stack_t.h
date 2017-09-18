/*
 * stack_t.h
 *
 *  Created on: 2017年9月18日
 *      Author: duranl
 */

#ifndef STACK_STACK_T_H_
#define STACK_STACK_T_H_

#include "../list/vector_t.h"

template <typename _Object>
class stack_t
{
private:
	vector_t<_Object> *objects;
	void init() {objects = new vector_t<_Object>();}

public:
	stack_t() { init(); }
	stack_t(const stack_t &rhs)
	{
		operator=(rhs);
	}

	~stack_t()
	{
		delete objects;
	}

	const stack_t &operator=(const stack_t &rhs)
	{
		if (this != &rhs) {
			*objects = *(rhs.objects);
		}
		return *this;
	}

	bool empty() const
	{
		return size() == 0;
	}
	int size() const
	{
		return objects->size();
	}

	void push(const _Object &x)
	{
		objects->push_back(x);
	}

	void pop()
	{
		objects->pop_back();
	}

	_Object &top() const
	{
		return objects->back();
	}
};

#endif /* STACK_STACK_T_H_ */
