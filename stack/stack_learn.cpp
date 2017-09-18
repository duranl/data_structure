/*
 * stack_learn.cpp
 *
 *  Created on: 2017年9月18日
 *      Author: duranl
 */

#include "stack_learn.h"
#include "stack_t.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

void check_the_symbol(string input)
{
	stack_t<char> char_stack;
	for (string::iterator iter = input.begin();
			iter != input.end(); ++iter) {
		if (*iter == '(')
			char_stack.push('(');
		else if (*iter == ')')
			char_stack.pop();
	}
	if (char_stack.empty() == true)
		cout << "the express is valid";
	else
		cout << "the express is unvalid";
}

void cal_postfix(string input)
{
	// stringstream str_stream(input);
	stack_t<int> op_stack;
	int cur_num = 0;
	int ret = 0;
	for (string::iterator iter = input.begin();
			iter != input.end(); iter++) {
		if (*iter > '0' && *iter < '9') {
			cur_num = cur_num * 10 + (*iter) - '0';
		} else if (*iter == ' ') {
			op_stack.push(cur_num);
			cur_num = 0;
		} else {
			int &tmp = op_stack.top();
			op_stack.pop();
			switch (*iter) {
			case '+':
				ret = tmp + cur_num;
				break;
			case '-':
				ret = tmp - cur_num;
				break;
			case '*':
				ret = tmp * cur_num;
				break;
			case '/':
				ret = tmp / cur_num;
				break;
			}
			op_stack.push(ret);
			cur_num = 0;
		}
	}
	cout << op_stack.top();
}

void infix_to_suffix(string input)
{
	int hash[256];
	hash['+'] = 1;
	hash['*'] = 2;
	hash['('] = 0;
	for (string::iterator iter = input.begin();
			iter != input.end(); iter++) {

	}
}

void stack_test()
{
	char buffs[256];

	cin.getline(buffs, 256);
	string input(buffs);
	cal_postfix(input);
}
