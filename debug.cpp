/*
Implementation of debugging functions.

Written by Stephen Chuang.
Last updated 5 July 2022.
*/


#include "debug.h"


void print_vector(int_vec v) {
    for (int value : v) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return;
}
