/*
 *	File name:	"experimental_stack.hpp"
 *	Date:		4/16/2020 6:43:08 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of stack ADT
 */

#pragma once

#ifndef _EXPERIMENTAL_STACK_HPP_
#define _EXPERIMENTAL_STACK_HPP_

#include "experimental_list.hpp"

#include <utility>
#include <cassert>

namespace experimental {
	/*  Stack ADT class
		provide a generic container that support LIFO data structure
	*/
	template<typename T, typename Container = List<T>>
	class Stack {
	public:
		using container_type = Container;
		using value_type = typename Container::value_type;
		using reference = typename Container::reference;
		using const_reference = typename Container::const_reference;
		using size_type = typename Container::size_type;

		Stack() : container_{} {}

		/* Element access */
		// ===============================================================================

		// access the top element of the stack
		// do not check if the stack is empty
		reference top() {
			assert(!container_.empty() && "cannot get top element from an empty stack");

			return container_.back();
		}
		const_reference top() const {
			assert(!container_.empty() && "cannot get top element from an empty stack");

			return container_.back();
		}

		/* Capacity operations */
		// ===============================================================================

		// check if the stack is empty
		bool empty() const {
			return container_.empty();
		}

		// query the size of the stack
		size_type size() const {
			return container_.size();
		}

		/* Modifying operations */
		// ===============================================================================

		// insert element at the top of the stack
		void push(value_type const &value) {
			container_.push_back(value);
		}
		void push(value_type &&value) {
			container_.push_back(std::move(value));
		}

		// remove element at the top of the stack
		// do not check if the stack is empty
		void pop() {
			assert(!container_.empty() && "cannot pop from an empty stack");

			container_.pop_back();
		}

	private:
		Container container_;
	};
}

#endif // !_EXPERIMENTAL_STACK_HPP_



