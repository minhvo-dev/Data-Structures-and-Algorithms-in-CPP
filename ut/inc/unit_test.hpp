/*
 *	File name:	"unit_test.hpp"
 *	Date:		9/5/2020 8:52:47 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Declaration of unit tests
 */

#pragma once

#ifndef _UNIT_TEST_HPP_
#define _UNIT_TEST_HPP_

#include <iostream>
#include <string>

using namespace std::string_literals;

#define _RUN_UNIT_TEST_(X) (std::cout << ((X() ? (#X + " passed"s) : (#X + " failed"s))) + '\n');

void experimental_vector_unit_tests();
void experimental_sorting_algorithms_unit_tests();
void experimental_stack_unit_test();
void experimental_list_unit_tests();
void experimental_BST_unit_tests();
void experimental_AVL_unit_tests();

#endif // !_UNIT_TEST_HPP_
