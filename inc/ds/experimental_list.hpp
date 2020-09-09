/*
 *	File name:	"experimental_list.hpp"
 *	Date:		4/2/2020 8:21:28 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of list ADT using double linked list
 */

#pragma once

#ifndef _EXPERIMENTAL_LIST_HPP_
#define _EXPERIMENTAL_LIST_HPP_

#include "../experimental_alias_declarations.hpp"

#include <utility>
#include <cassert>
#include <initializer_list>

#ifdef _LIST_UNINITIALIZED_ITERATOR_ASSERT_
#undef _LIST_UNINITIALIZED_ITERATOR_ASSERT_
#endif
// assert if iterator is uninitialized
#define _LIST_UNINITIALIZED_ITERATOR_ASSERT_(it) assert((it).pList_ != nullptr && (it).pCurrent_ != nullptr && "iterator is not initialized") 

namespace experimental {
	/* 	List ADT class
		provides a generic container with non-contiguous memory block
	*/
	template<typename T>
	class List {
	private:
		/*	Node class
			implement the idea of a node in doubly linked list
		*/
		struct Node {
			using value_type = T;

			value_type data_;
			Node *prev_;
			Node *next_;

			Node(value_type const &data = T{}, Node *prev = nullptr, Node *next = nullptr) noexcept
				: data_{ data }, prev_{ prev }, next_{ next }{}
			Node(value_type &&data, Node *prev = nullptr, Node *next = nullptr) noexcept
				: data_{ std::move(data) }, prev_{ prev }, next_{ next }{}
		};

		/*	ConstIterator class
			provides a wrapper of pointer to const that points to nodes in List ADT
			and basic operations
		*/
		class ConstIterator {
		public:
			using value_type = typename Node::value_type;
			using reference = value_type &;
			using const_reference = value_type const &;

			// Default constructor
			ConstIterator() = delete;

			/* Operator overloadings */
			// ======================================================================

			// dereference operator
			const_reference operator*() const {
				return retrieve();
			}
			// prefix increment operator
			ConstIterator& operator++() {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pList_->afterTail_ && "cannot increment pass the end");
				pCurrent_ = pCurrent_->next_;
				return *this;
			}
			// postfix increment operator
			ConstIterator operator++(int) {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pList_->afterTail_ && "cannot increment pass the end");
				auto old = *this;
				++(*this);
				return old;
			}
			// prefix decrememnt
			ConstIterator& operator--() {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pList_->beforeHead_ && "cannot decrement pass the head");
				pCurrent_ = pCurrent_->prev_;
				return *this;
			}
			// postfix decrement
			ConstIterator operator--(int) {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pList_->beforeHead_ && "cannot decrement pass the head");
				ConstIterator old = *this;
				--(*this);
				return old;
			}
			// equal operator
			bool operator==(ConstIterator const &rhs) const {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(rhs);
				assert(pList_ == rhs.pList_ && "compare mismatched iterators");
				return pCurrent_ == rhs.pCurrent_;
			}
			// not equal operator
			bool operator!=(ConstIterator const &rhs) const {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(rhs);
				assert(pList_ == rhs.pList_ && "compare mismatched iterators");
				return pCurrent_ != rhs.pCurrent_;
			}

		protected:
			List<value_type> const *pList_;
			Node *pCurrent_;

			ConstIterator(List<value_type> const *pList, Node *p) noexcept
				: pList_{ pList }, pCurrent_{ p } {}

			// retrieve data of the current iterator
			reference retrieve() const {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				return pCurrent_->data_;
			}
			
			/* Friend classes */
			// ====================================================================== 
			friend class List<value_type>;
		};

		/*	Iterator class
			inherit from ConstIterator class
			point to non-const
		*/
		class Iterator : public ConstIterator {
		public:
			using value_type = typename ConstIterator::value_type;
			using reference = typename ConstIterator::reference;
			using const_reference = typename ConstIterator::const_reference;

			// Default constructor
			Iterator() = delete;

			/* Operator overloadings */
			// ======================================================================

			// dereference operator
			reference operator*() {
				return ConstIterator::retrieve();
			}
			const_reference operator*() const {
				return ConstIterator::operator*();
			}

			// prefix increment
			Iterator& operator++() {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pList_->afterTail_ && "cannot increment pass the end");
				pCurrent_ = pCurrent_->next_; 
				return *this;
			}
			// postfix increment
			Iterator operator++(int) {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pList_->afterTail_ && "cannot increment pass the end");
				iterator old = *this;
				++(*this);
				return old;
			}
			// prefix decrememnt
			Iterator& operator--() {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pList_->beforeHead_ && "cannot decrement pass the head");
				pCurrent_ = pCurrent_->prev_; 
				return *this;
			}
			// postfix decrement
			Iterator operator--(int) {
				_LIST_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pList_->beforeHead_ && "cannot decrement pass the head");
				Iterator old = *this;
				pCurrent_ = pCurrent_->prev_;
				return old;
			}

		protected:
			using ConstIterator::pList_;
			using ConstIterator::pCurrent_;

			Iterator(List<value_type> const *pList, Node *p) noexcept
				: ConstIterator{ pList, p } {}

			/* Friend classes */
			// ====================================================================== 
			friend class List<value_type>;
		};

	public:
		using size_type = alias::size_type;
		using value_type = typename Node::value_type;
		using reference = value_type &;
		using const_reference = value_type const &;
		using iterator = Iterator;
		using const_iterator = ConstIterator;

		/* The Big-Five */
		// ======================================================================

		~List() {
			clear();
			delete beforeHead_;
			delete afterTail_;
		}

		List() {
			init();
		}

		List(List const &l) {
			init();
			for (auto &e : l) {
				push_back(e);
			}
		}

		List(List &&l) noexcept
			: size_{ l.size_ }, beforeHead_{ l.beforeHead_ }, afterTail_{ l.afterTail_ } {
			l.size_ = 0;
			l.beforeHead_ = nullptr;
			l.afterTail_ = nullptr;
		}

		List& operator=(List const &rhs) {
			List cpy = rhs; // expensive operation
			using std::swap;
			swap(*this, cpy);
			return *this;
		}

		List& operator=(List &&rhs) noexcept {
			using std::swap;
			swap(size_, rhs.size_);
			swap(beforeHead_, rhs.beforeHead_);
			swap(afterTail_, rhs.afterTail_);
			return *this;
		}

		/* Custom constructor */
		// ======================================================================

		explicit List(std::initializer_list<T> const &ul) {
			init();
			for (auto const &e : ul) {
				push_back(e);
			}
		}

		explicit List(std::initializer_list<T> &&ul) {
			init();
			for (auto &&e : ul) {
				push_back(std::move(e));
			}
		}

		/* Element access */
		// ======================================================================

		// access the first element of the list
		// do not check if the list is empty
		reference front() {
			return *begin();
		}
		const_reference front() const {
			return *begin();
		}
		// access the last element of the list
		// do not check if the list is empty
		reference back() {
			return *--end();
		}
		const_reference back() const {
			return *--end();
		}

		/* Capacity operations */
		// ======================================================================

		// query the size of the list
		size_type size() const {
			return size_;
		}
		// check if the list is empty
		bool empty() const {
			return size() == 0;
		}

		/* Modifying operations */
		// ======================================================================

		// insert item before the iterator it
		// return the iterator that points to the new item in the list
		iterator insert(iterator it, value_type const &item) {
			_LIST_UNINITIALIZED_ITERATOR_ASSERT_(it);
			assert(it.pList_ == this && "cannot insert into different lists");
			assert(it.pCurrent_ != beforeHead_ && "cannot insert before before-head");
			
			auto p = it.pCurrent_;
			++size_;
			return iterator(this, p->prev_ = p->prev_->next_ = new Node{ item, p->prev_, p });
		}
		iterator insert(iterator it, value_type &&item) {
			_LIST_UNINITIALIZED_ITERATOR_ASSERT_(it);
			assert(it.pList_ == this && "cannot insert into different lists");
			assert(it.pCurrent_ != beforeHead_ && "cannot insert before before-head");

			auto p = it.pCurrent_;
			++size_;
			return iterator(this, p->prev_ = p->prev_->next_ = new Node{ std::move(item), p->prev_, p });
		}
		// remove the element pointed by the iterator from the list
		// return the iterator that points to the next element of the list
		iterator erase(iterator it) {
			_LIST_UNINITIALIZED_ITERATOR_ASSERT_(it);
			assert(it.pList_ == this && "cannot erase iterator from different lists");
			assert(it.pCurrent_ != beforeHead_ && it.pCurrent_ != afterTail_ && "cannot erase pass-the-end");

			auto p = it.pCurrent_;
			auto retVal = ++it;
			p->prev_->next_ = p->next_;
			p->next_->prev_ = p->prev_;
			delete p;
			--size_;
			return retVal;
		}
		// remove elements from 'from' to, but not include, 'to' [from, to) from the list
		// return 'to' iterator
		iterator erase(iterator from, iterator to) {
			_LIST_UNINITIALIZED_ITERATOR_ASSERT_(from);
			_LIST_UNINITIALIZED_ITERATOR_ASSERT_(to);
			assert(from.pList_ == this && to.pList_ == this && "cannot erase iterators from different lists");
			assert(from.pCurrent_ != beforeHead_ && "cannot erase from before-head");

			for (; from != to; from = erase(from));
			return to;
		}

		// add item to the front of the list
		void push_front(value_type const &item) {
			insert(begin(), item);
		}
		void push_front(value_type &&item) {
			insert(begin(), std::move(item));
		}
		// add item to the back of the list
		void push_back(value_type const &item) {
			insert(end(), item);
		}
		void push_back(value_type &&item) {
			insert(end(), std::move(item));
		}
		// remove the first element of the list
		// do not check if the list is empty
		void pop_front() {
			erase(begin());
		}
		// remove the last element of the list
		// do not check if the list is empty
		void pop_back() {
			erase(--end());
		}
		// remove all the elements of the list
		void clear() {
			if (size_ > 0) {
				erase(begin(), end());
			}
		}

		/* Iterator operations */
		// ======================================================================

		// get the iterator pointing to the first element of the list
		// do not check if the list is empty
		iterator begin() {
			return iterator{ this, beforeHead_->next_ };
		}
		const_iterator begin() const {
			return const_iterator{ this, beforeHead_->next_ };
		}
		const_iterator cbegin() const {
			return begin();
		}
		// get the iterator pointing to the pass-the-last-element of the list
		iterator end() {
			return iterator{ this, afterTail_ };
		}
		const_iterator end() const {
			return iterator{ this, afterTail_ };
		}
		const_iterator cend() const {
			return end();
		}

	private:
		size_type size_;
		Node *beforeHead_;
		Node *afterTail_;

		// create an empty list
		void init() {
			size_ = 0;
			beforeHead_ = new Node{};
			afterTail_ = new Node{};
			beforeHead_->next_ = afterTail_;
			afterTail_->prev_ = beforeHead_;
		}
	};


}

#undef _LIST_UNINITIALIZED_ITERATOR_ASSERT_

#endif // !_EXPERIMENTAL_LIST_HPP_
