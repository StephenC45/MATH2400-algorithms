/*
Implementation of continued fraction functions.

WRitten by Stephen Chuang.
Last updated 19 August 2022.
*/


#include "continued_fractions.h"


// The main code that converts a fraction into a continued fraction
// representation.
int do_convert_cont_frac(void) {
    // Read input from user.
    print_limitations_cf_convert();
    int numerator;
    int denominator;
    take_input_cf_convert(numerator, denominator);

    // Set up and run extended Euclidean algorithm.
    int_vec q;
    int_vec r;
    int_vec x;
    int_vec y;
    auto_eea(q, r, x, y, numerator, denominator);

    // Take the quotients and print them in continued fraction format.
    std::cout << numerator << " / " << denominator << " = ";
    print_cont_frac(q);
    return 0;
}


// Prints limitations for continued fraction conversion.
void print_limitations_cf_convert(void) {
    std::cout << "Limitations:\n";

    std::cout << "- Maximum numerator/denominator is 10^8.\n";
    std::cout << "- Minimum numerator/denominator is 0.\n\n";

    return;
}


// Prints limitations for displaying continued fraction convergents.
void print_limitations_cf_converge(void) {
    std::cout << "Limitations:\n";

    std::cout << "- Maximum numerator/denominator is 10^8.\n";
    std::cout << "- Minimum numerator/denominator is 0.\n";
    std::cout << "- May not print all convergents due to risk of integer ";
    std::cout << "overflow.\n\n";

    return;
}


// Converts a fraction into a continued fraction without having to read input
// from user.
void auto_convert_cont_frac(int numerator, int denominator) {
    // Set up and run extended Euclidean algorithm.
    int_vec q;
    int_vec r;
    int_vec x;
    int_vec y;
    auto_eea(q, r, x, y, numerator, denominator);

    // Take the quotients and print them in continued fraction format.
    std::cout << numerator << " / " << denominator << " = ";
    print_cont_frac(q);
    return;
}


// Reads numerator and denominator fron user.
void take_input_cf_convert(int &num, int &den) {
    // Read numerator.
    std::cout << "Enter numerator: ";
    std::cin >> num;

    // Read denominator.
    std::cout << "Enter numerator: ";
    std::cin >> den;

    // Error checking.
    if (num < 0 || num > MAX_INPUT) {
        std::cerr << RED << "Error: invalid numerator." << RESET << "\n";
        return;
    } else if (den <= 0 || den > MAX_INPUT) {
        std::cerr << RED << "Error: invalid denominator." << RESET << "\n";
        return;
    }

    return;
}


// Prints a continued fraction when given a vector containing quotients from
// Euclidean algorithm.
void print_cont_frac(int_vec quotients) {
    // Print opening bracket.
    std::cout << "[";
    
    for (size_t index = 0; index < quotients.size(); ++index) {
        if (index == 0) {
            // Printing integer part of continued fraction.
            std::cout << quotients[index] << "; ";
        } else {
            // Printing the rest of continued fraction.
            if (index != quotients.size() - 1) {
                // Print trailing space if not last element.
                std::cout << quotients[index] << ", ";
            } else {
                std::cout << quotients[index];
            }
        }
    }

    // Print closing bracket.
    std::cout << "]\n\n";
    return;
}
