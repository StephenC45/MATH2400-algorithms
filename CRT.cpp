/*
Implementation of Chinese remainder theorem functions.

Written by Stephen Chuang.
Last updated 18 August 2022.
*/


#include "CRT.h"


// The main code that runs the CRT for linear congruences.
int do_crt_congruences(void) {
    // Read number of congruences to solve.
    print_limitations_crt();
    int congruence_count;
    std::cout << "Enter number of congruences: ";
    std::cin >> congruence_count;

    // Read constants and moduli from user.
    int_vec moduli;
    int_vec constants;
    take_input_crt(constants, moduli, congruence_count);

    // Check that moduli are pairwise coprime.
    int product = calculate_product(moduli);
    if (product < 0) {
        // calculate_product() returned negative value so an error occurred.
        // moduli.~vector();
        // constants.~vector();
        return EXIT_FAILURE;
    }

    int lcm = calculate_lcm(moduli);
    if (lcm != product) {
        // Moduli not pairwise coprime.
        int solution = handle_not_coprime(constants, moduli, lcm);
        if (solution >= 0) {
            std::cout << "\nSolution: x = " << solution << " (mod " << lcm;
            std::cout << ")\n\n";
        }
    } else {
        // Moduli are pairwise coprime.
    }
    
    return 0;
}


// Prints limitations for CRT.
void print_limitations_crt(void) {
    std::cout << "Limitations:\n";

    std::cout << "- Only works for systems where all congruences are of the ";
    std::cout << "form 'x = k (mod m)'.\n";
    std::cout << "- Limited protection from integer overflow.\n";
    std::cout << "- Not giving enough input may cause segmentation faults, ";
    std::cout << "memory leaks, or other memory errors.\n\n";

    return;
}


// Reads input for CRT.
void take_input_crt(int_vec &constants, int_vec &moduli, int count) {
    std::cout << "Equations must be in the form x = k (mod m).\n";
    std::cout << "Enter pairs of constants k and moduli m:\n";
    int modulus;
    int constant;

    // Read constants and moduli from input.
    for (int i = 0; i < count; ++i) {
        if (std::cin >> constant) {
            constants.push_back(constant);
        } else {
            std::cerr << RED << "Error: insufficient input." << RESET << "\n";
        }

        if (std::cin >> modulus) {
            moduli.push_back(modulus);
        } else {
            std::cerr << RED << "Error: insufficient input." << RESET << "\n";
        }
    }

    // Check that the user has entered in enough numbers.
    size_t count_check = count;
    if (constants.size() < count_check || moduli.size() < count_check) {
        std::cerr << RED << "Error: insufficient input." << RESET << "\n";
        constants.~vector();
        moduli.~vector();
        exit (EXIT_FAILURE);
    }

    return;
}


// Calcuates LCM of all items in a vector.
int calculate_lcm(int_vec v) {
    // Push moduli onto a stack.
    int_stack mod_stack;

    for (int value : v) {
        mod_stack.push(value);
    }

    // Keep going until there are 2 elements left in the stack.
    while (mod_stack.size() >= 2) {
        int num1 = mod_stack.top();
        mod_stack.pop();
        int num2 = mod_stack.top();
        mod_stack.pop();

        mod_stack.push((num1 * num2) / gcd(num1, num2));
    }

    return mod_stack.top();
}


// Calculates the product of all items in a vector.
int calculate_product(int_vec v) {
    int product = 1;
    for (int value : v) {
        if (log10(product) + log10(value) > 18) {
            // Product and value will be larger than 10^18 when multiplied.
            std::cerr << RED << "Error: integer overflow in calculating ";
            std::cerr << "product of moduli." << RESET << "\n";
            return -1;
        }

        product *= value;
    }

    return product;

}


// Uses Euclidean algorithm to find GCD.
int gcd(int a, int b) {
    int remainder;

    // First iteration.
    remainder = a % b;

    // Keep iterating until remainder is zero.
    while (remainder != 0) {
        a = b;
        b = remainder;
        remainder = a % b;
    }

    return b;
}


// Brute forces for a solution. Used when moduli are not pairwise coprime.
int brute_force(int_vec constants, int_vec moduli, int lcm) {
    // Start from 0.
    int test = 0;
    while (test < lcm) {
        size_t index = 0;
        while (index < constants.size()) {
            // Check if test is solution to each equation.
            if (test % moduli[index] != constants[index]) {
                break; // Stop incrementing index.
            }
            ++index;
        }

        // test is solution to all congruences. Return the solution.
        if (index == constants.size()) {
            return test;
        }

        ++test;
    }

    // If loop finishes without returning a solution, there is no solution.
    std::cerr << RED << "Error: no solution found." << RESET << "\n";
    return -1;
}


// Handles the situation where moduli are not pairwise coprime.
int handle_not_coprime(int_vec c, int_vec m, int lcm) {
    // Inform user that moduli are not pairwise coprime.
    std::cerr << YELLOW << "\nWarning: moduli not pairwise coprime." << RESET;
    std::cerr << "\n";

    if (lcm > MAX_BRUTE_FORCE) {
        // LCM of moduli too large to brute force quickly.
        std::cerr << RED << "Error: brute force too inefficient for given";
        std::cerr << " system of congruences." << RESET << "\n";
        return -1;

    } else {
        // LCM of moduli small enough to quickly give solution with brute force
        // approach.
        std::cerr << "Applying brute force approach...\n";
        int solution = brute_force(c, m, lcm);
        return solution;
    }
}
