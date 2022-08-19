/*
Header file for linear Diophantine equation functions.

Written by Stephen Chuang.
Last updated 19 August 2022.
*/


#ifndef LINEAR_DIOPHANTINE_H
#define LINEAR_DIOPHANTINE_H


#include <cmath>
#include <iostream>
#include <vector>
#include "debug.h"
#include "euclidean.h"


#define int long long
#define int_vec std::vector<long long>

#define RED   "\033[31m"
#define RESET "\033[0m"


// The main code that runs the linear Diophantine equastion solver.
int do_solve_lde(void);


// Prints limitations for solving linear Diophantine equations.
void print_limitations_solve_lde(void);


// Reads user input.
void take_input_solve_lde(int &x_coeff, int &y_coeff, int &c);


// Solves the Diophantine equation given the value of c, remainders, x values,
// and y values from performing extended Euclidean algorithm.
void solve_diophantine(int c, int_v r, int_v x, int_v y);


// Prints solution to Diophantine equation.
void show_diophantine_soln(int x_const, int y_const, int xk, int yk);


#endif
