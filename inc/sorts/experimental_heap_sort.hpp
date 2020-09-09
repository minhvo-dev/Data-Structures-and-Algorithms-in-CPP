/*
 *	File name:	"experimental_heap_sort.hpp"
 *	Date:		6/28/2020 9:57:09 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of heap sort algorithm
 *				Container is not supported yet.
 */

#pragma once

#ifndef _EXPERIMENTAL_HEAP_SORT_HPP_
#define _EXPERIMENTAL_HEAP_SORT_HPP_

#include "../experimental_alias_declarations.hpp"

#include <functional>
#include <utility>

namespace experimental {

	namespace details {

		/* Calculate the index of the left child of an element in the heap */
		inline alias::size_type get_left_child_index(alias::size_type parent) {
			return 2 * parent + 1;
		}

		/*  Percolate down an element depended on Comparator
		 *  to maintain the heap properties.
		 *
		 *  arr: the array
		 *  pos: the position from which to percolate down
		 *  sz: the logical size of the heap (not the size of the cnt)
		 *  cmp: the comparator (same as the heap sort's)
		 */
		template<typename T, typename Comparator>
		void percolate_down(T *arr, alias::size_type pos, alias::size_type sz, Comparator cmp) {
			using size_type = alias::size_type;

			size_type childIdx;
			T tmp;
			for (tmp = std::move(arr[pos]), childIdx = get_left_child_index(pos);
				 childIdx < sz;
				 pos = childIdx, childIdx = get_left_child_index(pos)) {
				if (childIdx != sz - 1 && cmp(arr[childIdx], arr[childIdx + 1])) { // get the greater child if sorting in ascending order
					++childIdx;
				}
				if (cmp(tmp, arr[childIdx])) { // percolate down
					arr[pos] = std::move(arr[childIdx]);
				}
				else {
					break;
				}
			}
			arr[pos] = std::move(tmp);
		}

		template<typename T, typename Comparator>
		void heap_sort_imp(T *arr, alias::size_type sz, Comparator cmp) {
			using size_type = alias::size_type;

			if (sz > 0) {
				// build heap
				// note: this process is similar to the process in experimental_binary_heap.hpp
				// but in this implementation, index starts at 0, not at 1
				for (size_type i = sz / 2; i > 0; --i) {
					percolate_down(arr, i - 1, sz, cmp);
				}

				// perform removing the first element of the heap N times
				using std::swap;
				for (size_type i = sz - 1; i > 0; --i) {
					swap(arr[0], arr[i]); // move to the back
					percolate_down(arr, 0, i, cmp); // maintain the heap properties
				}
			}
		}

	}

	/*	Heap sort: sort the container based on the Comparator
	// *
	// *	cnt: the container that needs to be sorted
	// *	cmp: the Comparator
	// *
	// *	Requirement: the Container must support random access
	// */
	//template<typename Container, typename Comparator = std::less<typename Container::value_type>>
	//void heap_sort(Container &cnt, Comparator cmp = Comparator()) {
	//	using T = typename Container::value_type;
	//	using size_type = typename Container::size_type;
	//	if (cnt.size() > 0) {
	//		// build heap
	//		// note: this process is similar to the process in experimental_binary_heap.hpp
	//		// but in this implementation, index starts at 0, not at 1
	//		for (size_type i = cnt.size() / 2; i > 0; --i) {
	//			details::percolate_down(cnt, i - 1, cnt.size(), cmp);
	//		}

	//		// perform removing the first element of the heap N times
	//		for (size_type i = cnt.size() - 1; i > 0; --i) {
	//			using std::swap;
	//			swap(cnt[0], cnt[i]); // move to the back
	//			details::percolate_down(cnt, 0, i, cmp); // maintain the heap properties
	//		}
	//	}
	//}

	/*	Heap sort: sort the array based on the Comparator
	 *
	 *	arr: the array that needs to be sorted
	 *	cmp: the Comparator
	 */
	template<typename T, alias::size_type SZ, typename Comparator = std::less<T>>
	void heap_sort(T (&arr)[SZ], Comparator cmp = Comparator()) {
		details::heap_sort_imp(arr, SZ, cmp);
	}

	// Heap sort pointer's version
	template<typename T, typename Comparator = std::less<T>>
	void heap_sort(T *arr, alias::size_type sz, Comparator cmp = Comparator()) {
		details::heap_sort_imp(arr, sz, cmp);
	}

}

#endif // !_EXPERIMENTAL_HEAP_SORT_HPP_
