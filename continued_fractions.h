/*
Header file for continued fraction functions.

Written by Stephen Chuang.
Last updated 19 August 2022.
*/


#ifndef CONTINUED_FRACTION_H
#define CONTINUED_FRACTION_H


#include <iostream>
#include <vector>
#include "debug.h"
#include "euclidean.h"


#define int long long
#define int_v std::vector<long long>

#define MAX_INPUT 1e8

#define RED    "\033[31m"
#define RESET  "\033[0m"
#define YELLOW "\033[33m"


// The main code that converts a fraction into a continued fraction
// representation.
int do_convert_cont_frac(void);


// The main code that converts a fraction into its continued fraction
// representation and prints convergents and error bounds.
int do_cont_frac_convergents(void);


// Prints limitations for continued fraction conversion.
void print_limitations_cf_convert(void);


// Prints limitations for displaying continued fraction convergents.
void print_limitations_cf_converge(void);


// Converts a fraction into a continued fraction without having to read input
// from user.
void auto_cont_frac(int n, int d, int_v &q, int_v &r, int_v &x, int_v &y);


// Reads numerator and denominator fron user.
void take_input_cf_convert(int &num, int &den);


// Prints a continued fraction when given a vector containing quotients from
// Euclidean algorithm.
void print_cont_frac(int_v quotients);


// Returns the absolute value of the input.
int absolute_val(int input);


// Prints convergents.
void print_convergents(int_v q, int_v x, int_v y);


// Finds the error bound of convergent i.
int calculate_error_bound(int_v q, int_v x, size_t i);


// Prints messages about where the program stopped printing convergents.
void print_convergent_stop(int stop_point);


#endif
