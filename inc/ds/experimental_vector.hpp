/*
 *	File name:	"experimental_vector.hpp"
 *	Date:		4/2/2020 9:29:35 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of vector ADT
 */

#pragma once

#ifndef _EXPERIMENTAL_VECTOR_HPP_
#define _EXPERIMENTAL_VECTOR_HPP_

#include "../experimental_alias_declarations.hpp"

#include <cassert>
#include <initializer_list>
#include <utility>

#ifdef _VECTOR_UNINITIALIZED_ITERATOR_ASSERT_
#undef _VECTOR_UNINITIALIZED_ITERATOR_ASSERT_
#endif
// assert if the iterator 'it' is not initialized
#define _VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(it) \
			assert((it).pVector_ \
					&& (it).pCurrent_ \
					&& "iterator is not initialized")

#ifdef _VECTOR_OUT_OF_BOUND_ITERATOR_ASSERT_
#undef _VECTOR_OUT_OF_BOUND_ITERATOR_ASSERT_
#endif
// assert if the iterator 'it' is out-of-bound
#define _VECTOR_OUT_OF_BOUND_ITERATOR_ASSERT_(it) \
			assert((it).pCurrent_ >= (it).pVector_->elements_ \
					&& (it).pCurrent_ <= &(it).pVector_->elements_[pVector_->size_] \
					&& "out-of-bound iterator access")

#ifdef _VECTOR_MISMATCHED_ITERATOR_ASSERT_
#undef _VECTOR__MISMATCHED_ITERATOR_ASSERT_
#endif
// assert if two iterators are from different vector
#define _VECTOR_MISMATCHED_ITERATOR_ASSERT_(itX, itY) \
			assert((itX).pVector_ == (itY).pVector_ \
					&& "cannot do operations on mismatched iterators")

namespace experimental {
	/* 	Vector ADT class
	 	provides a generic container with contiguous memory block
	*/
	template<typename T>
	class Vector {
	private:
		/*	ConstIterator class
			provides a wrapper of pointer to const that points to elements in Vector ADT
			and basic operations.
			Note:
			- Increment and decrement may cause overflow of arithmetic operations on numeric type.
		*/
		class ConstIterator {
		public:
			using value_type = T;
			using reference = value_type const &;
			using difference_type = alias::pointer_difference_type;

			// Default constructor
			ConstIterator() = delete;

			/* Operator overloadings */
			// ======================================================================

			// dereference operator
			reference operator*() const {
				return retrieve();
			}
			// prefix increment
			ConstIterator& operator++() {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				++pCurrent_;
				return *this;
			}
			// postfix increment
			ConstIterator operator++(int) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				ConstIterator old = *this;
				++(*this);
				return old;
			}
			// prefix decrement
			ConstIterator& operator--() {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				--pCurrent_;
				return *this;
			}
			// postfix decrement
			ConstIterator operator--(int) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				ConstIterator old = *this;
				--(*this);
				return old;
			}
			// equal operator
			bool operator==(ConstIterator const &rhs) const {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(rhs);
				_VECTOR_MISMATCHED_ITERATOR_ASSERT_(*this, rhs);
				return pCurrent_ == rhs.pCurrent_;
			}
			// not equal operator
			bool operator!=(ConstIterator const &rhs) const {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(rhs);
				_VECTOR_MISMATCHED_ITERATOR_ASSERT_(*this, rhs);
				return pCurrent_ != rhs.pCurrent_;
			}
			// less than operator
			bool operator<(ConstIterator const &rhs) const {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(rhs);
				_VECTOR_MISMATCHED_ITERATOR_ASSERT_(*this, rhs);
				return pCurrent_ < rhs.pCurrent_;
			}
			// greater than operator
			bool operator>(ConstIterator const &rhs) const {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(rhs);
				_VECTOR_MISMATCHED_ITERATOR_ASSERT_(*this, rhs);
				return pCurrent_ > rhs.pCurrent_;
			}
			// less than or equal operator
			bool operator<=(ConstIterator const &rhs) const {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(rhs);
				_VECTOR_MISMATCHED_ITERATOR_ASSERT_(*this, rhs);
				return pCurrent_ <= rhs.pCurrent_;
			}
			// greater than or equal operator
			bool operator>=(ConstIterator const &rhs) const {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(rhs);
				_VECTOR_MISMATCHED_ITERATOR_ASSERT_(*this, rhs);
				return pCurrent_ >= rhs.pCurrent_;
			}
			// increment operator
			ConstIterator operator+(alias::size_type n) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				return ConstIterator(pVector_, pCurrent_ + n);
			}
			ConstIterator operator+=(alias::size_type n) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				pCurrent_ += n;
				return *this;
			}
			// decrement operator
			ConstIterator operator-(alias::size_type n) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				return ConstIterator(pVector_, pCurrent_ - n);
			}
			ConstIterator operator-=(alias::size_type n) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				pCurrent_ -= n;
				return *this;
			}
			// arithmetic operator
			difference_type operator-(ConstIterator const &rhs) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(rhs);
				_VECTOR_MISMATCHED_ITERATOR_ASSERT_(*this, rhs);
				return pCurrent_ - rhs.pCurrent_;
			}


		protected:
			using pointer = value_type *;

			Vector<value_type> const *pVector_;
			pointer pCurrent_;

			ConstIterator(Vector<value_type> const *pVector, pointer p) noexcept
				: pVector_{ pVector }, pCurrent_{ p }{}

			value_type& retrieve() const {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_OUT_OF_BOUND_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != &pVector_->elements_[pVector_->size_] && "cannot dereference end-iterator");
				return *pCurrent_;
			}
			
			/* Friend classes */
			// ======================================================================
			friend class Vector<value_type>;

		};

		/*	Iterator class
			inherit from ConstIterator class
			point to non-const
			Note:
			- Increment and decrement may cause overflow of arithmetic operations on numeric type.
		*/
		class Iterator : public ConstIterator {
		public:
			using value_type = typename ConstIterator::value_type;
			using reference = typename value_type &;
			using const_reference = typename ConstIterator::reference;
			using pointer = typename ConstIterator::pointer;

			Iterator() = delete;

			/* Operator overloadings */
			// ======================================================================

			// dereference
			reference operator*() {
				return ConstIterator::retrieve();
			}
			const_reference operator*() const {
				return ConstIterator::operator*();
			}
			// prefix increment operator
			Iterator& operator++() {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_OUT_OF_BOUND_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != &pVector_->elements_[pVector_->size_] && "cannot increment iterator pass end");
				++pCurrent_;
				return *this;
			}
			// postfix increment operator 
			Iterator operator++(int) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_OUT_OF_BOUND_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != &pVector_->elements_[pVector_->size_] && "cannot increment iterator pass end");
				Iterator old = *this;
				++(*this);
				return old;
			}
			// prefix decrement operator
			Iterator& operator--() {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_OUT_OF_BOUND_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pVector_->elements_ && "cannot decrement iterator pass begin");
				--pCurrent_;
				return *this;
			}
			// postfix decrement operator
			Iterator operator--(int) {
				
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				_VECTOR_OUT_OF_BOUND_ITERATOR_ASSERT_(*this);
				assert(pCurrent_ != pVector_->elements_ && "cannot decrement iterator pass begin");
				Iterator old = *this;
				--(*this);
				return old;
			}
			// increment operator
			Iterator operator+(alias::size_type n) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				return Iterator(pVector_, pCurrent_ + n);
			}
			Iterator operator+=(alias::size_type n) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				pCurrent_ += n;
				return *this;
			}
			// decrement operator
			Iterator operator-(alias::size_type n) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				return Iterator(pVector_, pCurrent_ - n);
			}
			Iterator operator-=(alias::size_type n) {
				_VECTOR_UNINITIALIZED_ITERATOR_ASSERT_(*this);
				pCurrent_ -= n;
				return *this;
			}
			
			
		protected:
			// must declare names in base class here
			// look-up mechanism will not work without declaration
			using ConstIterator::pVector_;
			using ConstIterator::pCurrent_;

			Iterator(Vector<value_type> const *pVector, value_type *p) noexcept
				: ConstIterator(pVector, p) {}

			/* Friend classes */
			// ======================================================================
			friend class Vector<value_type>;

		};

	public:
		using value_type = T;
		using reference = value_type &;
		using const_reference = value_type const &;
		using size_type = alias::size_type;

		using iterator = Iterator;
		using const_iterator = ConstIterator;

		/* The Big-Five */
		// ===============================================================================
		~Vector() {
			delete[] elements_;
		}

		explicit Vector(size_type sz = 0)
			: size_{ sz }, capacity_{ sz }, elements_{ new value_type[sz] }{}

		Vector(Vector const &v)
			: size_{ v.size_ }, capacity_{ v.capacity_ }, elements_{ new value_type[v.size_] } {
			for (size_type i = 0; i < size_; ++i) {
				elements_[i] = v.elements_[i];
			}
		}

		Vector(Vector &&v) noexcept
			: size_{ v.size_ }, capacity_{ v.capacity_ }, elements_{ v.elements_ } {
			v.elements_ = nullptr;
			v.size_ = 0;
			v.capacity_ = 0;
		}

		Vector& operator=(Vector const &rhs) {
			if (this != &rhs) {
				delete[] elements_;
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				elements_ = new value_type[capacity_];
				for (size_type i = 0; i < size_; ++i) {
					elements_[i] = rhs.elements_[i];
				}
			}
			return *this;
		}

		Vector& operator=(Vector &&rhs) noexcept {
			using std::swap;
			swap(size_, rhs.size_);
			swap(capacity_, rhs.capacity_);
			swap(elements_, rhs.elements_);
			return *this;
		}

		/* Custom constructors */
		// ===============================================================================
		explicit Vector(std::initializer_list<value_type> const &l)
			: size_{ 0 }, capacity_{ l.size() }, elements_{ new value_type[l.size()] } {
			for (auto i = std::begin(l), end = std::end(l); i != end; ++i) {
				push_back(*i);
			}
		}

		explicit Vector(std::initializer_list<value_type> &&l)
			: size_{ 0 }, capacity_{ l.size() }, elements_{ new value_type[l.size()] } {
			for (auto i = std::begin(l), end = std::end(l); i != end; ++i) {
				push_back(std::move(*i));
			}
		}

		/* Element access */
		// ===============================================================================

		// Indexing: operator[]
		// return a reference to the element at index idx
		// do not check if the index is out-of-bound
		reference operator[](size_type idx) {
			return elements_[idx];
		}
		const_reference operator[](size_type idx) const {
			return elements_[idx];
		}

		// get the first element of the vector
		// do not check if the vector is empty
		reference front() {
			return elements_[0];
		}
		const_reference front() const {
			return elements_[0];
		}

		// get the last element of the vector
		// do not check if the vector is empty
		reference back() {
			return elements_[size() - 1];
		}
		const_reference back() const {
			return elements_[size() - 1];
		}

		/* Capacity operations */
		// ===============================================================================

		// query the size of the vector
		size_type size() const noexcept {
			return size_;
		}

		// query the capacity of the vector
		size_type capacity() const noexcept {
			return capacity_;
		}

		// check if the vector is empty
		// return true if empty, false otherwise
		bool empty() const noexcept {
			return size() == 0;
		}

		// reserve the capacity of the vector
		// if new capacity is greater than current capacity, move elements to new allocated memory
		// if new capacity is less than current capacity, do nothing
		void reserve(size_type newCapacity) {
			if (newCapacity > capacity()) {
				if (auto newArray = new value_type[newCapacity]) {
					for (size_type i = 0, sz = size(); i < sz; ++i) {
						newArray[i] = std::move(elements_[i]);
					}
					capacity_ = newCapacity;
					delete[] elements_;
					elements_ = newArray;
				}
			}
		}

		// resize the vector
		// increase the capacity to newsize x 1.5 if new size is greater than current size
		void resize(size_type newSize) {
			if (newSize > capacity()) {
				reserve(static_cast<size_type>(newSize * 1.5));
			}
			size_ = newSize;
		}

		/* Modifying operations */
		// ===============================================================================

		// add new element into the end of the vector
		// if the size == capacity, increase the capacity
		void push_back(value_type const &e) { // lvalue version
			if (size() == capacity()) {
				reserve(static_cast<size_type>(capacity() * 1.5) + 1);
			}
			elements_[size_++] = e;
		}
		void push_back(value_type &&e) { // rvalue version
			if (size() == capacity()) {
				reserve(static_cast<size_type>(capacity() * 1.5) + 1);
			}
			elements_[size_++] = std::move(e);
		}

		// remove the last element of the vector
		// do not check if the vector is empty
		void pop_back() {
			--size_;
		}

		// remove all the elements of the vector
		void clear() {
			size_ = 0;
		}

		/* Iterator operations */
		// ===============================================================================

		// get the iterator pointing at the begining of the vector
		iterator begin() {
			return { this, elements_ };
		}
		const_iterator begin() const {
			return { this, elements_ };
		}
		const_iterator cbegin() const {
			return begin();
		}

		// get the iterator pointing at pass-the-lass-element of the vector
		iterator end() {
			return { this, &elements_[size_] };
		}
		const_iterator end() const {
			return { this, &elements_[size_] };
		}
		const_iterator cend() const {
			return { this, &elements_[size_] };
		}

	private:
		size_type size_;
		size_type capacity_;
		value_type *elements_;
	};
}


#undef _VECTOR_UNINITIALIZED_ITERATOR_ASSERT_
#undef _VECTOR_OUT_OF_BOUND_ITERATOR_ASSERT_
#undef _VECTOR_MISMATCHED_ITERATOR_ASSERT_
#endif // !_EXPERIMENTAL_VECTOR_HPP_
