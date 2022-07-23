/*
Header file for debugging functions.

Written by Stephen Chuang.
Last updated 6 July 2022.
*/


#ifndef DEBUG_H
#define DEBUG_H


#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>


#define bool_vec std::vector<bool>
#define int long long
#define int_vec std::vector<long long>
#define str std::string

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"


// Debugging functions that print the contents of a vector.
void print_vector(int_vec v);
void print_vector(bool_vec v);


#endif