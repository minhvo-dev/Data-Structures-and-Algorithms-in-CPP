/*
 *	File name:	"benchmark.cpp"
 *	Date:		9/7/2020 9:28:48 AM
 *	Author:		Vo, Dinh Tue Minh
 *	Purpose:	Implement benchmark schema
 */

#include "./inc/random_generator.hpp"
#include "./inc/benchmark.hpp"
#include "../inc/experimental_alias_declarations.hpp"
#include "../inc/sorts/experimental_heap_sort.hpp"
#include "../inc/sorts/experimental_merge_sort.hpp"
#include "../inc/sorts/experimental_quick_sort.hpp"
#include "../inc/sorts/experimental_shell_sort.hpp"

#include <cstring>
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace experimental;

long long calculate_running_time(int *arr, unsigned int sz, void (*sort)(int *, alias::size_type, std::less<int>)) {
	auto start = std::chrono::high_resolution_clock::now();
	sort(arr, sz, std::less<int>());
	auto stop = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

int* read_data_from_file(std::string const &fileName, unsigned int const SIZE) {
	int *arr = nullptr;
	unsigned int sz = 0;
	std::ifstream data(fileName);
	if (data) {
		data >> sz;
		if (sz == SIZE) {
			arr = new int[sz];
			for (unsigned int i = 0; i < sz; ++i) {
				data >> arr[i];
			}
		}
		data.close();
	}
	return arr;
}

long long benchmark(int *arr, unsigned const int sz, void (*sort)(int *arr, alias::size_type, std::less<int>)) {
	int *cpy = new int[sz];
	memcpy(cpy, arr, sizeof(int) * sz);

	auto start = std::chrono::high_resolution_clock::now();
	sort(cpy, sz, std::less<int>());
	auto stop = std::chrono::high_resolution_clock::now();

	delete[] cpy;

	return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

void benchmark_sorting_algorithms() {
	puts("Start benchmarking ...\n");
	std::ofstream heapSortOutput("heap_sort_benchmark_result.txt");
	std::ofstream mergeSortOutput("merge_sort_benchmark_result.txt");
	std::ofstream quickSortOutput("quick_sort_benchmark_result.txt");
	std::ofstream shellSortOutput("shell_sort_benchmark_result.txt");
	if (!heapSortOutput || !mergeSortOutput || !quickSortOutput || !shellSortOutput) {
		puts("Cannot open output files.");
		heapSortOutput.close();
		mergeSortOutput.close();
		quickSortOutput.close();
		shellSortOutput.close();
		return;
	}
	// lambda to write data to all output files
	auto write_to_all = [&heapSortOutput, &mergeSortOutput, &quickSortOutput, &shellSortOutput](std::string const &data) {
		heapSortOutput << data;
		mergeSortOutput << data;
		quickSortOutput << data;
		shellSortOutput << data;
	};
	auto benchmark_and_write_all = [&heapSortOutput, &mergeSortOutput, &quickSortOutput, &shellSortOutput](int *arr, unsigned int const arrSize) {
		heapSortOutput << benchmark(arr, arrSize, heap_sort) << ' ';
		mergeSortOutput << benchmark(arr, arrSize, merge_sort) << ' ';
		quickSortOutput << benchmark(arr, arrSize, quick_sort) << ' ';
		shellSortOutput << benchmark(arr, arrSize, shell_sort) << ' ';
	};

	int *arr = nullptr;

	/* SMALL KEYS */
	write_to_all("Small keys:\n");
	for (unsigned int iSz = 0, nSz = sizeof(SAMPLE_SIZES) / sizeof(SAMPLE_SIZES[0]); iSz < nSz; ++iSz) {
		unsigned int const sz = SAMPLE_SIZES[iSz];
		write_to_all('\t' + std::to_string(sz) + ":\n");
		{
			/* SORTED */
			write_to_all("\t\tSorted: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/small_keys_" << sz << '_' << iSample << "_sorted.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");

			/* REVERSED SORTED */
			write_to_all("\t\tReversed sorted: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/small_keys_" << sz << '_' << iSample << "_reversed_sorted.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");

			/* ALMOST SORTED */
			write_to_all("\t\tAlmost sorted: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/small_keys_" << sz << '_' << iSample << "_almost_sorted.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");

			/* RANDOM */
			write_to_all("\t\tRandom: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/small_keys_" << sz << '_' << iSample << "_random.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");

		}
	}

	/* UNIQUE KEYS */
	write_to_all("Unique keys:\n");
	for (unsigned int iSz = 0, nSz = sizeof(SAMPLE_SIZES) / sizeof(SAMPLE_SIZES[0]); iSz < nSz; ++iSz) {
		unsigned int const sz = SAMPLE_SIZES[iSz];
		write_to_all('\t' + std::to_string(sz) + ":\n");
		{
			/* SORTED */
			write_to_all("\t\tSorted: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/unique_keys_" << sz << '_' << iSample << "_sorted.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");

			/* REVERSED SORTED */
			write_to_all("\t\tReversed sorted: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/unique_keys_" << sz << '_' << iSample << "_reversed_sorted.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");

			/* ALMOST SORTED */
			write_to_all("\t\tAlmost sorted: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/unique_keys_" << sz << '_' << iSample << "_almost_sorted.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");

			/* RANDOM */
			write_to_all("\t\tRandom: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/unique_keys_" << sz << '_' << iSample << "_random.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");

		}
	}

	write_to_all("Normal distribution:\n");
	/* NORMAL DISTRIBUTION */
	for (unsigned int iSz = 0, nSz = sizeof(SAMPLE_SIZES) / sizeof(SAMPLE_SIZES[0]); iSz < nSz; ++iSz) {
		unsigned int const sz = SAMPLE_SIZES[iSz];
		write_to_all('\t' + std::to_string(sz) + ":\n");
		{
			/* SMALL */
			write_to_all("\t\tSmall: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/normal_distribution_" << sz << '_' << iSample << "_small.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");

			/* LARGE */
			write_to_all("\t\tLarge: ");
			for (unsigned int iSample = 1; iSample <= NUMBER_OF_SAMPLES; ++iSample) {
				// generate sample file name
				std::ostringstream oss;
				oss << "./data/sortings/normal_distribution_" << sz << '_' << iSample << "_large.txt";
				std::string fileName = oss.str();
				std::cout << "Benchmarking " << fileName << '\n';
				int *arr = read_data_from_file(fileName, sz);
				if (arr) {
					benchmark_and_write_all(arr, sz);
					std::cout << "Finished benchmarking " << fileName << '\n';
				}
				else {
					std::cout << "Error " << fileName << '\n';
				}
			}
			write_to_all("\n");
		}
	}

	delete[] arr;

	heapSortOutput.close();
	mergeSortOutput.close();
	quickSortOutput.close();
	shellSortOutput.close();

	puts("Finished benchmarking ...\n");
}