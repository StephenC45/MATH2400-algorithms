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
#define int_vec std::vector<long long>

#define MAX_INPUT 1e8

#define RED    "\033[31m"
#define RESET  "\033[0m"
#define YELLOW "\033[33m"


// The main code that converts a fraction into a continued fraction
// representation.
int do_convert_cont_frac(void);


// Prints limitations for continued fraction conversion.
void print_limitations_cf_convert(void);


// Prints limitations for displaying continued fraction convergents.
void print_limitations_cf_converge(void);


// Converts a fraction into a continued fraction without having to read input
// from user.
void auto_convert_cont_frac(int numerator, int denominator);


// Reads numerator and denominator fron user.
void take_input_cf_convert(int &num, int &den);


// Prints a continued fraction when given a vector containing quotients from
// Euclidean algorithm.
void print_cont_frac(int_vec quotients);


#endif
