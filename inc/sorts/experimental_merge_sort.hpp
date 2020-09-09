/*
 *	File name:	"experimental_merge_sort.hpp"
 *	Date:		6/28/2020 8:47:07 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of merge sort algorithm
 *				Container is not supported yet.
 */

#pragma once

#ifndef _EXPERIMENTAL_MERGE_SORT_HPP_
#define _EXPERIMENTAL_MERGE_SORT_HPP_

#include "../experimental_alias_declarations.hpp"

#include <utility>
#include <functional>

namespace experimental {

	namespace details {

		/*  Merge two sorted halves of a subarray.
		 *
		 *  arr: array that needs to be sorted
		 *  merArr: temporary array to hold the merged result
		 *  left: the left-most index of the first half subarray
		 *  right: the left-most index of the second half subarray
		 *  end: the right-most index of the second half subarray
		 *  cmp: the Comparator
		 */
		template<typename T, typename Comparator>
		void merge(T *arr,
				   T *merArr,
				   alias::size_type left,
				   alias::size_type right,
				   alias::size_type end,
				   Comparator cmp) {
			using size_type = alias::size_type;
			size_type leftEnd = right - 1, merIdx = left;
			size_type const SZ = end - left + 1;

			// copy element from two halves to the merged array based on cmp
			while (left <= leftEnd && right <= end) {
				if (cmp(arr[left], arr[right])) {
					merArr[merIdx++] = std::move(arr[left++]);
				}
				else {
					merArr[merIdx++] = std::move(arr[right++]);
				}
			}
			// copy the rest of first half to the merged array
			while (left <= leftEnd) {
				merArr[merIdx++] = std::move(arr[left++]);
			}
			// copy the rest of second half to the merged array
			while (right <= end) {
				merArr[merIdx++] = std::move(arr[right++]);
			}
			// copy the merged array back to the original array
			for (size_type i = 0; i < SZ; ++i, --end) {
				arr[end] = std::move(merArr[end]);
			}
		}

		/*  Recursive calls in merge sort.
		 *
		 *  arr: array that need to be sorted
		 *  merArr: temporary array to hold the merged result
		 *  left: the left-most index of the subarray (including)
		 *  right: the right-most index of the subarray (including)
		 *  cmp: the Comparator
		 */
		template<typename T, typename Comparator>
		void merge_sort(T *arr,
						T *merArr,
						alias::size_type left,
						alias::size_type right,
						Comparator cmp) {
			if (left < right) {
				alias::size_type center = left + (right - left) / 2;
				merge_sort(arr, merArr, left, center, cmp);
				merge_sort(arr, merArr, center + 1, right, cmp);
				experimental::details::merge(arr, merArr, left, center + 1, right, cmp);
			}
		}
	}

	template<typename T, typename Comparator = std::less<T>>
	void merge_sort(T *arr, alias::size_type sz, Comparator cmp = Comparator()) {
		T *tmpArray = new T[sz];
		details::merge_sort(arr, tmpArray, 0, sz - 1, cmp);
		delete[] tmpArray;
	}

	template<typename T, alias::size_type SZ, typename Comparator = std::less<T>>
	void merge_sort(T (&arr)[SZ], Comparator cmp = Comparator()) {
		merge_sort(arr, SZ, cmp);
	}
}

#endif // !_EXPERIMENTAL_MERGE_SORT_HPP_
