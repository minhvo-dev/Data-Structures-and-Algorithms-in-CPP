/*
 *	File name:	"random_generator.cpp"
 *	Date:		9/7/2020 9:38:42 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implement random generators
 */

#include "./inc/random_generator.hpp"

#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

unsigned int generate_random_number_in_range(unsigned int low, unsigned int high) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(low, high);
	return d(gen);
}

int* generate_random_numbers_in_range(unsigned int sz, unsigned int low, unsigned int high) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(low, high);

	int *arr = new int[sz];
	for (unsigned int i = 0; i < sz; ++i) {
		arr[i] = d(gen);
	}

	return arr;
}

int* generate_random_numbers_with_normal_distribution(unsigned int sz, double mean, double sd) {
	static std::random_device rd{};
	static std::mt19937 gen(rd());
	std::normal_distribution<> d(mean, sd);

	int *arr = new int[sz];
	for (unsigned int i = 0; i < sz; ++i) {
		arr[i] = static_cast<int>(std::round(d(gen)));
	}

	return arr;
}

unsigned int const SAMPLE_SIZES[6] = { 1'000, 10'000, 100'000, 1'000'000, 10'000'000, 100'000'000 };
unsigned int const NUMBER_OF_SAMPLES = 5;

static constexpr char const* root = "data/sortings/";

void generate_samples() {
	puts("Generating sample...");
	
	for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
		for (unsigned int iSz = 0, nSz = sizeof(SAMPLE_SIZES) / sizeof(SAMPLE_SIZES[0]); iSz < nSz; ++iSz) {
			const unsigned int sz = SAMPLE_SIZES[iSz];
			int *arr = nullptr;
			{
				/*	Generate samples which contain small number of keys
				 *	The number of keys: 1% of the total size
				 */
				arr = generate_random_numbers_in_range(SAMPLE_SIZES[iSz], 1, static_cast<unsigned int>(sz * 0.01));
				std::ostringstream oss;
				oss << root << "small_keys_" << sz << '_' << iSample;

				// sorted
				{
					std::sort(arr, arr + sz);
					std::string fileName = oss.str() + "_sorted.txt";
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = 0; i < sz; ++i) {
							output << arr[i] << ' ';
						}
					}
					output.close();
				}
				// reversed sorted
				{
					std::string fileName = oss.str() + "_reversed_sorted.txt";
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = sz; i > 0;) {
							output << arr[--i] << ' ';
						}
					}
					output.close();
				}
				//almost sorted: 5% of the numbers are in wrong order
				{
					std::sort(arr, arr + sz);
					for (unsigned int iPair = 0, nPair = static_cast<unsigned int>(sz * 0.05) / 2; iPair < nPair; ++iPair) {
						unsigned int first, second;
						first = generate_random_number_in_range(0, sz - 1);
						do {
							second = generate_random_number_in_range(0, sz - 1);
						}
						while (second == first);
						std::swap(arr[first], arr[second]);
					}

					std::string fileName = oss.str() + "_almost_sorted.txt";
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = 0; i < sz; ++i) {
							output << arr[i] << ' ';
						}
					}
					output.close();
				}

				// random
				{
					for (unsigned int i = 0; i < sz; ++i) {
						unsigned int first, second;
						first = generate_random_number_in_range(0, sz - 1);
						do {
							second = generate_random_number_in_range(0, sz - 1);
						}
						while (first == second);
						std::swap(arr[first], arr[second]);
					}

					std::string fileName = oss.str() + "_random.txt";
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = 0; i < sz; ++i) {
							output << arr[i] << ' ';
						}
					}
					output.close();
				}

			}
			{
				for (unsigned int i = 0; i < sz; ++i) {
					arr[i] = i;
				}
				/*	Generate samples which contain unique keys */
				std::ostringstream oss;
				oss << root << "unique_keys_" << sz << '_' << iSample;

				// sorted
				{
					std::string fileName = oss.str() + "_sorted.txt";
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = 0; i < sz; ++i) {
							output << arr[i] << ' ';
						}
					}
					output.close();
				}
				// reversed sorted
				{
					std::string fileName = oss.str() + "_reversed_sorted.txt";
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = sz; i > 0;) {
							output << arr[--i] << ' ';
						}
					}
					output.close();
				}
				//almost sorted: 5% of the numbers are in wrong order
				{
					std::sort(arr, arr + sz);
					for (unsigned int iPair = 0, nPair = static_cast<unsigned int>(sz * 0.05) / 2; iPair < nPair; ++iPair) {
						unsigned int first, second;
						first = generate_random_number_in_range(0, sz - 1);
						do {
							second = generate_random_number_in_range(0, sz - 1);
						}
						while (second == first);
						std::swap(arr[first], arr[second]);
					}

					std::string fileName = oss.str() + "_almost_sorted.txt";
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = 0; i < sz; ++i) {
							output << arr[i] << ' ';
						}
					}
					output.close();
				}

				// random
				{
					for (unsigned int i = 0; i < sz; ++i) {
						unsigned int first, second;
						first = generate_random_number_in_range(0, sz - 1);
						do {
							second = generate_random_number_in_range(0, sz - 1);
						}
						while (first == second);
						std::swap(arr[first], arr[second]);
					}

					std::string fileName = oss.str() + "_random.txt";
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = 0; i < sz; ++i) {
							output << arr[i] << ' ';
						}
					}
					output.close();
				}
			}
			{
				// small normal distribution: mean = sz/2, sd = sz / 100
				{
					arr = generate_random_numbers_with_normal_distribution(sz, sz / 2.0, sz / 100.0);
					std::ostringstream oss;
					oss << root << "normal_distribution_" << sz << '_' << iSample << "_small.txt";
					std::string fileName = oss.str();
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = 0; i < sz; ++i) {
							output << arr[i] << ' ';
						}
					}
					output.close();
				}
				// large normal distribution: mean = sz/2, sd = sz / 10
				{
					arr = generate_random_numbers_with_normal_distribution(sz, sz / 2.0, sz / 10.0);
					std::ostringstream oss;
					oss << root << "normal_distribution_" << sz << '_' << iSample << "_large.txt";
					std::string fileName = oss.str();
					std::ofstream output(fileName);
					if (output) {
						output << sz << '\n';
						for (unsigned int i = 0; i < sz; ++i) {
							output << arr[i] << ' ';
						}
					}
					output.close();
				}

			}
			delete[] arr;
		}
	}
	puts("Finished generating samples...");
}