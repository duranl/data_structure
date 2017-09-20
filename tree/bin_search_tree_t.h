/*
 * bin_search_tree_t.h
 *
 *  Created on: 2017年9月20日
 *      Author: duranl
 */

#ifndef TREE_BIN_SEARCH_TREE_T_H_
#define TREE_BIN_SEARCH_TREE_T_H_

#include <cstdlib>
#include <iostream>

template <typename _Comparable, typename _Comparator=std::less<_Comparable> >
class bin_search_tree_t
{
public:
	bin_search_tree_t();
	bin_search_tree_t(const bin_search_tree_t &rhs);
	~bin_search_tree_t()
	{
		make_empty();
	}

	/**
	 * Return the minimum item in the tree.
	 */
	const _Comparable &find_min() const
	{
		return find_min(root)->element;
	}
	/**
	 * Return the maximum item in the tree.
	 */
	const _Comparable &find_max() const
	{
		return find_max(root)->element;
	}
	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains(const _Comparable &x) const
	{
		return contains(x, root);
	}
	bool is_empty() const
	{
		return root == NULL;
	}
	/**
	 * Print the tree contents in sorted order.
	 */
	void print_tree() const
	{
		if (is_empty())
			std::cout << "Empty tree" << std::endl;
		else
			print_tree(root);
	}

	/**
	 * Return the height of the tree.
	 */
	int height() const
	{
		return height(root);
	}

	void make_empty()
	{
		make_empty(root);
	}
	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert(const _Comparable &x)
	{
		insert(x, root);
	}
	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove(const _Comparable &x)
	{
		remove(x, root);
	}

	/**
	 * Deep copy.
	 */
	const bin_search_tree_t &operator=(const bin_search_tree_t &rhs)
	{
		if (this != &rhs) {
			make_empty();
			root = clone(rhs.root);
		}
		return *this;
	}

private:
	struct bin_node
	{
		_Comparable element;
		bin_node *left;
		bin_node *right;

		bin_node(const _Comparable &the_element, bin_node *l, bin_node *r)
			: element(the_element), left(l), right(r) { }
	};

	bin_node *root;
	_Comparator is_less_than;

	/**
	 * Internal method to compute the height of a subtree rooted at t.
	 */
	int height(bin_node *t) const
	{
		if (t == NULL)
			return -1;
		else
			return 1 + max(height(t->left), height(t->right));
	}

	/**
	 * Internal method to insert x into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(const _Comparable &x, bin_node *&t)
	{
		if (t == NULL)
			t = new bin_node(x, NULL, NULL);
		else if (is_less_than(x, t->element))
			insert(x, t->left);
		else if (is_less_than(t->element, x))
			insert(x, t->right);
		else
			; // Duplicate; do nothing
	}

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void remove(const _Comparable &x, bin_node *&t)
	{
		if (t == NULL)
			return; // Item not found; Do nothing;
		if (is_less_than(x, t->element))
			remove(x, t->left);
		else if (is_less_than(t->element, x))
			remove(x, t->right);
		else if (t->left != NULL && t->right != NULL) { // Two children
			t->element = find_min(t->right)->element;
			remove(t->element, t->right);
		} else {
			bin_node *old_node = t;
			t = (t->left != NULL) ? t->left : t->right;
			delete old_node;
		}


	}
	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	bin_node *find_min(bin_node *t) const
	{
		if (t == NULL)
			return NULL;
		if (t->left == NULL)
			return t;
		return find_min(t->left);
	}
	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	bin_node *find_max(bin_node *t) const
	{
		if (t != NULL)
			while (t->right != NULL)
				t = t->right;
		return t;
	}
	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the subtree.
	 */
	bool contains(const _Comparable &x, bin_node *t) const
	{
		if (t == NULL)
			return false;
		else if (is_less_than(x, t->element))
			return contais(x, t->left);
		else if (is_less_than(t->element, x))
			return contains(x, t->right);
		else
			return true;	// Match
	}
	/**
	 * Internal method to make subtree empty.
	 */
	void make_empty(bin_node *&t)
	{
		if (t != NULL) {
			make_empty(t->left);
			make_empty(t->right);
			delete t;
			t = NULL;
		}
	}
	/**
	 * Internal method to print a subtree rooted at t in sorted order.
	 */
	void print_tree(bin_node *t) const
	{
		if (t != NULL) {
			print_tree(t->left);
			std::cout << t->element << std::endl;
			print_tree(t->right);
		}
	}

	/**
	 * Internal method to clone subtree.
	 */
	bin_node *clone(bin_node *t) const
	{
		if (t == NULL)
			return NULL;
		return new bin_node(t->element, clone(t->left), clone(t->right));
	}

};

#endif /* TREE_BIN_SEARCH_TREE_T_H_ */
