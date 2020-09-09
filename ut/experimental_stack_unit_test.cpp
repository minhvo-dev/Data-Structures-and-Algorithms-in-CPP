/*	
 *	File name:	"experimental_stack_unit_test.cpp"
 *	Date:		9/5/2020 6:21:41 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Unit tests for experimental stack
 */

#include "./inc/unit_test.hpp"
#include "../inc/ds/experimental_stack.hpp"
#include "../inc/ds/experimental_vector.hpp"

using namespace experimental;

bool experimental_stack_empty_test() {
	Stack<int> si;
	return si.empty() && si.size() == 0;
}

bool experimental_stack_size_test() {
	Stack<int> si;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		si.push(i);
	}
	return si.size() == SZ;
}

bool experimental_stack_push_pop_test() {
	Stack<int> si;
	si.push(1);
	si.push(2);
	if (si.top() != 2) {
		return false;
	}
	si.pop();
	return si.top() == 1 && si.size() == 1;
}

bool experimental_stack_custom_container_test() {
	Stack<int, Vector<int>> si;
	for (int i = 0; i < 10; ++i) {
		si.push(i);
	}
	for (int i = 0; i < 5; ++i) {
		si.pop();
	}
	if (si.size() != 5 && si.top() != 4) {
		return false;
	}
	si.push(0);
	return si.size() == 6 && si.top() == 0;
}

void experimental_stack_unit_test() {
	puts("----------------------------------------------------------");
	puts("Running Stack Unit Tests...\n");

	_RUN_UNIT_TEST_(experimental_stack_empty_test);

	_RUN_UNIT_TEST_(experimental_stack_size_test);

	_RUN_UNIT_TEST_(experimental_stack_push_pop_test);

	_RUN_UNIT_TEST_(experimental_stack_custom_container_test);

	puts("\nFinished Stack Unit Tests...");
	puts("----------------------------------------------------------");
}