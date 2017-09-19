/*
 * queue_t.h
 *
 *  Created on: 2017年9月19日
 *      Author: duranl
 */

#ifndef QUEUE_QUEUE_T_H_
#define QUEUE_QUEUE_T_H_

#include "../list/list_t.h"

template <typename _Object>
class queue_t
{
private:
	list_t<_Object> *datas;
	void init() {datas = new list_t<_Object>();}

public:
	queue_t()
	{
		init();
	}

	~queue_t()
	{
		delete datas;
	}

	void enqueue(const _Object &x)
	{
		datas->push_back(x);
	}

	_Object dequeue()
	{
		_Object ret_val = datas->front();
		datas->pop_front();
		return ret_val;
	}

	int size() const
	{
		return datas->size();
	}

	bool empty() const
	{
		return size() == 0;
	}
};

#endif /* QUEUE_QUEUE_T_H_ */
