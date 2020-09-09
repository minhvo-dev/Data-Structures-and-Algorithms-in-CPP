/*	
 *	File name:	"experimental_list_unit_test.cpp"
 *	Date:		9/5/2020 7:01:13 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Unit tests for experimental list
 */

#include "./inc/unit_test.hpp"
#include "../inc/ds/experimental_list.hpp"

using namespace experimental;

bool experimental_list_copy_constructor_test() {
	List<int> li{ 1, 2};
	List<int> cpy = li;
	return cpy.size() == 2 && cpy.front() == 1 && cpy.back() == 2;
}

bool experimental_list_empty_test() {
	List<int> li;
	return li.empty() && li.size() == 0;
}

bool experimental_list_front_back_test() {
	List<int> li{ 1,2,3 };
	li.front() = 0;
	li.back() = 100;
	return li.size() == 3 && li.front() == 0 && li.back() == 100;
}

bool experimental_list_push_front_test() {
	List<int> li;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		li.push_front(i);
	}
	return li.size() == SZ && li.front() == (SZ - 1) && li.back() == 0;
}

bool experimental_list_push_back_test() {
	List<int> li;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		li.push_back(i);
	}
	return li.size() == SZ && li.back() == (SZ - 1) && li.front() == 0;
}

bool experimental_list_pop_front_test() {
	List<int> li;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		li.push_back(i);
	}
	for (int i = 0; i < SZ; ++i) {
		if (li.front() != i) {
			return false;
		}
		li.pop_front();
	}
	return li.empty();
}

bool experimental_list_pop_back_test() {
	List<int> li;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		li.push_front(i);
	}
	for (int i = 0; i < SZ; ++i) {
		if (li.back() != i) {
			return false;
		}
		li.pop_back();
	}
	return li.empty();
}

bool experimental_list_insert_test() {
	List<int> li;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		li.insert(li.end(), i);
	}
	auto it = li.cbegin();
	if (li.size() != SZ) {
		return false;
	}
	for (int i = 0; i < SZ; ++i, ++it) {
		if (*it != i) {
			return false;
		}
	}
	return true;
}

bool experimental_list_erase_test() {
	List<int> li;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		li.push_back(i);
	}
	auto it = li.cbegin();
	if (li.size() != SZ) {
		return false;
	}
	for (int i = 0; i < SZ; ++i) {
		if (li.front() != i) {
			return false;
		}
		li.erase(li.begin());
	}
	if (!li.empty()) {
		return false;
	}
	for (int i = 0; i < SZ; ++i) {
		li.push_back(i);
	}
	li.erase(li.begin(), li.end());
	return li.empty();
}

void experimental_list_unit_tests() {
	puts("----------------------------------------------------------");
	puts("Running Vector Unit Tests...\n");

	_RUN_UNIT_TEST_(experimental_list_copy_constructor_test);

	_RUN_UNIT_TEST_(experimental_list_empty_test);

	_RUN_UNIT_TEST_(experimental_list_front_back_test);

	_RUN_UNIT_TEST_(experimental_list_push_front_test);

	_RUN_UNIT_TEST_(experimental_list_push_back_test);

	_RUN_UNIT_TEST_(experimental_list_pop_front_test);

	_RUN_UNIT_TEST_(experimental_list_pop_back_test);

	_RUN_UNIT_TEST_(experimental_list_insert_test);

	_RUN_UNIT_TEST_(experimental_list_erase_test);

	puts("\nFinished Vector Unit Tests...");
	puts("----------------------------------------------------------");
}