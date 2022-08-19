/*
Header file for prime sieves.

Written by Stephen Chuang.
Last updated 19 August 2022.
*/


#ifndef SIEVE_H
#define SIEVE_H


#include <iostream>
#include <vector>
#include "debug.h"


#define bool_vec std::vector<bool>
#define int long long
#define int_vec std::vector<long long>

#define LARGE_INPUT_SIZE 20000000 // 2 * 10^7

#define YELLOW "\033[33m"
#define RED    "\033[31m"
#define RESET  "\033[0m"


// The main code that runs the sieve of Eratosthenes and prints output to a file
// primes.txt.
int do_eratosthenes(void);


// Prints limitations for sieve of Eratosthenes.
void print_limitations_eratosthenes(void);


// Handles user input for sieve of Eratosthenes.
void take_input_eratosthenes(int &limit);


// Performs sieve of Eratosthenes, returning an integer vector containing the
// primes up to and including n.
int_vec eratosthenes(int n);


// Performs sieve of Eratosthenes, but returns the raw Boolean vector.
bool_vec raw_eratosthenes(int n);


#endif
