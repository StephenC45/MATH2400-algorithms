/*
Header file for Chinese remainder theorem functions.

Written by Stephen Chuang.
Last updated 19 August 2022.
*/


#ifndef CRT_H
#define CRT_H


#include <cmath>
#include <iostream>
#include <stack>
#include <vector>
#include "debug.h"
#include "euclidean.h"


#define int long long
#define int_stack std::stack<long long>
#define int_vec std::vector<long long>

#define MAX_BRUTE_FORCE 1e7

#define RED    "\033[31m"
#define RESET  "\033[0m"
#define YELLOW "\033[33m"


// The main code that runs the CRT for linear congruences.
int do_crt_congruences(void);


// Prints limitations for CRT.
void print_limitations_crt(void);


// Reads input for CRT.
void take_input_crt(int_vec &constants, int_vec &moduli, int count);


// Calcuates LCM of all items in a vector.
int calculate_lcm(int_vec v);


// Calculates the product of all items in a vector.
int calculate_product(int_vec v);


// Uses Euclidean algorithm to find GCD.
int gcd(int a, int b);


// Brute forces for a solution. Used when moduli are not pairwise coprime.
int brute_force(int_vec constants, int_vec moduli, int lcm);


// Handles the situation where moduli are not pairwise coprime. Uses a brute
// force approach to solve if possible.
int handle_not_coprime(int_vec c, int_vec m, int lcm);


// Handles the situation where moduli are pairwise coprime. This is the normal
// application of Chinese remainder theorem.
int handle_coprime(int_vec c, int_vec m, int product);


// Solve an equation of the form kx = 1 (mod m) using extended Euclidean
// algorithm.
int solve_congruent_to_one(int x_coeff, int mod);


#endif
