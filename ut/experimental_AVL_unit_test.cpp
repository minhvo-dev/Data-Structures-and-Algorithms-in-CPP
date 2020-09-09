/*
 *	File name:	"experimental_AVL_unit_test.cpp"
 *	Date:		9/6/2020 10:14:59 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Unit tests for experimental AVL tree
 */

#include "./inc/unit_test.hpp"
#include "../inc/ds/experimental_avl_tree.hpp"

#include <string>
#include <sstream>

using namespace experimental;

bool experimental_AVL_empty_test() {
	AVLTree<int> t;
	return t.empty() && t.size() == 0 && t.height() == -1;
}

bool experimentaL_AVL_insert_test() {
	AVLTree<int> t;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		t.insert(i);
		if (t.size() != i + 1 || t.contains(i) == false) {
			return false;
		}
	}

	t.clear();
	for (int i = 0; i < SZ; ++i) {
		t.insert(-i);
		if (t.size() != i + 1 || t.contains(-i) == false) {
			return false;
		}
	}
	return t.height() == 9;
}

bool experimental_AVL_remove_test() {
	AVLTree<int> t;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		t.insert(i);
	}

	for (int i = 0; i < SZ; ++i) {
		t.remove(i);
		if (t.size() != SZ - i - 1 || t.contains(i)) {
			return false;
		}
	}

	t.remove(SZ); // does nothing

	return t.empty();
}

bool experimental_AVL_customer_comparator_test() {
	AVLTree<int, std::greater<int>> t;
	for (int i = 0; i < 10; ++i) {
		t.insert(i);
	}

	std::string res = "3 7 8 9 5 6 4 1 2 0 ";
	std::ostringstream oss;
	t.print_tree(oss);
	return oss.str() == res && t.height() == 3;
}

void experimental_AVL_unit_tests() {
	puts("----------------------------------------------------------");
	puts("Running AVL Unit Tests...\n");

	_RUN_UNIT_TEST_(experimental_AVL_empty_test);

	_RUN_UNIT_TEST_(experimentaL_AVL_insert_test);

	_RUN_UNIT_TEST_(experimental_AVL_remove_test);

	_RUN_UNIT_TEST_(experimental_AVL_customer_comparator_test);

	puts("\nFinished AVL Unit Tests...");
	puts("----------------------------------------------------------");
}