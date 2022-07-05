/*
Header file for debugging functions.

Written by Stephen Chuang.
Last updated 5 July 2022.
*/


#ifndef DEBUG_H
#define DEBUG_H


#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>


#define str std::string
#define int long long
#define int_vec std::vector<long long>

#define RED "\033[31m"
#define RESET "\033[0m"



// Debugging function that prints the contents of a vector.
void print_vector(int_vec v);


#endif