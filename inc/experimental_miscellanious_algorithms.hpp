/*
 *	File name:	"experimental_miscellanious_algorithms.hpp"
 *	Date:		4/21/2020 8:52:08 PM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implementation of algorithms that are used in other algorithms
 */

#pragma once

#ifndef _EXPERIMENTAL_MISCELLANIOUS_ALGORITHMS_HPP_
#define _EXPERIMENTAL_MISCELLANIOUS_ALGORITHMS_HPP_

namespace experimental {
    
    // return the greater value of two values
    // requirement: value type must support operator<
    template<typename T>
    constexpr T const& max(T const &a, T const &b) {
        return a < b ? b : a;
    }

    // return the smaller value of two values
    // requirement: value type must support operator<
    template<typename T>
    constexpr T const& min(T const &a, T const &b) {
        return a < b ? a : b;
    }
}

#endif // !_EXPERIMENTAL_MISCELLANIOUS_ALGORITHMS_HPP_
