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
    int_v q;
    int_v r;
    int_v x;
    int_v y;
    auto_eea(q, r, x, y, numerator, denominator);

    // Take the quotients and print them in continued fraction format.
    std::cout << numerator << " / " << denominator << " = ";
    print_cont_frac(q);
    return 0;
}


// The main code that converts a fraction into its continued fraction
// representation and prints convergents and error bounds.
int do_cont_frac_convergents(void) {
    // Read input from user.
    print_limitations_cf_converge();
    int numerator;
    int denominator;
    take_input_cf_convert(numerator, denominator);

    // Vectors to be used in converting to continued fraction and calculating
    // convergents and error bounds.
    int_v q;
    int_v r;
    int_v x;
    int_v y;

    // Convert to continued fraction.
    auto_cont_frac(numerator, denominator, q, r, x, y);

    // Print the convergents and error bounds.
    print_convergents(q, x, y);
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
void auto_cont_frac(int n, int d, int_v &q, int_v &r, int_v &x, int_v &y) {
    // Run extended Euclidean algorithm.
    auto_eea(q, r, x, y, n, d);

    // Take the quotients and print them in continued fraction format.
    std::cout << n << " / " << d << " = ";
    print_cont_frac(q);
    return;
}


// Reads numerator and denominator fron user.
void take_input_cf_convert(int &num, int &den) {
    // Read numerator.
    std::cout << "Enter numerator: ";
    std::cin >> num;

    // Read denominator.
    std::cout << "Enter denominator: ";
    std::cin >> den;

    // Error checking.
    if (num < 0 || num > MAX_INPUT) {
        std::cerr << RED << "Error: invalid numerator." << RESET << "\n";
        exit(EXIT_FAILURE);
    } else if (den <= 0 || den > MAX_INPUT) {
        std::cerr << RED << "Error: invalid denominator." << RESET << "\n";
        exit(EXIT_FAILURE);
    }

    return;
}


// Prints a continued fraction when given a vector containing quotients from
// Euclidean algorithm.
void print_cont_frac(int_v quotients) {
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


// Prints the absolute value of the integer input.
int absolute_val(int input) {
    if (input < 0) {
        return (input * -1);
    }
    return input;
}


// Prints convergents.
void print_convergents(int_v q, int_v x, int_v y) {    
    // Use of index here refers to the index in vector q.
    for (size_t index = 0; index < q.size(); ++index) {
        // Determine if convergent is positive or negative.
        bool convergent_negative = false;
        if (x[index + 2] < 0 && y[index + 2] < 0) {
            convergent_negative = true;
        } else if (x[index + 2] >= 0 && y[index + 2] >= 0) {
            convergent_negative = true;
        }
        
        // Terminate program if necessary to prevent integer overflow.
        if (x[index + 2] > MAX_INPUT || y[index + 2] > MAX_INPUT) {
            print_convergent_stop(index);
            return;
        }

        // Get the absolute values of x and y.
        int x_value = absolute_val(x[index + 2]);
        int y_value = absolute_val(y[index + 2]);

        // Print the convergent and its error bound.
        std::cout << "Convergent " << index << ": ";
        if (convergent_negative) {
            std::cout << "-";
        }
        std::cout << y_value << " / " << x_value << "\n";

        // Check that index is valid before calculating error bound.
        if ((index + 1) >= q.size() || (index + 2) >= x.size()) {
            std::cout << "Error bound cannot be calculated without illegal ";
            std::cout << "memory access.\n\n";
            return;
        }

        // Print error bound.
        std::cout << "The error bound for";
        std::cout << " this is 1 / ";
        std::cout << calculate_error_bound(q, x, index) << "\n\n";
    }
}


// Finds the error bound of convergent i.
int calculate_error_bound(int_v q, int_v x, size_t i) {
    // Take the next quotient and the square of the current value of x.
    int next_quotient = q[i + 1];
    int x_squared = x[i + 2] * x[i + 2];
    return (next_quotient * x_squared);
}


// Prints messages about where the program stopped printing convergents.
void print_convergent_stop(int stop_point) {
    // Print to stdout.
    std::cout << RED << "Program terminated to prevent integer ";
    std::cout << "overflow." << RESET << "\n";

    // Print the point where the program stopped,
    std::cout << "\nConvergent " << stop_point << " not printed.\n";

    // Print same error message to stderr.
    std::cerr << "\n" << RED << "Program terminated to prevent integer";
    std::cerr << " overflow." << RESET << "\n\n";

    return;
}
