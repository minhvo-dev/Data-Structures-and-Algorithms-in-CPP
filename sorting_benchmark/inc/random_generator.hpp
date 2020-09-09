/*
 *	File name:	"random_generator.hpp"
 *	Date:		9/7/2020 9:35:03 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Custom random number generators.
 *				Prepare the samples for benchmarking sorting algorithms
 */

#pragma once

#ifndef _RANDOM_GENERATOR_HPP_
#define _RANDOM_GENERATOR_HPP_

extern unsigned int const SAMPLE_SIZES[6];
extern unsigned int const NUMBER_OF_SAMPLES;

/*	Generate a random number in range [low, high]
 *	based on uniform distribution
 *
 *	low: low bound (including)
 *	high: high bound (including)
 */
unsigned int generate_random_number_in_range(unsigned int low, unsigned int high);

/*	Generate random integer numbers in range [low, high]
 *	based on uniform distribution
 *
 *	sz: total random numbers
 *	maxKey: right bound of the range
 *	Return: pointer to array
 *
 *	Note: caller should free the array.
 */
int* generate_random_numbers_in_range(unsigned int sz, unsigned int low, unsigned int high);

/*	Generate random integer numbers based on normal distribution
 *
 *	sz: total random numbers
 *	mean: mean of the distribution
 *	sd: standard deviation of the distribution
 *	Return: pointer to array
 *
 *	Note: caller should free the array.
 */
int* generate_random_numbers_with_normal_distribution(unsigned int sz, double mean, double sd);

void generate_samples();

#endif // !_RANDOM_GENERATOR_HPP_
