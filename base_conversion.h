/*
Header file for base conversion functions.

Written by Stephen Chuang.
Last updated 28 March 2023.
*/


#ifndef BASE_CONVERSION_H
#define BASE_CONVERSION_H


#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_set>
#include "debug.h"


typedef struct range_pair {
    int range_start;
    int range_end;
} range_pair;


#define int long long
#define int_vec std::vector<long long>
#define str std::string

#define MAX_LENGTH      12
#define MAX_BASE        36
#define MAX_INT         1000000000 // 10^9
#define LARGE_THRESHOLD 100000     // 10^5
#define MAX_ITERATIONS  2500000    // You may change this. O(n) time.
#define OLD_MAX_ITER    25000      // You may change this. O(n^2) time.

#define BINARY      2
#define OCTAL       8
#define DECIMAL     10
#define HEXADECIMAL 16

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
range_pair frac_convert(int_vec &num, int den, int_vec &ints, int base);


// Finds if there are any repeats of the first numerator using the tortoise and
// hare algorithm.
range_pair find_repeat(int_vec num);


// Finds the earliest repeat in a sequence and returns the indices of the
// start and end.
range_pair subsequence_repeat(int_vec sequence, size_t end);


// Finds the second repeat of an element in the sequence.
size_t second_repeat(int test_num, int_vec values);


// Fraction base conversion, but using std::unordered_set to track repeated 
// numerators. Faster with smaller input.
range_pair frac_convert_set(int_vec &num, int den, int_vec &ints, int base);


// Finds the indices of the first two instances of key in num.
void find_first_two(range_pair &rp, int_vec num, int key);


// Prints the integer parts obtained from the fractional base conversion
// algorithm.
void print_result(int_vec int_parts, bool periodic, int start, int end);


// Prints the result if periodic.
void print_periodic(int_vec int_parts, int start, int end);


// Performs decimal integer base conversion without having to read input from 
// the user.
str auto_dec_int_conversion(int value, int new_base);


// Reverses a string.
str reverse_string(str input_str);


#endif
