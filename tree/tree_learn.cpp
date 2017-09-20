/*
 * tree_learn.cpp
 *
 *  Created on: 2017年9月20日
 *      Author: duranl
 */

#include "tree_learn.h"
#include "../stack/stack_t.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

template <typename _Object>
class bin_tree_node_t
{
public:
	_Object element;
	bin_tree_node_t *left;
	bin_tree_node_t *right;
	bin_tree_node_t() { left = NULL, right = NULL;}
	bin_tree_node_t(const bin_tree_node_t &rhs)
	{
		operator=(rhs);
	}
	bin_tree_node_t(const _Object element,
			bin_tree_node_t *left, bin_tree_node_t *right) :
				element(element), left(left), right(right)
	{}

	const bin_tree_node_t &operator=(const bin_tree_node_t &rhs)
	{
		if (this != &rhs) {
			element = rhs.element;
			left = rhs.left;
			right = rhs.right;
		}
		return *this;
	}
};

template <typename _Object>
void inorder_traversal(const bin_tree_node_t<_Object> *root) {
	if (root == NULL)
		return;
	inorder_traversal(root->left);
	cout << root->element;
	inorder_traversal(root->right);
}

void express_tree(const string &input)
{
	stack_t<bin_tree_node_t<string> > op_stack;
	stringstream strstream;
	bin_tree_node_t<string> *new_node, *left, *right, *op;
	for (string::const_iterator iter = input.begin();
			iter != input.end(); iter++) {
		if (*iter == ' ') {
			string str;
			strstream >> str;
			new_node = new bin_tree_node_t<string>(str, NULL, NULL);
			op_stack.push(*new_node);
			strstream.clear();
		} else if (*iter == '+' || *iter == '*') {
			right = new bin_tree_node_t<string>(op_stack.pop());
			left = new bin_tree_node_t<string>(op_stack.pop());
			string op_val;
			strstream << *iter;
			strstream >> op_val;
			op = new bin_tree_node_t<string>(op_val, left, right);
			op_stack.push(*op);
			strstream.clear();
		} else {
			strstream << *iter;
		}
	}

	bin_tree_node_t<string> root = op_stack.pop();
	inorder_traversal(&root);
}


void tree_test()
{
	char input[256];
	cin.getline(input, 255);
	string str(input);
	express_tree(str);
}
