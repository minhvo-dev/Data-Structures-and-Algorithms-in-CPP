/*
 *	File name:	"experimental_avl_tree.hpp"
 *	Date:		4/21/2020 7:03:03 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of AVL tree - auto-balancing binary search tree
 */

#pragma once

#ifndef _EXPERIMENTAL_AVL_TREE_HPP_
#define _EXPERIMENTAL_AVL_TREE_HPP_

#include "../experimental_miscellanious_algorithms.hpp"
#include "../experimental_alias_declarations.hpp"

#include <functional>

namespace experimental {

	template<typename T, typename Comparator = std::less<T>>
	class AVLTree {
	private:
		/*  AVLNode class
			implement node idea in the AVL tree
		*/
		struct AVLNode {
			using value_type = T;
			using height_type = int;

			value_type value_;
			AVLNode *pLeft_;
			AVLNode *pRight_;
			height_type height_;	// height of the node in the AVL tree
									// start at 0, -1 if null

			AVLNode(value_type const &value, AVLNode *pLeft, AVLNode *pRight, int height = 0)
				: value_{ value }, pLeft_{ pLeft }, pRight_{ pRight }, height_{ height }{}
			AVLNode(value_type &&value, AVLNode *pLeft, AVLNode *pRight, int height = 0)
				: value_{ std::move(value) }, pLeft_{ pLeft }, pRight_{ pRight }, height_{ height }{}
		};

		using node = AVLNode;
		using node_ptr = node *;

	public:
		using value_type = typename node::value_type;
		using reference = value_type &;
		using const_reference = value_type const &;
		using size_type = alias::size_type;
		using height_type = typename AVLNode::height_type;

		/* The Big-Five */
		// ======================================================================

		~AVLTree() { clear(pRoot_); }

		AVLTree() noexcept
			: pRoot_{ nullptr }, cmp_{} {}

		AVLTree(AVLTree const &avl) 
			: pRoot_{ clone(avl.pRoot_) }, cmp_{ avl.cmp_ } {}

		AVLTree(AVLTree &&avl) noexcept
			: pRoot_{ avl.pRoot_ }, cmp_{ std::move(avl.cmp_) } {}

		AVLTree& operator=(AVLTree const &rhs) {
			if (this != &rhs) {
				clear(pRoot_);
				pRoot_ = clone(rhs.pRoot_);
				cmp_ = rhs.cmp_;
			}
			return *this;
		}

		AVLTree& operator=(AVLTree &&rhs) {
			using std::swap;
			swap(pRoot_, rhs.pRoot_);
			swap(cmp_, rhs.cmp_);
			return *this;
		}

		/* Capacity operations */
		// ======================================================================

		// query if the tree is empty
		bool empty() const {
			return pRoot_ == nullptr;
		}

		size_type size() const {
			return size(pRoot_);
		}

		/* Modifying operations */
		// ======================================================================

		// insert 'value' into a AVL tree
		void insert(const_reference value) {
			insert(value, pRoot_);
		}
		void insert(value_type &&value) {
			insert(std::move(value), pRoot_);
		}

		// remove 'value' from a AVL tree
		// do nothing if the value does not exist
		void remove(const_reference value) {
			remove(value, pRoot_);
		}

		// remove all nodes from the AVL tree
		void clear() {
			clear(pRoot_);
		}

		/* Search operations */
		// ======================================================================

		// query if the 'value' exists in the AVL tree
		bool contains(const_reference value) const {
			return contains(value, pRoot_);
		}

		/* Other operations */
		// ======================================================================

		// query the height of the tree
		height_type height() const {
			return height(pRoot_);
		}
		
		// print the BST to 'os' stream using preorder traversal
		void print_tree(std::ostream &out = std::cout) const {
			print_tree(pRoot_, out);
		}

	private:
		// return the number of node in the tree
		// return 0 if the tree is empty
		size_type size(node_ptr p) const {
			if (p == nullptr) {
				return 0;
			}
			return 1 + size(p->pLeft_) + size(p->pRight_);
		}

		// return the height of node p or -1 if nullptr
		height_type height(node_ptr p) const {
			return p == nullptr ? -1 : p->height_;
		}

		// insert 'value' into an AVL tree which starts at node 'r'
		// the tree will remain balance condition
		void insert(const_reference value, node_ptr &r) {
			if (r == nullptr)
				r = new node(value, nullptr, nullptr);
			else if (cmp_(value, r->value_)) {
				insert(value, r->pLeft_);
			}
			else if (cmp_(r->value_, value)) {
				insert(value, r->pRight_);
			}
			else {
				; // duplicate
			}
			balance(r);
		}

		// balance an un-balanced a sub AVL tree which starts at node 'r'
		// precondition: the sub tree must be already balanced or within one from being balanced
		void balance(node_ptr &r) {
			if (r == nullptr) return;

			if (height(r->pLeft_) - height(r->pRight_) > 1) {
				// unbalanced on left subtree
				if (height(r->pLeft_->pLeft_) >= height(r->pLeft_->pRight_)) {
					// case 1: left-left
					single_rotate_left(r);
				}
				else {
					// case 2: left-right
					double_rotate_left(r);
				}
			}
			else if (height(r->pRight_) - height(r->pLeft_) > 1) {
				// unbalanced on right subtree
				if (height(r->pRight_->pRight_) >= height(r->pRight_->pLeft_)) {
					// case 4: right-right
					single_rotate_right(r);
				}
				else {
					// case 3: right-left
					double_rotate_right(r);
				}
			}
			else {
				; // still balanced
			}

			r->height_ = max(height(r->pLeft_), height(r->pRight_)) + 1;
		}

		// rotate a sub binary tree
		// case 1: left-left unbalanced
		void single_rotate_left(node_ptr &r) {
			auto leftR = r->pLeft_;
			r->pLeft_ = leftR->pRight_;
			leftR->pRight_ = r;

			// update height of the modified nodes
			r->height_ = max(height(r->pLeft_), height(r->pRight_)) + 1;
			leftR->height_ = max(height(leftR->pLeft_), height(leftR->pRight_)) + 1;

			// update new root
			r = leftR;
		}

		// rotate a sub binary tree
		// case 4: right-right unbalanced
		void single_rotate_right(node_ptr &r) {
			auto rightR = r->pRight_;
			r->pRight_ = rightR->pLeft_;
			rightR->pLeft_ = r;

			// update height of the modified nodes
			r->height_ = max(height(r->pLeft_), height(r->pRight_)) + 1;
			rightR->height_ = max(height(rightR->pLeft_), height(rightR->pRight_)) + 1;

			// update new root
			r = rightR;
		}

		// rotate a sub binary tree
		// case 2: left-right unbalanced
		void double_rotate_left(node_ptr &r) {
			single_rotate_right(r->pLeft_);
			single_rotate_left(r);
		}

		// rotate a sub binary tree
		// case 3: right-left unbalanaced
		void double_rotate_right(node_ptr &r) {
			single_rotate_left(r->pRight_);
			single_rotate_right(r);
		}


		// detach left-most node
		// return the pointer to that node
		// return nullptr if the tree is empty
		node_ptr detach_left_most_node(node_ptr &r) {
			if (r == nullptr) return nullptr;
			if (r->pLeft_ == nullptr) {
				auto cpy = r;
				r = nullptr;
				return cpy;
			}
			return detach_left_most_node(r->pLeft_);
		}

		// remove 'value' from a sub AVL tree which starts at 'r'
		// if the tree does not contain value then do nothing
		// the balance condition is maintained
		// root might be re-set
		void remove(const_reference value, node_ptr &r) {
			if (r == nullptr) return;
			if (cmp_(value, r->value_)) {
				remove(value, r->pLeft_);
			}
			else if (cmp_(r->value_, value)) {
				remove(value, r->pRight_);
			}
			else if (r->pLeft_ != nullptr && r->pRight_ != nullptr) {
				// remove node with two children
				// - detach the minimum node from the right child
				// - replace the value of the deleting node with the detached node value
				auto p = detach_left_most_node(r->pRight_);
				r->value_ = std::move(p->value_);
				delete p;
				p = nullptr;
			}
			else {
				// remove node with at most one child
				// - replace the node by its child
				auto delNode = r;
				r = (r->pLeft_ == nullptr ? r->pRight_ : r->pLeft_);
				delete delNode;
				delNode = nullptr;
			}

			// rebalance the tree
			balance(r);
		}

		// remove all nodes from the AVL tree
		void clear(node_ptr &r) {
			if (r != nullptr) {
				clear(r->pLeft_);
				clear(r->pRight_);
				delete r;
				r = nullptr;
			}
		}

		// clone a sub tree
		// make a deep copy of all nodes in the tree
		node_ptr clone(node_ptr r) const {
			if (r == nullptr) return nullptr;
			return new node(r->value_, clone(r->pLeft_), clone(r->pRight_), r->height_);
		}

		// query if 'value' exists in a sub BST which starts at node 'r'
		// precondition: value_type must support Comparator(value_type, value_type)
		bool contains(const_reference value, node_ptr r) const {
			if (r == nullptr) return false;
			if (cmp_(value, r->value_)) return contains(value, r->pLeft_);
			else if (cmp_(r->value_, value)) return contains(value, r->pRight_);
			return true;
		}

		// print the sub BST which starts at node 'r' to 'os' stream
		// preorder traversal
		void print_tree(node_ptr r, std::ostream &os) const {
			if (r != nullptr) {
				os << r->value_ << ' ';
				print_tree(r->pLeft_, os);
				print_tree(r->pRight_, os);
			}
		}

		node_ptr pRoot_;
		Comparator cmp_;
	};
}

#endif // !_EXPERIMENTAL_AVL_TREE_HPP_
