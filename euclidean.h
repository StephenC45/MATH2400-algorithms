/*
Header file for Euclidean algorithm functions.

Written by Stephen Chuang.
Last updated 6 July 2022.
*/


#ifndef EUCLIDEAN_H
#define EUCLIDEAN_H


#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "debug.h"


// Store a pair of x and y values.
typedef struct xy_pair {
    long long x;
    long long y;
} xy_pair;


#define str std::string
#define int long long
#define int_v std::vector<long long>

#define MAX_INT_64 9e18

#define RED "\033[31m"
#define RESET "\033[0m"


// The main code that runs the Euclidean algorithm.
int do_euclidean(void);


// The main code that runs the extended Euclidean algorithm.
int do_extended_euclidean(void);


// Runs extended Euclidean algorithm without having to read user input.
// For use by other programs.
void auto_eea(int_v &q, int_v &r, int_v &x, int_v &y, int a, int b);


// Prints limitations for the Euclidean algorithm.
void print_limitations_ea(void);


// Prints limitations for the extended Euclidean algorithm.
void print_limitations_eea(void);


// Returns the larger of two numbers.
int max(long long a, long long b);


// Runs the Euclidean algorithm to calculate the standard GCD, prints out each
// step, and then returns the GCD.
int euclidean(long long a, long long b, int output_width);


// Prints a single step of the Euclidean algorithm.
void print_step(long long a, long long b, long long q, long long r, int width);


// Reads and validates input for the extended Euclidean algorithm.
void take_input_eea(int &num1, int &num2);


// Swaps two integers.
void swap_if_needed(int &num1, int &num2);


// Sets up the extended Euclidean algorithm.
void setup_eea(int_vec &q, int_vec &r, int_vec &x, int_vec &y, int n1, int n2);


// Performs extended Euclidean algorithm.
xy_pair extended_euclidean(int_v &q, int_v &r, int_v &x, int_v &y, int width);


// Performs normal Euclidean algorithm to get quotients and remainders.
// Returns the number of iterations, not the GCD.
int normal_euclidean(int_vec &q, int_vec &r, int width);


// Prints the result from the extended Euclidean algorithm in full.
void show_full_result(int_vec q, int_vec r, int_vec x, int_vec y, int width);


// Formatted printing of vector.
void format_print_vector(int_vec v, int width);


// Checks the result from the extended Euclidean algorithm.
bool check_success(int_vec q, int_vec r, int_vec x, int_vec y, int width);


#endif
