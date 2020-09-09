/*
 *	File name:	"experimental_binary_heap.hpp"
 *	Date:		4/28/2020 9:09:26 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of binary heap
 */

#pragma once

#ifndef _EXPERIMENTAL_BINARY_HEAP_HPP_
#define _EXPERIMENTAL_BINARY_HEAP_HPP_

#include "experimental_vector.hpp"

#include <functional>
#include <utility>

namespace experimental {
	/*  BinaryHeap class
		uses array to implement binary heap, which allows duplicates,
		index starts at 1
	*/
	template<typename T, typename Comparator = std::less<T>>
	class BinaryHeap {
	public:
		using value_type = T;
		using reference = value_type &;
		using const_reference = value_type const &;
		using size_type = typename Vector<T>::size_type;

		/* Custom constructors */
		// ======================================================================
		explicit BinaryHeap(size_type capacity = INITIAL_SIZE_)
			: heapArray_{}, size_{ 0 }, cmp_{} {
			heapArray_.reserve(capacity + 1);
		}

		explicit BinaryHeap(Vector<value_type> const &v)
			: heapArray_(v.size() + INITIAL_SIZE_), size_{ v.size() }, cmp_{} {
			// copy elements from vector to the heap
			for (size_type i = 0, sz = v.size(); i < sz; ++i) {
				heapArray_[i + 1] = v[i];
			}
			build_heap();
		}

		/* Element access */
		// ===============================================================================

		// get the first element of the heap
		const_reference front() const {
			return heapArray_[1];
		}

		/* Capacity operations */
		// ===============================================================================

		// query if the heap is empty
		bool empty() const {
			return size_ == 0;
		}

		// get the size of the heap
		size_type size() const {
			return size_;
		}

		/* Modifying operations */
		// ===============================================================================

		// insert an element into the heap
		// allow duplicates to be inserted
		void insert(const_reference x) {
			if (size_ == heapArray_.size() - 1) {
				// reach capacity
				// increase the capacity of the underlying array
				heapArray_.resize(heapArray_.size() * 2 + 1);
			}

			// percolate up
			// using the heapArray_[0] to hold a copy of x
			value_type cpy = x;
			heapArray_[0] = std::move(cpy);
			size_type cur = ++size_;
			for (size_type parent = static_cast<size_type>(cur / 2);
				 cmp_(x, heapArray_[parent]);
				 cur = parent, parent /= 2) {
				heapArray_[cur] = std::move(heapArray_[parent]);
			}
			heapArray_[cur] = std::move(heapArray_[0]);
		}

		void insert(value_type &&x) {
			if (size_ == heapArray_.size() - 1) {
				// reach capacity
				// increase the capacity of the underlying array
				heapArray_.resize(heapArray_.size() * 2 + 1);
			}

			// percolate up
			// pushing x to the back of the array
			using std::swap;
			size_type cur = ++size_;
			heapArray_[cur] = std::move(x);
			for (size_type parent = static_cast<size_type>(cur / 2);
				 parent > 0 && cmp_(heapArray_[cur], heapArray_[parent]);
				 cur = parent, parent /= 2) {
				swap(heapArray_[cur], heapArray_[parent]);
			}
		}

		// remove the element at index idx in the heap
		// do not check if the heap is empty or the index is out-of-bound
		void erase(size_type idx) {
			heapArray_[idx + 1] = std::move(heapArray_[size_--]); // move the last element to the removing element 
			// re-heap the heap where the remove happened
			percolate_down(idx + 1);
		}

		// remove the elements whose value is 'val'
		// do nothing if value 'val' does not exist in the heap
		void remove(const_reference val) {
			remove(val, 1, size_ + 1);
		}

		// remove all the elements in the heap
		void clear() {
			heapArray_.clear();
		}

	private:
		Vector<value_type> heapArray_; // containts elements
		size_type size_;
		Comparator cmp_;

		// establish heap order property from the random ordered
		// elements in the internal vector
		void build_heap() {
			// percolate down every element who has children
			for (size_type i = static_cast<size_type>(size_ / 2); i > 0; --i) {
				percolate_down(i);
			}
		}

		// percolate down the element at index 'idx' in the heap
		// by moving down it along the path in which contains smaller elements
		// choose the smaller between 2 children to maintain the properties of heap
		// 'idx' is the index where the percolate begins
		void percolate_down(size_type idx) {
			auto child = idx * 2; // left child
			value_type tmp = std::move(heapArray_[idx]);
			for (; idx * 2 <= size_; idx = child) {
				child = idx * 2;
				// get the 'smaller' between left and right children
				if (child != size_ && cmp_(heapArray_[child + 1], heapArray_[child])) {
					++child;
				}
				if (cmp_(heapArray_[child], tmp)) {
					heapArray_[idx] = std::move(heapArray_[child]);
				}
				else {
					break;
				}
			}
			heapArray_[idx] = std::move(tmp);
		};

		// remove the 'val' in the heap in range [beg, end)
		void remove(const_reference val, size_type beg, size_type end) {
			while (beg < end) {
				if (cmp_(heapArray_[beg], val)) {
					++beg;
				}
				else if (cmp_(val, heapArray_[beg])) {
					// found a 'graater' element in the heap
					// increase the index 
					// and update the end to the left child of current element
					++beg;
					end = min(end, 2 * beg);
				}
				else {
					// found the 'val' in the heap
					// move the last element to the removing element
					heapArray_[beg] = std::move(heapArray_[size_--]);
					// re-heap
					percolate_down(beg);
					// update the end
					end = min(end, size_ + 1);
					// continue removing since there might be duplicates of 'val' in the heap
					// range at new begin and end
				}
			}
		}

		static const size_type INITIAL_SIZE_;
	};

	template<typename T, typename Comparator>
	typename BinaryHeap<T, Comparator>::size_type const BinaryHeap<T, Comparator>::INITIAL_SIZE_ = 100;

}

#endif // !_EXPERIMENTAL_BINARY_HEAP_HPP_

