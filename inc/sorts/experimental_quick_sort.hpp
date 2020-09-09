/*
 *	File name:	"experimental_quick_sort.hpp"
 *	Date:		9/3/2020 7:38:32 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of quick sort algorithm
 *				which utilizes insertion sort to sort small arrays
 *				Container is not supported yet.
 */

#pragma once

#ifndef _EXPERIMENTAL_QUICK_SORT_HPP_
#define _EXPERIMENTAL_QUICK_SORT_HPP_

#include "experimental_insertion_sort.hpp"
#include "../experimental_alias_declarations.hpp"

#include <utility>
#include <functional>

namespace experimental {

	namespace details {

		static alias::size_type constexpr THRESHOLD = 10; // to determine whether an array is 'small'

		/*	Internal quicksort's operation
		 *		for the subarray of cnt[left, right], find the median of three elements:
		 *			cnt[left], cnt[right] and cnt[(left + right)/2]
		 *		and move the smallest of three to the cnt[left], the largest to the cnt[right]
		 *		and the median to cnt[right - 1]
		 *
		 *	arr: the array
		 *	left: the left-most index of the subarray
		 *	right: the right-most index of the subarray
		 *	cmp: comparator
		 *
		 *	Requirement: the Container must support random access
		 */
		template<typename T, typename Comparator>
		T const& median3(T *arr,
						 alias::size_type left,
						 alias::size_type right,
						 Comparator cmp) {
			alias::size_type center = left + (right - left) / 2;
			using std::swap;
			// move 'smallest' to the left, 'largest' to the right
			if (cmp(arr[center], arr[left])) {
				swap(arr[left], arr[center]);
			}
			if (cmp(arr[right], arr[left])) {
				swap(arr[left], arr[right]);
			}
			if (cmp(arr[right], arr[center])) {
				swap(arr[center], arr[right]);
			}
			// place pivot at position r(right - 1)
			swap(arr[center], arr[right - 1]);
			return arr[right - 1];
		}

		/*	Recursive calls in quick sort
		 *
		 *	array: the array that needs to be sorted
		 *	left: the left-most index of the subarray
		 *	right: the right-most index of the subarray
		 *	cmp: comparator
		 *	threshold: to determine whether an array is small
		 *
		 *	Requirement: the Container must support random access
		 */
		template<typename T, typename Comparator>
		void quick_sort(T *arr,
						alias::size_type left,
						alias::size_type right,
						Comparator cmp,
						alias::size_type threshold = THRESHOLD) {
			using std::swap;
			if (left + threshold < right) {
				// pre-partioning: determining pivot
				T const &pivot = median3(arr, left, right, cmp);
				// partitioning
				alias::size_type i = left, j = right - 1;
				while (true) {
					while (cmp(arr[++i], pivot)) {}
					while (cmp(pivot, arr[--j])) {}
					if (i < j) {
						swap(arr[i], arr[j]);
					}
					else {
						break;
					}
				}
				swap(arr[i], arr[right - 1]); // restore pivot's position
				// recursion
				quick_sort(arr, left, i - 1, cmp); // left part
				quick_sort(arr, i + 1, right, cmp); // right part
			}
			else {
				// sorting small array using insertion sort
				insertion_sort_imp(arr, left, right, cmp);
			}
		}

	}


	/*	Quick sort: sort the array based on Comparator
	 *
	 *	arr: the array that needs to be sorted
	 *	sz: size of the array
	 *	cmp: the comparator
	 *
	 *	Requirement: the Container must support random access
	 */
	template<typename T, typename Comparator = std::less<T>>
	void quick_sort(T *arr, alias::size_type sz, Comparator cmp = Comparator()) {
		if (sz > 0) {
			details::quick_sort(arr, 0, sz - 1, cmp);
		}
	}

	// Quick sort array's version
	template<typename T, alias::size_type SZ, typename Comparator = std::less<T>>
	void quick_sort(T (&arr)[SZ], Comparator cmp = Comparator()) {
		details::quick_sort(arr, 0, SZ - 1, cmp);
	}
}

#endif // !_EXPERIMENTAL_QUICK_SORT_HPP_
