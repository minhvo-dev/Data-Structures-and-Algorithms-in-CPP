/*	
 *	File name:	"Driver.cpp"
 *	Date:		4/2/2020 5:19:18 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Main driver
 */

#include "./ut/inc/unit_test.hpp"
#include "./sorting_benchmark/inc/benchmark.hpp"

int main() {

    experimental_vector_unit_tests();
    experimental_sorting_algorithms_unit_tests();
    experimental_stack_unit_test();
    experimental_list_unit_tests();
    experimental_BST_unit_tests();
    experimental_AVL_unit_tests();

    benchmark_sorting_algorithms();

    return EXIT_SUCCESS;
}