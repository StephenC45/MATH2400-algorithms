/*
A program that can help you check your answers to some types of MATH2400
problems.

Written by Stephen Chuang.
Last updated 5 July 2022.
*/


#include "debug.h"
#include "euclidean.h"

#define FEEDBACK_LINK "<blank>" // Update this later.


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
    } else {
        // Invalid input.
        std::cerr << RED << "Error: unknown input '" << input << "'" << RESET;
        std::cerr << RESET << "\n";
        return EXIT_FAILURE;
    }
}



// Prints a welcome message and a menu with options.
void print_welcome(void) {
    // Print the welcome message.
    std::cout << "Welcome.\n\nReport errors, suggest features, or give ";
    std::cout << "using the form here: " << FEEDBACK_LINK << "\n\n";

    // Print the menu of options.
    std::cout << "Enter an option below:\n\n";

    std::cout << " 1 - Euclidean Algorithm\n";
    std::cout << " 2 - Extended Euclidean Algorithm\n";

    std::cout << "\n";
    return;
}
