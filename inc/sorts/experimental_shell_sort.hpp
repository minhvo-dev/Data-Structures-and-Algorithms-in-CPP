/*
 *	File name:	"experimental_shell_sort.hpp"
 *	Date:		6/28/2020 7:36:04 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of shell sort with Sedgewick increment sequence
 *				Container is not supported yet.
 */

#pragma once

#ifndef _EXPERIMENTAL_SHELL_SORT_HPP_
#define _EXPERIMENTAL_SHELL_SORT_HPP_

#include "../ds/experimental_vector.hpp"
#include "../experimental_alias_declarations.hpp"

#include <utility>

namespace experimental {

	namespace details {

		/*	Sedgewick increment sequence
		 *	The terms of sequence are either of the form (9*4^i - 9*2^i + 1) or (4^i - 3*2*i + 1)
		 */
		constexpr unsigned int SEQUENCE_SIZE = 30;
		constexpr alias::size_type SEQUENCE[SEQUENCE_SIZE] = { 
			1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 
			8929, 16001, 36289, 64769, 146305, 260609, 587521, 1045505, 2354689, 4188161, 
			9427969, 16764929, 37730305, 67084289, 150958081, 268386305, 603906049, 1073643521, 2415771649, 4294770689 };
		
		/*	Shell sort: sort the array based on the Comparator
		 *
		 *	arr: the array that needs to be sorted
		 *	sz: size of the array
		 *	cmp: the comparator
		 */
		template<typename T, typename Comparator>
		void shell_sort_imp(T *arr, alias::size_type sz, Comparator cmp) {
			// find the start index
			unsigned int iSeq = 0;
			for (alias::size_type halfSz = sz / 2; iSeq < SEQUENCE_SIZE && SEQUENCE[iSeq] < halfSz; ++iSeq) {}
			
			for (; iSeq > 0; --iSeq) {
				auto gap = SEQUENCE[iSeq - 1]; // gap between items in the subarray
				for (auto i = gap; i < sz; ++i) {
					// insertion sort on subarray
					T tmp = std::move(arr[i]);
					auto j = i;
					for (; j >= gap && cmp(tmp, arr[j - gap]); j -= gap) {
						arr[j] = std::move(arr[j - gap]);
					}
					arr[j] = std::move(tmp);
				}
			}
		}
	}

	/*	Shell sort: sort the array based on the Comparator
	 *	using the Sedgewick increment sequence
	 *
	 *	arr: the array that needs to be sorted
	 *	cmp: the Comparator
	 */
	template<typename T, alias::size_type SZ, typename Comparator = std::less<T>>
	inline void shell_sort(T (&arr)[SZ], Comparator cmp = Comparator()) {
		details::shell_sort_imp(arr, SZ, cmp);
	}

	/*	Shell sort: sort the array based on the Comparator
	 *	using the Sedgewick increment sequence
	 *
	 *	arr: the array that needs to be sorted
	 *	sz: size of the array
	 *	cmp: the Comparator
	 */
	template<typename T, typename Comparator = std::less<T>>
	inline void shell_sort(T *arr, alias::size_type sz, Comparator cmp = Compartor()) {
		details::shell_sort_imp(arr, sz, cmp);
	}
}

#endif // !_EXPERIMENTAL_SHELL_SORT_HPP_
