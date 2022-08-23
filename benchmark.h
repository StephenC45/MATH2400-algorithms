/*
Header file for benchmark functions.

Written by Stephen Chuang.
Last upated 23 August 2022.
*/


#ifndef BENCHMARK_H
#define BENCHMARK_H


// Include file based on operating system.
#ifdef _WIN32
#include <Windows.h>
#define SLEEP_COMMAND Sleep(20000)
#define INPUTFILE_SIZE 1560006262 // Intended size of input file in bytes.

#else
#include <unistd.h>
#define SLEEP_COMMAND sleep(20)
#define INPUTFILE_SIZE 1440005511 // Intended size of input file in bytes.
#endif


#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "base_conversion.h"
#include "continued_fractions.h"
#include "debug.h"
#include "euclidean.h"
#include "linear_diophantine.h"
#include "sieve.h"
#include "benchmark.h"


#define int long long

#define EUCLID_INPUT       "7540113804746346429 4660046610375530309\n"
#define EEA_INPUT          "701408733 433494437\n"
#define INT_BASE_INPUT     "ZZZZZZZZZZZZ\n36\n2\n"
#define FRAC_BASE_INPUT    "123456789\n987654321\n2\n"
#define CONVERGENT_INPUT   "39088169\n63245986\n"
#define DIOPHANTINE_INPUT  "701408733\n433494437\n123\n"
#define ERATOSTHENES_INPUT "2500000000\n"

#define EUCLID_ITER       12000000 // 1.2 * 10^7
#define EEA_ITER          12000000
#define INT_BASE_ITER     12000000 // 1.2 * 10^7
#define FRAC_BASE_ITER    250
#define CONVERGENT_ITER   12000000 // 1.2 * 10^7
#define DIOPHANTINE_ITER  12000000
#define ERATOSTHENES_ITER 1



#define REFERENCE_TIME 87500000 // 87.5 seconds.


// Input generator for the benchmark.
void generate_input(void);


// Generates repeated input.
void generate_repeat_input(std::ofstream &outfile, int count, str input);


// Calculates the I/O speed.
void show_io_speed(int time_microsec, int bytes);


// Prints information about the benchmark.
void print_benchmark_info(void);


// Benchmark function for normal Euclidean algorithm.
void benchmark_euclidean(int a, int b);


// Benchmark function for extended Euclidean algorithm.
void benchmark_eea(int a, int b);


// Benchmark function for integer base conversion.
void benchmark_int_base(str input, int old_base, int new_base);


// Benchmark function for fraction base conversion.
void benchmark_frac_base(int original_num, int denominator, int new_base);


// Benchmark function for continued fraction convergents.
void benchmark_convergents(int numerator, int denominator);


// Benchmark function for linear Diophantine solver.
void benchmark_diophantine(int x_coeff, int y_coeff, int constant);


// Benchmark function for sieve of Eratosthenes.
void benchmark_eratosthenes(int input);


// Prints error message for invalid input.
void print_input_error_message(void);


// Prints result for the entire benchmark.
void show_benchmark_result(int time);


#endif
