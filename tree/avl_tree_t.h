/*
 * avl_tree_t.h
 *
 *  Created on: 2017年9月26日
 *      Author: duranl
 */

#ifndef TREE_AVL_TREE_T_H_
#define TREE_AVL_TREE_T_H_

#include <cstdlib>
#include <cmath>

template <typename _Comparable, typename _Comparator = std::less<_Comparable> >
class avl_tree_t
{
private:
	struct avl_node
	{
		_Comparable element;
		avl_node *left;
		avl_node *right;
		int height;

		avl_node(const _Comparable &the_element, avl_node *lt,
				avl_node *rt, int h = 0)
			: element(the_element), left(lt), right(rt), height(h)
		{ }
	};

	avl_node *root;
	_Comparator is_less_than;

	/**
	 * Rotate binary tree node with left child.
	 * For AVL trees, this is a single rotation for case 1.
	 * Update heights, then set new root.
	 */
	void rotate_with_left_child(avl_node *&k2)
	{
		avl_node *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = std::max(height(k2->left), height(k2->right)) + 1;
		k1->height = std::max(height(k1->left), height(k1->right)) + 1;
		k2 = k1;
	}


	/**
	 * Double rotate binary tree node: first left child
	 * with its right child; then node k3 with new left child.
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights, then set new root.
	 */
	void double_with_left_child(avl_node *&k3)
	{
		rotate_with_right_child(k3->left);
		rotate_with_left_child(k3);
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotate_with_right_child(avl_node *&k1)
	{
		avl_node *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = std::max(height(k1->left), height(k1->right)) + 1;
		k2->height = std::max(heigth(k2->left), height(k2->right)) + 1;
		k1 = k2;
	}

	/**
	 * Double rotate binary tree node: first right child
	 * with its left child; then node k2 with new right child.
	 * For AVL trees, this is a double rotation for case 3.
	 * Update heights, then set new root.
	 */
	void double_with_right_child(avl_node *&k2)
	{
		rotate_with_left_child(k2->right);
		rotate_with_right_child(k2);
	}

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(const _Comparable &x, avl_node *&t)
	{
		if (t == NULL)
			t = new avl_node(x, NULL, NULL);
		else if (is_less_than(x, t->element)) {
			insert(x, t->left);
			if (height(t->left) - height(t->right) == 2)
				if (is_less_than(x, t->left->element))
					rotate_with_left_child(t);
				else
					double_with_left_child(t);
		}
		else if (is_less_than(t->element, x)) {
			insert(x, t->right);
			if (height(t->right) - height(t->left) == 2)
				if (is_less_than(t->right->element, x))
					rotate_with_right_child(t);
				else
					double_with_right_child(t);
		}
		else
			; // Duplicate, do nothing
		t->height = std::max(height(t->left), height(t->right)) + 1;
	}

public:
	/**
	 * Return the height of node t or -1 if NULL.
	 */
	int height(avl_node *t) const
	{
		return t == NULL ? -1 : t->height;
	}

	void insert(_Comparable &x)
	{
		insert(x, root);
	}
};

#endif /* TREE_AVL_TREE_T_H_ */
