/*
 *	File name:	"experimental_vector_unit_test.cpp"
 *	Date:		9/4/2020 9:36:26 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Unit tests for experimental vector
 */

#include "./inc/unit_test.hpp"
#include "../inc/ds/experimental_vector.hpp"

using namespace experimental;

bool experimental_vector_copy_constructor() {
	Vector<int> v1{ 1,2,3 };
	Vector<int> v2 = v1;
	return v2.size() == 3 && v2[0] == 1 && v2[1] == 2 && v2[2] == 3;
}

bool experimental_vector_empty_test() {
	Vector<int> v;
	return v.size() == 0 && v.empty();
}

bool experimental_vector_size_test() {
	Vector<int> v{ 1,2,3,4 };
	return v.size() == 4;
}

bool experimental_vector_element_access_test() {
	Vector<int> v{ 1,2,3 };
	return v[1] == 2 && v.front() == 1 && v.back() == 3;
}

bool experimental_vector_add_element_test() {
	Vector<int> v;
	for (int i = 0; i < 1000; ++i) {
		v.push_back(i);
	}
	for (int i = 0; i < 1000; ++i) {
		if (v[i] != i) {
			return false;
		}
	}
	return true;
}

bool experimental_vector_remove_element_test() {
	Vector<int> vi;
	constexpr int sz = 1000, rm = 500;
	for (int i = 0; i < sz; ++i) {
		vi.push_back(i);
	}
	for (int i = 0; i < rm; ++i) {
		vi.pop_back();
	}

	if (vi.size() != sz - rm) {
		return false;
	}
	for (int i = 0; i < sz - rm; ++i) {
		if (vi[i] != i) {
			return false;
		}
	}
	vi.clear();
	return vi.size() == 0;
}

bool experimental_vector_begin_iterator_test() {
	Vector<int> vi{ 1,2,3,4,5 };
	return *(vi.begin()) == 1 && *(vi.cbegin()) == 1;
}

bool experimental_vector_assign_iterator_test() {
	Vector<int> vi{ 1,2,3,4,5 };
	Vector<int>::iterator it = vi.begin();
	*it = 0;
	it += 4;
	*it = 100;
	return *(vi.begin()) == 0 && *(vi.begin() + 4) == 100;
}

bool experimental_vector_increment_iterator_test_1() {
	Vector<int> vi{ 1,2,3,4,5 };
	int start = 1;
	for (Vector<int>::iterator it = vi.begin(), end = vi.end(); it != end; ++it) {
		if (*it != start++) {
			return false;
		}
	}
	return true;
}

bool experiemental_vector_increment_iterator_test_2() {
	Vector<int> vi{ 0,1,2,3,4,5,6,7,8,9 };
	using Iter = Vector<int>::iterator;
	Iter beg = vi.begin();
	Iter i5 = beg + 5;
	Iter i2 = i5 - 3;
	Iter i7 = i2 + 5;
	return *i5 == 5 && *i2 == 2 && *i7 == 7;
}

bool experimental_vector_boolean_iterator_test() {
	Vector<int> vi{ 1,2,3,4,5 };
	Vector<int>::iterator it0 = vi.begin();
	Vector<int>::iterator it3 = it0 + 3;
	return it3 > it0 && it0 < it3 && (it3 - 3) == it0;
}

void experimental_vector_unit_tests() {
	puts("----------------------------------------------------------");
	puts("Running Vector Unit Tests...\n");

	_RUN_UNIT_TEST_(experimental_vector_copy_constructor);

	_RUN_UNIT_TEST_(experimental_vector_empty_test);

	_RUN_UNIT_TEST_(experimental_vector_size_test);

	_RUN_UNIT_TEST_(experimental_vector_element_access_test);

	_RUN_UNIT_TEST_(experimental_vector_add_element_test);

	_RUN_UNIT_TEST_(experimental_vector_remove_element_test);

	_RUN_UNIT_TEST_(experimental_vector_begin_iterator_test);

	_RUN_UNIT_TEST_(experimental_vector_assign_iterator_test);

	_RUN_UNIT_TEST_(experimental_vector_increment_iterator_test_1);

	_RUN_UNIT_TEST_(experiemental_vector_increment_iterator_test_2);

	_RUN_UNIT_TEST_(experimental_vector_boolean_iterator_test);

	puts("\nFinished Vector Unit Tests...");
	puts("----------------------------------------------------------");
}