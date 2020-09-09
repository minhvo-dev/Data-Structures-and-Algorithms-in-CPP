/*
 *	File name:	"experimental_insertion_sort.hpp"
 *	Date:		6/28/2020 6:39:36 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of insertion sort algorithm
 */

#ifndef _EXPERIMENTAL_INSERTION_SORT_HPP_
#define _EXPERIMENTAL_INSERTION_SORT_HPP_

#include "../experimental_alias_declarations.hpp"

#include <functional>
#include <utility>

namespace experimental {

	namespace details {

		/*  Sort the subarray [first, last) of a container
		 *
		 *  first: the left-most iterator of the subarray (including)
		 *  last: the past-the-last iterator of the subarray (excluding)
		 *  cmp: the Comparator
		 */
		template<typename Iterator, typename Comparator>
		void insertion_sort_imp(Iterator first,
								Iterator last,
								Comparator cmp) {
			using value_type = typename Iterator::value_type;
			using size_type = alias::size_type;

			for (Iterator i = first; i != last; ++i) {
				value_type tmp = std::move(*i);
				Iterator j = i; // empty spot index
				for (; j != first && cmp(tmp, *(j - 1)); --j) {
					*j = std::move(*(j - 1));
				}
				*j = std::move(tmp); // move the value to the empty spot
			}
		}

		/*  Sort the subarray arr[left, right]
		 *
		 *  arr: array that need to be sorted
		 *  left: the left-most index of the subarray (including)
		 *  right: the right-most index of the subarray (including)
		 *  cmp: the Comparator
		 */
		template<typename T, typename Comparator>
		void insertion_sort_imp(T *arr,
								alias::size_type left,
								alias::size_type right,
								Comparator cmp) {
			for (alias::size_type i = left + 1; i <= right; ++i) {
				T tmp = std::move(arr[i]);
				alias::size_type j = i;
				for (; j > left && cmp(tmp, arr[j - 1]); --j) {
					arr[j] = std::move(arr[j - 1]);
				}
				arr[j] = std::move(tmp);
			}
		}

	}
	/*  Insertion sort: sort the container based on the first and last iterator,
	 *  default is in ascending order.
	 *
	 *  first: the left-most iterator of the subarray (including)
	 *  last: the past-the-last iterator of the subarray (excluding)
	 *  cmp: the comparator
	 *
	 *  Requirement: The Container must support random access.
	 */
	template<typename Iterator, typename Comparator = std::less<typename Iterator::value_type>>
	void insertion_sort(Iterator first, Iterator last, Comparator cmp = Comparator()) {
		if (first != last) {
			details::insertion_sort_imp(first, last, cmp);
		}
	}

	// insertion sort array's version
	template<typename T, alias::size_type SZ, typename Comparator = std::less<T>>
	void insertion_sort(T (&arr)[SZ], Comparator cmp = Comparator()) {
	    if constexpr (SZ > 0) {
	        details::insertion_sort_imp(arr, 
	                                    static_cast<alias::size_type>(0), 
	                                    static_cast<alias::size_type>(SZ - 1),
	                                    cmp);
	    }
	}

	// insertion sort pointer's version
	template<typename T, typename Comparator = std::less<T>>
	void insertion_sort(T *arr, alias::size_type sz, Comparator cmp = Comparator()) {
	    if (sz > 0) {
	        details::insertion_sort_imp(arr, 
	                                    static_cast<alias::size_type>(0), 
	                                    static_cast<alias::size_type>(sz - 1),
	                                    cmp);
	    }
	}
}

#endif // !_EXPERIMENTAL_INSERTION_SORT_HPP_
