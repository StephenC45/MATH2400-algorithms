/*
Implementation of the Euclidean algorithm in C++. This program also prints every
iteration with all mathematical operators aligned.

Written by Stephen Chuang.
Last updated on 31 May 2022.

Report errors or bugs to: stephen.chuang@student.unsw.edu.au

Known issues: none

Limitations: 
-> Maximum inputs of around 9 quintillion (9 * 10^18) due to integer limits.
*/



#include <cmath>
#include <iomanip>
#include <iostream>



// Returns the larger of two numbers.
long long max(long long a, long long b);

// Runs the Euclidean algorithm to calculate the standard GCD, prints out each
// step, and then returns the GCD.
long long euclidean(long long a, long long b, int output_width);

// Prints a single step of the Euclidean algorithm.
void print_step(long long a, long long b, long long q, long long r, int width);



int main(void) {
    // Read two numbers from the user.
    long long input1;
    long long input2;
    std::cout << "Enter 2 positive integers (space separated): ";
    std::cin >> input1 >> input2;

    // Input validation.
    if (input1 <= 0 || input2 <= 0) {
        std::cerr << "Error: invalid input.\n";
        exit(EXIT_FAILURE);
    }

    // Determine width for formatted printing.
    int width = log10(max(input1, input2)) + 1;

    // Run the Euclidean algorithm, storing the result in a variable.
    long long result;
    if (input1 > input2) {
        result = euclidean(input1, input2, width);
    } else {
        result = euclidean(input2, input1, width);
    }

    // Print the GCD and terminate the program.
    std::cout << "GCD is: " << result << '\n';
    return 0;
}


// Returns the larger of two numbers.
long long max(long long a, long long b) {
    if (a > b) {
        return a;
    }
    return b;
}

// Runs the Euclidean algorithm to calculate the standard GCD, prints out each
// step, and then returns the GCD.
long long euclidean(long long a, long long b, int output_width) {
    long long quotient;
    long long remainder;

    std::cout << "\nCalculating GCD of " << a << " and " << b << "\n\n";

    // First iteration.
    remainder = a % b;
    quotient = a / b;
    print_step(a, b, quotient, remainder, output_width);
    int iteration_count = 1;

    // Keep iterating until remainder is zero.
    while (remainder != 0) {
        a = b;
        b = remainder;
        remainder = a % b;
        quotient = a / b;
        print_step(a, b, quotient, remainder, output_width);
        ++iteration_count;
    }

    std::cout << "\nNumber of iterations: " << iteration_count << '\n';

    return b;
}

// Prints a single step of the Euclidean algorithm.
void print_step(long long a, long long b, long long q, long long r, int width) {
    // Print a statement of the form 'a = q * b + r'.
    std::cout << std::setw(width) << a << " = ";
    std::cout << std::setw(width) << q << " * ";
    std::cout << std::setw(width) << b << " + ";
    std::cout << std::setw(width) << r << '\n';
    return;
}
