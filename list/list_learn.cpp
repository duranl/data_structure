/*
 * list_lean.cpp
 *
 *  Created on: 2017年9月16日
 *      Author: duranl
 */

#include <iostream>
#include <vector>

using namespace std;

template<typename container, typename object>
void change(container &c, const object &newValue)
{
	typename container::iterator iter = c.begin();
	while (iter != c.end())
		*iter++ = newValue;
}

template <typename container>
void printCollection(const container &c, ostream &out = cout)
{
	if (c.empty())
		cout << "(empty)";
	else {
		typename container::const_iterator iter = c.begin();
		out << "[ " << *iter++; // Print first item

		while (iter != c.end())
			cout << ", " << *iter++;
		out << " ]" << endl;
	}
}

void list_test()
{
	vector<int> vec;
	for (int i = 0; i < 3; i++) {
		vec.push_back(i);
	}

	printCollection(vec);

	change(vec, 5);
	printCollection(vec);
}
