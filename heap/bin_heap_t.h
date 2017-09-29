/*
 * bin_heap.h
 *
 *  Created on: 2017年9月21日
 *      Author: duranl
 */

#ifndef HEAP_BIN_HEAP_T_H_
#define HEAP_BIN_HEAP_T_H_

#include <cstdlib>
#include <vector>

template <typename _Comparable>
class bin_heap_t
{
public:
	explicit bin_heap_t(int capacity = 100);
	explicit bin_heap_t(const std::vector<_Comparable> &items);

	bool is_empty() const;
	const _Comparable &find_min() const;

	/**
	 * Insert item x, allowing duplicates.
	 */
	void insert(const _Comparable &x)
	{
		if (current_size == array.size() - 1)
			array.resize(array.size() * 2);

		// Percolate up
		int hole = ++current_size;
		for (; hole > 1 && x < array[hole / 2]; hole /= 2)
			array[hole] = array[hole / 2];
		array[hole] = x;
	}
	/**
	 * Remove the minimum item.
	 */
	void delete_min()
	{
		if (is_empty()) {

		}
		array[1] = array[current_size--];
		percolate_down(1);
	}
	/**
	 * Remove the minimum item and place it in min_item.
	 */
	void delete_min(_Comparable &min_item)
	{
		if (is_empty()) {

		}

		min_item = array[1];
		array[1] = array[current_size];
		percolate_down(1);
	}
	void make_empty();

private:
	int current_size; // Number of elements in heap
	std::vector<_Comparable> array; // The heap array

	void build_heap();
	/**
	 * Internal method to percolate down in the heap.
	 * hole is the index at which the percolate begins.
	 */
	void percolate_down(int hole)
	{
		int child;
		_Comparable tmp = array[hole];
		for (; hole * 2 <= current_size; hole = child) {
			child = hole * 2;
			if (child != current_size
					&& array[child + 1] < array[child])
				child++;
			if (array[child] < tmp)
				array[hole] = array[child];
			else
				break;
		}
		array[hole] = tmp;
	}
};

#endif /* HEAP_BIN_HEAP_T_H_ */
