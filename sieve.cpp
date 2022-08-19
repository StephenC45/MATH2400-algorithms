/*
Header file for prime sieves.

Written by Stephen Chuang.
Last updated 19 August 2022.
*/


#include "sieve.h"


// The main code that runs the sieve of Eratosthenes and prints output to a file
// primes.txt.
int do_eratosthenes(void) {
    // Read input from the user.
    print_limitations_eratosthenes();
    int max_num;
    take_input_eratosthenes(max_num);

    // Perform sieve of Eratosthenes and print output.
    int_vec sieve_output = eratosthenes(max_num);
    for (int prime : sieve_output) {
        std::cout << prime << "\n";
    }
    return 0;
}


// Prints limitations for sieve of Eratosthenes.
void print_limitations_eratosthenes(void) {
    std::cerr << "Limitations:\n";

    std::cerr << "- Time complexity is O(n * log(log(n))) so will be slow for ";
    std::cerr << "inputs above 10-20 million or so.\n- More efficient sieves ";
    std::cerr << "exist but are harder to implement.\n- It is best to redirect";
    std::cerr << " output from this program. On Linux, use something like ";
    std::cerr << "\'./2400 > output.txt\'.\n\n";

    return;
}


// Handles user input for sieve of Eratosthenes.
void take_input_eratosthenes(int &limit) {
    // Read a single integer, the maximum number to be included in the sieve.
    std::cerr << "Enter number for sieve of Eratosthenes: ";
    if (std::cin >> limit) {
        // Input read successfully, now perform input validation.
        if (limit <= 1) {
            std::cerr << RED << "Error: input too small." << RESET << "\n";
            exit(EXIT_FAILURE);
        } else if (limit > LARGE_INPUT_SIZE) {
            std::cerr << YELLOW << "Warning: due to large input, this will ";
            std::cerr << "take a long time." << RESET << "\n";
        }
    } else {
        // Failed to read input.
        std::cerr << RED << "Error reading input." << RESET << "\n";
        exit(EXIT_FAILURE);
    }
}


// Performs sieve of Eratosthenes, returning an integer vector containing the 
// primes up to and including n.
int_vec eratosthenes(int n) {
    // Get the raw output.
    bool_vec raw_output = raw_eratosthenes(n);

    // Loop over the raw output and only store values that are prime.
    int_vec result;
    for (size_t index = 0; index < raw_output.size(); ++index) {
        if (raw_output[index]) {
            result.push_back(index);
        }
    }

    return result;
}


// Performs sieve of Eratosthenes, but returns the raw Boolean vector.
bool_vec raw_eratosthenes(int n) {
    // Initialise a vector all true initially.
    bool_vec result;
    result.reserve(n + 1);
    for (int i = 0; i <= n; ++i) {
        result.push_back(true);
    }

    // Zero and one are not prime.
    result[0] = false;
    result[1] = false;

    // Start from 2, go up to and including sqrt(n).
    for (int i = 2; i * i <= n; ++i) {
        // If entry i is true, mark all its multiples (except itself) as false.
        if (result[i]) {
            for (size_t j = 2 * i; j < result.size(); j += i) {
                result[j] = false;
            }
        }
    }

    return result;
}
