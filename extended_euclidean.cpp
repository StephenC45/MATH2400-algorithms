/*
Implementation of the extended Euclidean algorithm in C++. This program includes
error checking and output will be in red if an error occurs.

This program must be compiled using the C++11 standard or later. The compilation
command I used was:
g++ -x c++ -Wall -Wextra -Weffc++ -Wshadow -pedantic-errors -std=c++17 -g extended_euclidean.cpp -o extended_euclidean

For larger numbers, the output might look weird unless you have a very wide
terminal. In that case, you can run the program like this, enter 2 positive
integers as usual (you will not be prompted), and the output will be sent to a 
file called output.txt:
./extended_euclidean > output.txt

Written by Stephen Chuang
Last updated on 2 June 2022.

Report errors or bugs to: stephen.chuang@student.unsw.edu.au

Known issues: none

Limitations: 
-> Maximum inputs of around 1 billion (1 * 10^9) due to integer limits.
*/



#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cstdlib>

#define int long long
#define int_vec std::vector<long long>

#define RED "\033[31m"
#define RESET "\033[0m"

// Store a pair of x and y values.
typedef struct xy_pair {
    int x;
    int y;
} xy_pair;


// Reads and validates input.
void take_input(int &num1, int &num2);

// Swaps two integers.
void swap_if_needed(int &num1, int &num2);

// Returns the larger of two integers.
int max(int num1, int num2);

// Sets up the extended Euclidean algorithm.
void setup_eea(int_vec &q, int_vec &r, int_vec &x, int_vec &y, int n1, int n2);

// Performs extended Euclidean algorithm.
xy_pair extended_euclidean(int_vec &q, int_vec &r, int_vec &x, int_vec &y);

// Performs normal Euclidean algorithm to get quotients and remainders.
// Returns the number of iterations, not the GCD.
int normal_euclidean(int_vec &q, int_vec &r);

// Prints the result from the extended Euclidean algorithm in full.
void show_full_result(int_vec q, int_vec r, int_vec x, int_vec y, int width);

// Formatted printing of vector.
void format_print_vector(int_vec v, int width);

// Checks the result from the extended Euclidean algorithm.
bool check_success(int_vec q, int_vec r, int_vec x, int_vec y, int width);

// Debugging function that prints the contents of a vector.
void print_vector(int_vec v);



int32_t main(void) {
    // Read and validate user input.
    int input1;
    int input2;
    take_input(input1, input2);
    
    int_vec q;
    int_vec r;
    int_vec x;
    int_vec y;

    // Perform the extended Euclidean algorithm.
    setup_eea(q, r, x, y, input1, input2);
    extended_euclidean(q, r, x, y);

    // Check and show the results.
    int width = log10(max(input1, input2)) + 2;
    if (check_success(q, r, x, y, width)) {
        show_full_result(q, r, x, y, width);
        std::cout << "GCD = " << r[r.size() - 2] << '\n';
        std::cout << "  x = " << x[x.size() - 2] << '\n';
        std::cout << "  y = " << y[y.size() - 2] << '\n';
        std::cout << "\nGCD = " << x[x.size() - 2] << " * " << input1 << " + ";
        std::cout << y[y.size() - 2] << " * " << input2 << '\n';
        return 0;
    }

    return EXIT_FAILURE;
}


// Reads and validates input.
void take_input(int &num1, int &num2) {
    // Read input.
    std::cout << "Enter 2 positive integers (space separated): ";
    std::cin >> num1 >> num2;

    // Validate input.
    if (num1 <= 0 || num2 <= 0) {
        std::cerr << RED << "Error: invalid input.\n" << RESET;
        exit(EXIT_FAILURE);
    } else if (num1 > 1e9 || num2 > 1e9) {
        std::cerr << RED;
        std::cerr << "Error: inputs this large can cause integer overflow.\n";
        std::cerr << RESET;
        exit(EXIT_FAILURE);
    }

    // Swap input order if needed.
    swap_if_needed(num1, num2);
    return;
}

// Swaps two integers.
void swap_if_needed(int &num1, int &num2) {
    if (num2 > num1) {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
    return;
}

// Returns the larger of two integers.
int max(int num1, int num2) {
    if (num2 > num1) {
        return num2;
    }
    return num1;
}

// Sets up the extended Euclidean algorithm.
void setup_eea(int_vec &q, int_vec &r, int_vec &x, int_vec &y, int n1, int n2) {
    // Allocate memory to store values.
    q.reserve(45);
    r.reserve(45);
    x.reserve(45);
    y.reserve(45);
    
    // Start with two elements already in r, x, and y.
    r.push_back(n1);
    r.push_back(n2);
    x.push_back(1);
    x.push_back(0);
    y.push_back(0);
    y.push_back(1);
    return;
}

// Performs extended Euclidean algorithm.
xy_pair extended_euclidean(int_vec &q, int_vec &r, int_vec &x, int_vec &y) {
    // Fill quotients and remainders using normal Euclidean algorithm.
    int iteration_count = normal_euclidean(q, r);

    // Fill in the rows for x and y.
    for (int i = 0; i < iteration_count; ++i) {
        x.push_back(x[x.size() - 2] - (q[x.size() - 2] * x[x.size() - 1]));
        y.push_back(y[y.size() - 2] - (q[y.size() - 2] * y[y.size() - 1]));
    }

    xy_pair result;
    result.x = x[x.size() - 2];
    result.y = y[y.size() - 2];
    return result;
}

// Performs normal Euclidean algorithm to get quotients and remainders.
// Returns the number of iterations, not the GCD.
int normal_euclidean(int_vec &q, int_vec &r) {
    int iteration_count = 0;
    
    int remainder = 1;
    int quotient = 0;
    while (remainder != 0) {
        quotient = r[r.size() - 2] / r[r.size() - 1];
        remainder = r[r.size() - 2] % r[r.size() - 1];

        q.push_back(quotient);
        r.push_back(remainder);
        ++iteration_count;
    }

    return iteration_count;
}

// Prints the result from the extended Euclidean algorithm in full.
void show_full_result(int_vec q, int_vec r, int_vec x, int_vec y, int width) {
    std::cout << '\n';

    // Leave two blank entries to make quotients line up.
    std::cout << "q: || ";
    std::cout << std::setw(width) << "" << " | ";
    std::cout << std::setw(width) << "" << " | ";
    format_print_vector(q, width);

    std::cout << "r: || ";
    format_print_vector(r, width);

    std::cout << "x: || ";
    format_print_vector(x, width);

    std::cout << "y: || ";
    format_print_vector(y, width);

    std::cout << '\n';
}

// Formatted printing of vector.
void format_print_vector(int_vec v, int width) {
    for (int value : v) {
        std::cout << std::setw(width) << value << " | ";
    }
    std::cout << '\n';
    return;
}

// Checks the result from the extended Euclidean algorithm.
bool check_success(int_vec q, int_vec r, int_vec x, int_vec y, int width) {
    // Get the initial input and the penultimate element of r, x, and y.
    int num1 = r[0];
    int num2 = r[1];
    int gcd = r[r.size() - 2];
    int x_result = x[x.size() - 2];
    int y_result = y[y.size() - 2];

    if (gcd != (x_result * num1 + y_result * num2)) {
        int result = x_result * num1 + y_result * num2;
        std::cerr << RED << "\nError: wrong answer produced." << "\n\n";

        std::cerr << "GCD = " << gcd << '\n';
        std::cerr << "  x = " << x_result << "\n  y = " << y_result << "\n\n";

        std::cerr << "Expected result: x * " << num1;
        std::cerr << " + y * " << num2 << " = " << gcd << '\n';

        std::cerr << "  Actual result: x * " << num1;
        std::cerr << " + y * " << num2 << " = " << result << "\n\n";

        show_full_result(q, r, x, y, width);
        std::cerr << RESET;
        return false;
    }

    return true;
}

// Debugging function that prints the contents of a vector.
void print_vector(int_vec v) {
    for (int value : v) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return;
}
