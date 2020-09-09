/*
 *	File name:	"experimental_BST_unit_test.cpp"
 *	Date:		9/6/2020 9:03:01 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Unit tests for experimental binary search tree
 */

#include "./inc/unit_test.hpp"
#include "../inc/ds/experimental_binary_search_tree.hpp"

#include <functional>
#include <string>
#include <sstream>

using namespace experimental;

bool experimental_BST_empty_test() {
	BinarySearchTree<int> bst;
	return bst.empty() && bst.size() == 0;
}

bool experimental_BST_insert_test() {
	BinarySearchTree<int> bst;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		bst.insert(i);
		if (bst.size() != i + 1) {
			return false;
		}
	}

	bst.clear();
	for (int i = 0; i < SZ; ++i) {
		bst.insert(-i);
		if (bst.size() != i + 1) {
			return false;
		}
	}

	return true;
}

bool experimental_BST_remove_test() {
	BinarySearchTree<int> bst;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		bst.insert(i);
	}
	for (int i = 0; i < SZ; ++i) {
		bst.remove(i);
		if (bst.size() != SZ - i - 1) {
			return false;
		}
	}

	bst.clear();
	for (int i = 0; i < SZ; ++i) {
		bst.insert(-i);
	}
	for (int i = 0; i < SZ; ++i) {
		bst.remove(-i);
		if (bst.size() != SZ - i - 1) {
			return false;
		}
	}

	return true;
}

bool experimental_BST_contain_test() {
	BinarySearchTree<int> bst;
	constexpr int SZ = 1000;
	for (int i = 0; i < SZ; ++i) {
		bst.insert(i);
	}
	if (bst.contains(-1)) {
		return false;
	}
	if (bst.contains(0) == false && bst.contains(SZ / 2) == false) {
		return false;
	}
	bst.remove(SZ / 2);
	return !bst.contains(SZ / 2);
}

bool experimental_BST_min_max_test() {
	BinarySearchTree<int> bst;
	constexpr int SZ = 1000;
	int sign = 1;
	for (int i = 0; i < SZ; ++i) {
		bst.insert(i * sign);
		sign *= -1;
	}
	return bst.find_min() == -999 && bst.find_max() == 998;
}

bool experimental_BST_custom_comparator_test() {
	BinarySearchTree<int, std::greater<int>> bst;
	int sign = 1;
	for (int i = 0; i < 10; ++i) {
		bst.insert(i * sign);
		sign *= -1;
	}
	std::string res = "0 2 4 6 8 -1 -3 -5 -7 -9 ";
	std::ostringstream oss;
	bst.print_tree(oss);
	return oss.str() == res;
}

void experimental_BST_unit_tests() {
	puts("----------------------------------------------------------");
	puts("Running BST Unit Tests...\n");

	_RUN_UNIT_TEST_(experimental_BST_empty_test);

	_RUN_UNIT_TEST_(experimental_BST_insert_test);

	_RUN_UNIT_TEST_(experimental_BST_remove_test);

	_RUN_UNIT_TEST_(experimental_BST_contain_test);

	_RUN_UNIT_TEST_(experimental_BST_min_max_test);

	_RUN_UNIT_TEST_(experimental_BST_custom_comparator_test);

	puts("\nFinished BST Unit Tests...");
	puts("----------------------------------------------------------");
}