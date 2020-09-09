/*	
 *	File name:	"experimental_sorting_algorithms_unit_test.cpp"
 *	Date:		9/5/2020 9:53:53 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Unit tests for sorting algorithms
 */

#include "./inc/unit_test.hpp"
#include "../inc/ds/experimental_vector.hpp"
#include "../inc/sorts/experimental_insertion_sort.hpp"
#include "../inc/sorts/experimental_heap_sort.hpp"
#include "../inc/sorts/experimental_shell_sort.hpp"
#include "../inc/sorts/experimental_merge_sort.hpp"
#include "../inc/sorts/experimental_quick_sort.hpp"

#include <functional>
#include <algorithm>
#include <ctime>

using namespace experimental;

void generate_random_numbers(int *arr, unsigned int sz) {
	std::srand(std::time(nullptr));
	for (unsigned int i = 0; i < sz; ++i) {
		arr[i] = std::rand();
	}
}

bool experimental_insertion_sort_array_test() {
	constexpr int SZ = 10;
	int vi[SZ];
	for (int i = 0; i < SZ; ++i) {
		vi[i] = -i;
	}
	insertion_sort(vi);
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] < vi[i - 1]) {
			return false;
		}
	}

	insertion_sort(vi, std::greater<int>());
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] > vi[i - 1]) {
			return false;
		}
	}

	for (int i = 0; i < SZ; ++i) {
		vi[i] = SZ;
	}
	insertion_sort(vi);
	insertion_sort(vi, std::greater<int>());

	for (int i = 0; i < SZ; ++i) {
		if (vi[i] != SZ) {
			return false;
		}
	}

	generate_random_numbers(vi, SZ);
	int cpy[SZ];
	for (unsigned int i = 0; i < SZ; ++i) {
		cpy[i] = vi[i];
	}

	insertion_sort(vi);
	std::sort(cpy, cpy + SZ);

	for (unsigned int i = 0; i < SZ; ++i) {
		if (vi[i] != cpy[i]) {
			return false;
		}
	}

	return true;
}

bool experimental_heap_sort_array_test() {
	constexpr int SZ = 1000;
	int vi[SZ];
	for (int i = 0; i < SZ; ++i) {
		vi[i] = -i;
	}
	heap_sort(vi);
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] < vi[i - 1]) {
			return false;
		}
	}

	heap_sort(vi, std::greater<int>());
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] > vi[i - 1]) {
			return false;
		}
	}

	for (int i = 0; i < SZ; ++i) {
		vi[i] = SZ;
	}
	heap_sort(vi);
	heap_sort(vi, std::greater<int>());

	for (int i = 0; i < SZ; ++i) {
		if (vi[i] != SZ) {
			return false;
		}
	}

	generate_random_numbers(vi, SZ);
	int cpy[SZ];
	for (unsigned int i = 0; i < SZ; ++i) {
		cpy[i] = vi[i];
	}

	heap_sort(vi);
	std::sort(cpy, cpy + SZ);

	for (unsigned int i = 0; i < SZ; ++i) {
		if (vi[i] != cpy[i]) {
			return false;
		}
	}

	return true;
}

bool experimental_shell_sort_array_test() {
	constexpr int SZ = 1000;
	int vi[SZ];
	for (int i = 0; i < SZ; ++i) {
		vi[i] = -i;
	}
	shell_sort(vi);
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] < vi[i - 1]) {
			return false;
		}
	}

	shell_sort(vi, std::greater<int>());
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] > vi[i - 1]) {
			return false;
		}
	}

	for (int i = 0; i < SZ; ++i) {
		vi[i] = SZ;
	}
	shell_sort(vi);
	shell_sort(vi, std::greater<int>());

	for (int i = 0; i < SZ; ++i) {
		if (vi[i] != SZ) {
			return false;
		}
	}

	generate_random_numbers(vi, SZ);
	int cpy[SZ];
	for (unsigned int i = 0; i < SZ; ++i) {
		cpy[i] = vi[i];
	}

	shell_sort(vi);
	std::sort(cpy, cpy + SZ);

	for (unsigned int i = 0; i < SZ; ++i) {
		if (vi[i] != cpy[i]) {
			return false;
		}
	}

	return true;
}

bool experimental_merge_sort_array_test() {
	constexpr int SZ = 1000;
	int vi[SZ];
	for (int i = 0; i < SZ; ++i) {
		vi[i] = -i;
	}
	merge_sort(vi);
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] < vi[i - 1]) {
			return false;
		}
	}

	merge_sort(vi, std::greater<int>());
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] > vi[i - 1]) {
			return false;
		}
	}

	for (int i = 0; i < SZ; ++i) {
		vi[i] = SZ;
	}
	merge_sort(vi);
	merge_sort(vi, std::greater<int>());

	for (int i = 0; i < SZ; ++i) {
		if (vi[i] != SZ) {
			return false;
		}
	}

	generate_random_numbers(vi, SZ);
	int cpy[SZ];
	for (unsigned int i = 0; i < SZ; ++i) {
		cpy[i] = vi[i];
	}

	merge_sort(vi);
	std::sort(cpy, cpy + SZ);

	for (unsigned int i = 0; i < SZ; ++i) {
		if (vi[i] != cpy[i]) {
			return false;
		}
	}

	return true;
}


bool experimental_quick_sort_array_test() {
	constexpr int SZ = 10;
	int vi[SZ];
	for (int i = 0; i < SZ; ++i) {
		vi[i] = -i;
	}
	quick_sort(vi);
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] < vi[i - 1]) {
			return false;
		}
	}

	quick_sort(vi, std::greater<int>());
	for (int i = 1; i < SZ; ++i) {
		if (vi[i] > vi[i - 1]) {
			return false;
		}
	}

	for (int i = 0; i < SZ; ++i) {
		vi[i] = SZ;
	}
	quick_sort(vi);
	quick_sort(vi, std::greater<int>());

	for (int i = 0; i < SZ; ++i) {
		if (vi[i] != SZ) {
			return false;
		}
	}

	generate_random_numbers(vi, SZ);
	int cpy[SZ];
	for (unsigned int i = 0; i < SZ; ++i) {
		cpy[i] = vi[i];
	}

	quick_sort(vi);
	std::sort(cpy, cpy + SZ);

	for (unsigned int i = 0; i < SZ; ++i) {
		if (vi[i] != cpy[i]) {
			return false;
		}
	}

	return true;
}


void experimental_sorting_algorithms_unit_tests() {
	puts("----------------------------------------------------------");
	puts("Running Sorting Algorithm Unit Tests...\n");

	_RUN_UNIT_TEST_(experimental_insertion_sort_array_test);

	_RUN_UNIT_TEST_(experimental_heap_sort_array_test);

	_RUN_UNIT_TEST_(experimental_shell_sort_array_test);

	_RUN_UNIT_TEST_(experimental_merge_sort_array_test);

	_RUN_UNIT_TEST_(experimental_quick_sort_array_test);

	puts("\nFinished Sorting Algorithm Unit Tests...");
	puts("----------------------------------------------------------");
}