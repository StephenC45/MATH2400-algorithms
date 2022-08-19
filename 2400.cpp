/*
A program that can help you check your answers to some types of MATH2400
problems.

Written by Stephen Chuang.
Last updated 19 August 2022.
*/


#include "base_conversion.h"
#include "continued_fractions.h"
#include "crt.h"
#include "debug.h"
#include "euclidean.h"
#include "linear_diophantine.h"
#include "sieve.h"


#define FEEDBACK_LINK "https://forms.gle/DpoX1eTry7V9yewV7"


// Prints a welcome message and a menu with options.
void print_welcome(void);



int32_t main(void) {
    // Take the user's input then decide what to run.
    std::string input;
    print_welcome();
    std::cin >> input;
    std::cerr << "\n";

    if (input == "1") {
        return do_euclidean();
    } else if (input == "2") {
        return do_extended_euclidean();
    } else if (input == "3") {
        return do_integer_base_conversion();
    } else if (input == "4") {
        return do_fraction_base_conversion();
    } else if (input == "5") {
        return do_convert_cont_frac();
    } else if (input == "6") {
        return do_cont_frac_convergents();
    } else if (input == "7") {
        return do_solve_lde();
    } else if (input == "8") {
        return do_crt_congruences();
    } else if (input == "9") {
        return do_eratosthenes();
    }

    // Since none of the above triggered, input is invalid.
    std::cerr << RED << "Error: unknown input '" << input << "'" << RESET;
    std::cerr << "\n";
    return EXIT_FAILURE;
}



// Prints a welcome message and a menu with options.
void print_welcome(void) {
    // Print the welcome message.
    std::cerr << "Welcome.\n\nReport errors, suggest features, or give ";
    std::cerr << "using the form here: " << FEEDBACK_LINK << "\n\n";

    std::cerr << "Be sure to pull from the repository regularly to get the ";
    std::cerr << "latest features, bug fixes, and efficiency improvements.\n\n";

    // Print the menu of options.
    std::cerr << "Enter an option below:\n\n";

    std::cerr << " 1 - Euclidean Algorithm\n";
    std::cerr << " 2 - Extended Euclidean Algorithm\n";
    std::cerr << " 3 - Integer Base Conversion (up to base-36)\n";
    std::cerr << " 4 - Decimal Fraction Base Conversion\n";
    std::cerr << " 5 - Fraction to Continued Fraction\n";
    std::cerr << " 6 - Fraction to Continued Fraction Convergents\n";
    std::cerr << " 7 - Linear Diophantine Solver\n";
    std::cerr << " 8 - Chinese Remainder Theorem (Linear Congruences)\n";
    std::cerr << " 9 - Sieve of Eratosthenes\n";

    std::cerr << "\n";
    return;
}
