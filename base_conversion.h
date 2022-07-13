/*
Header file for base conversion functions.

Written by Stephen Chuang.
Last updated 6 July 2022.
*/


#ifndef BASE_CONVERSION_H
#define BASE_CONVERSION_H


#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include "debug.h"


typedef struct range_pair {
    int range_start;
    int range_end;
} range_pair;


#define int long long
#define int_vec std::vector<long long>
#define str std::string

#define MAX_LENGTH 12
#define MAX_BASE 36
#define MAX_INT 1000000000   // 10^9
#define MAX_ITERATIONS 25000 // You may change this. Currently O(n^2).

#define BLUE  "\033[36m"
#define RED   "\033[31m"
#define RESET "\033[0m"


// The main code that runs integer base conversion.
int do_integer_base_conversion(void);


// The main code that runs decimal fraction base converson.
int do_fraction_base_conversion(void);


// Prints limitations for the integer base conversion algorithm.
void print_limitations_int(void);


// Prints limitations for the decimal fraction base conversion algorithm.
void print_limitations_frac(void);


// Prints all characters and what number they represent.
void print_characters();


// Reads and validates input for integer base conversion.
void take_input_int(str &in, int &old_base, int &new_base, int_vec &digits);


// Checks if a string is a valid number in its base, and stores the decimal
// digits in a vector.
void check_string(str input, int base, int_vec &digits);


// Convert to decimal.
int to_decimal(int_vec digits, int base);


// Convert decimal to digits of specified base.
int_vec dec_to_base_digits(int decimal, int new_base);


// Checks validity of remainders.
bool check_remainder(int remainder);


// Converts digits into a number in the specified base.
str digits_to_str(int_vec in_v, int new_base);


// Reads and validates user input for the fraction base conversion algorithm.
void take_input_frac(int &num, int &den, int &base);


// Performs the base conversion algorithm on fractional parts.
range_pair frac_convert(int_vec &num, int_vec &den, int_vec &ints, int base);


// Finds if there are any repeats of the first numerator and first denominator.
range_pair find_repeat(int_vec num, int_vec den);


// Prints the integer parts obtained from the fractional base conversion
// algorithm.
void print_result(int_vec int_parts, bool periodic, int start, int end);


#endif
