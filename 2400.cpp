/*
A program that can help you check your answers to some types of MATH2400
problems.

Written by Stephen Chuang.
Last updated 6 July 2022.
*/


#include "base_conversion.h"
#include "debug.h"
#include "euclidean.h"

#define FEEDBACK_LINK "https://forms.gle/DpoX1eTry7V9yewV7"


// Prints a welcome message and a menu with options.
void print_welcome(void);



int32_t main(void) {
    // Take the user's input then decide what to run.
    std::string input;
    print_welcome();
    std::cin >> input;
    std::cout << "\n";

    if (input == "1") {
        return do_euclidean();
    } else if (input == "2") {
        return do_extended_euclidean();
    } else if (input == "3") {
        return do_integer_base_conversion();
    } else if (input == "4") {
        return do_fraction_base_conversion();
    }

    // Since none of the above triggered, input is invalid.
    std::cerr << RED << "Error: unknown input '" << input << "'" << RESET;
    std::cerr << RESET << "\n";
    return EXIT_FAILURE;
}



// Prints a welcome message and a menu with options.
void print_welcome(void) {
    // Print the welcome message.
    std::cout << "Welcome.\n\nReport errors, suggest features, or give ";
    std::cout << "using the form here: " << FEEDBACK_LINK << "\n\n";

    std::cout << "Be sure to pull from the repository regularly to get the ";
    std::cout << "latest features, bug fixes, and efficiency improvements.\n\n";

    // Print the menu of options.
    std::cout << "Enter an option below:\n\n";

    std::cout << " 1 - Euclidean Algorithm\n";
    std::cout << " 2 - Extended Euclidean Algorithm\n";
    std::cout << " 3 - Integer Base Conversion (up to base-36)\n";
    std::cout << " 4 - Decimal Fraction Base Conversion\n";

    std::cout << "\n";
    return;
}
