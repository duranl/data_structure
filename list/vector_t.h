/*
 * vector_my.hpp
 *
 *  Created on: 2017年9月16日
 *      Author: duranl
 */

#ifndef LIST_VECTOR_T_
#define LIST_VECTOR_T_

#include <cstdlib>
#include <cassert>

template <typename _Object>
class vector_t
{
public:
	explicit vector_t(int init_size = 0)
		: the_size(init_size), the_capacity(init_size + SPARE_CAPACITY)
	{
		objects = new _Object[the_capacity];
	}

	vector_t(const vector_t &rhs) : objects(NULL)
	{
		operator=(rhs);
	}

	~vector_t()
	{
		delete [] objects;
	}

	const vector_t & operator=(const vector_t &rhs)
	{
		if (this != &rhs) {
			delete [] objects;
			the_size = rhs.size();
			the_capacity = rhs.capacity();

			objects = new _Object[capacity()];
			for (int k = 0; k < size(); k++)
				objects[k] = rhs.objects[k];
		}
		return *this;
	}

	void resize(int new_size)
	{
		if (new_size > the_capacity)
			reserve(new_size * 2 + 1);
		the_size = new_size;
	}

	void reserve(int new_capacity)
	{
		if (new_capacity < the_size)
			return;

		_Object *old_array = objects;

		objects = new _Object[new_capacity];
		for (int k = 0; k < the_size; k++)
			objects[k] = old_array[k];

		the_capacity = new_capacity;

		delete [] old_array;
	}

	_Object &operator[] (int index)
	{
		assert(index >= 0 && index < the_size);
		return objects[index];
	}
	const _Object &operator[] (int index) const
	{
		assert(index >= 0 && index < the_size);
		return objects[index];
	}

	bool empty() const
	{
		return size() == 0;
	}
	int size() const
	{
		return the_size;
	}
	int capacity() const
	{
		return the_capacity;
	}

	void push_back(const _Object &x)
	{
		if (the_size == the_capacity)
			reserve(2 * the_capacity + 1);
		objects[the_size++] = x;
	}

	void pop_back()
	{
		assert(the_size > 0);
		the_size--;
	}

	const _Object &back() const
	{
		assert(the_size > 0);
		return objects[the_size - 1];
	}

	typedef _Object *iterator;
	typedef const _Object *const_iterator;

	iterator begin()
	{
		return &objects[0];
	}
	const_iterator begin() const
	{
		return &objects[0];
	}
	iterator end()
	{
		return &objects[size()];
	}
	const_iterator end() const
	{
		return &objects[size()];
	}

	enum {SPARE_CAPACITY = 16};
private:
	int the_size;
	int the_capacity;
	_Object *objects;
};



#endif /* LIST_VECTOR_T_ */
