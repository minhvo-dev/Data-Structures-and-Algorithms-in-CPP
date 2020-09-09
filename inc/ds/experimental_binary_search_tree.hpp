/*
 *	File name:	"experimental_binary_search_tree.hpp"
 *	Date:		4/18/2020 4:29:48 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of binary search tree
 */

#pragma once

#ifndef _EXPERIMENTAL_BINARY_SEARCH_TREE_HPP_
#define _EXPERIMENTAL_BINARY_SEARCH_TREE_HPP_

#include "../experimental_alias_declarations.hpp"

#include <utility>
#include <iostream>
#include <functional>

namespace experimental {

	/*  BinarySearchTree class
		provides basic operations of a binary search tree
		The order is determined by Comparator object
	*/
	template<typename T, typename Comparator = std::less<T>>
	class BinarySearchTree {

	private:
		/*  BinaryNode class
			implement node idea in a binary search tree
		*/
		struct BinaryNode {
			using value_type = T;

			value_type value_;
			BinaryNode *pLeft_;
			BinaryNode *pRight_;

			BinaryNode(value_type const &data, BinaryNode *pLeft, BinaryNode *pRight)
				: value_{ data }, pLeft_{ pLeft }, pRight_{ pRight }{}
			BinaryNode(value_type &&data, BinaryNode *pLeft, BinaryNode *pRight)
				: value_{ std::move(data) }, pLeft_{ pLeft }, pRight_{ pRight }{}
		};

		using node = BinaryNode;
		using node_ptr = node *;

	public:
		using value_type = typename node::value_type;
		using reference = value_type &;
		using const_reference = value_type const &;
		using size_type = alias::size_type;

		/* The Big-Five */
		// ======================================================================
		~BinarySearchTree() { clear(pRoot_); }

		BinarySearchTree()
			: pRoot_{ nullptr }, cmp_{} {}

		BinarySearchTree(BinarySearchTree const &bst)
			: pRoot_{ clone(bst.pRoot_) }, cmp_{ bst.cmp_ } {}

		BinarySearchTree(BinarySearchTree &&bst) noexcept
			: pRoot_{ bst.pRoot_ }, cmp_{ std::move(bst.cmp_) } {
			bst->pRoot_ = nullptr;
		}

		BinarySearchTree& operator=(BinarySearchTree const &rhs) {
			if (this != &rhs) {
				clear();
				pRoot_ = clone(rhs.pRoot_);
				cmp_ = rhs.cmp_;
			}
			return *this;
		}

		BinarySearchTree& operator=(BinarySearchTree &&rhs) noexcept {
			using std::swap;
			swap(pRoot_, rhs.pRoot_);
			swap(cmp_, rhs.cmp_);
			return *this;
		}

		/* Capacity operations */
		// ======================================================================

		bool empty() const { 
			return pRoot_ == nullptr;
		}

		size_type size() const {
			return size(pRoot_);
		}

		/* Modifying operations */
		// ======================================================================

		// insert 'value' into a BST
		void insert(const_reference value) {
			insert(value, pRoot_);
		}
		void insert(value_type &&value) {
			insert(std::move(value), pRoot_);
		}

		// remove 'value' from a BST
		// do nothing if the value does not exist
		void remove(const_reference value) {
			remove(value, pRoot_);
		}

		// remove all nodes from the BST
		void clear() {
			clear(pRoot_);
		}

		/* Search operations */
		// ======================================================================

		// find the minimun value of a BST
		const_reference find_min() {
			return find_min(pRoot_)->value_;
		}

		// find the maximum value of a BST
		const_reference find_max() {
			return find_max(pRoot_)->value_;
		}

		// query if 'value' exists in the BST
		bool contains(const_reference value) const {
			return contains(value, pRoot_);
		}

		/* Display operations */
		// ======================================================================

		// print the BST to 'os' stream using preorder traversal
		void print_tree(std::ostream &out = std::cout) const {
			print_tree(pRoot_, out);
		}

	
	private:
		/* Internal methods */
		// ======================================================================

		// get the size of the subtree which starts at node 'r'
		// return 0 if r is nullptr
		size_type size(node_ptr r) const {
			if (r == nullptr) {
				return 0;
			}
			return 1 + size(r->pLeft_) + size(r->pRight_);
		}

		// insert 'value' to a sub BST which starts at node 'r'
		// the root might be modified
		void insert(const_reference value, node_ptr &r) {
			if (r == nullptr) {
				r = new node(value, nullptr, nullptr);
			}
			else if (cmp_(value, r->value_)) {
				insert(value, r->pLeft_);
			}
			else if (cmp_(r->value_, value)) {
				insert(value, r->pRight_);
			}
			else {
				; // duplicate
			}
		}
		void insert(value_type &&value, node_ptr &r) {
			if (r == nullptr) {
				r = new node(std::move(value), nullptr, nullptr);
			}
			else if (cmp_(value, r->value_)) {
				insert(std::move(value), r->pLeft_);
			}
			else if (cmp_(r->value_, value)) {
				insert(std::move(value), r->pRight_);
			}
			else {
				; // duplicate
			}
		}

		// detach the left-most node of a BST
		// return the pointer to that node
		// return nullptr if the BST is empty
		node_ptr detach_left_most_node(node_ptr &r) {
			if (r == nullptr) return nullptr;
			if (r->pLeft_ == nullptr) {
				auto retVal = r;
				r = nullptr;
				return retVal;
			}
			return detach_left_most_node(r->pLeft_);
		}

		// remove 'value' from a sub BST which starts at node 'r'
		// the root might be modified
		void remove(const_reference value, node_ptr &r) {
			if (r == nullptr) return; // empty tree, do nothing
			if (cmp_(value, r->value_)) remove(value, r->pLeft_);
			else if (cmp_(r->value_, value)) remove(value, r->pRight_);
			else if (r->pLeft_ != nullptr && r->pRight_ != nullptr) {
				// delete node which has 2 children
				// - detach left-most node from the right subtree 
				// - replace the deleting node value by the detached node value
				auto minRight = detach_left_most_node(r->pRight_);
				r->value_ = std::move(minRight->value_);
				delete minRight;
				minRight = nullptr;
			}
			else {
				// delete node which has at most one child
				// - replace the node by its child
				auto delNode = r; // make a copy
				r = (r->pLeft_ != nullptr) ? r->pLeft_ : r->pRight_;
				delete delNode;
				delNode = nullptr;
			}
		}

		// remove all nodes from a sub BST which starts at node 'r'
		void clear(node_ptr &r) {
			if (r != nullptr) {
				clear(r->pLeft_);
				clear(r->pRight_);
				delete r;
				r = nullptr;
			}
		}

		// find the node that contains minimum value of a sub BST which starts at node 'r'
		// return node pointer containing the 'smallest' item
		node_ptr find_min(node_ptr r) const {
			if (r != nullptr) {
				if (r->pLeft_ != nullptr && cmp_(r->pLeft_->value_, r->value_)) {
					for (; r->pLeft_ != nullptr; r = r->pLeft_) {}
				}
				if (r->pRight_ != nullptr && cmp_(r->pRight_->value_, r->value_)) {
					for (; r->pRight_ != nullptr; r = r->pRight_) {}
				}
			}
			return r;
		}
		// find the node that contains maximum value of a sub BST which starts at node 'r'
		// return node pointer containing the 'largest' item
		node_ptr find_max(node_ptr r) const {
			if (r != nullptr) {
				for (; r->pRight_ != nullptr; r = r->pRight_);
			}
			return r;
		}

		// query if 'value' exists in a sub BST which starts at node 'r'
		// Precondition: value_type must support Comparator(value_type, value_type)
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

		// clone a BST whose root is 'r'
		// make deep copy of all node in the BST started at r
		node_ptr clone(node_ptr r) const {
			if (r == nullptr) return nullptr;
			return new node{ r->value_, clone(r->pLeft_), clone(r->pRight_) };
		}

		node_ptr pRoot_;
		Comparator cmp_;
	};

}
#endif // !_EXPERIMENTAL_BINARY_SEARCH_TREE_HPP_
