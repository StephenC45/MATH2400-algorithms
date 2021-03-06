/*
Implementation of base conversion functions.

This is the older version where decimal fraction base conversion is slower but
produces results that are closer to the simplest possible period.

Written by Stephen Chuang.
Last updated 14 July 2022.
*/


#include "base_conversion.h"


// The main code that runs integer base conversion.
int do_integer_base_conversion(void) {
    print_limitations_int();
    // Tell user how to input their string.
    std::cout << "\nCharacters represent the following base-10 numbers:\n";
    print_characters();
    
    // Read input and separate to digits.
    str input;
    int original_base;
    int new_base;
    int_vec digits;
    take_input_int(input, original_base, new_base, digits);

    // Convert input to individual digits.
    int decimal_val = to_decimal(digits, original_base);
    
    // Convert decimal number to new base.
    int_vec result_v = dec_to_base_digits(decimal_val, new_base);
    str result = digits_to_str(result_v, new_base);
    std::cout << "\nYour number in base-" << new_base << ": " << result << '\n';
    return 0;
}


// The main code that runs decimal fraction base conversion.
int do_fraction_base_conversion(void) {
    print_limitations_frac();
    // Read user input for numerator and denominator.
    int numerator;
    int denominator;
    int new_base;
    bool periodic = true;
    take_input_frac(numerator, denominator, new_base);

    // Vectors to store the integer and fractional parts after multiplying by
    // the base.
    int_vec numerators;
    int_vec denominators;
    int_vec integer_parts;
    numerators.reserve(OLD_MAX_ITER);
    denominators.reserve(OLD_MAX_ITER);
    integer_parts.reserve(OLD_MAX_ITER);

    // Perform first iteration.
    int product = numerator * new_base;
    numerators.push_back(product % denominator);
    denominators.push_back(denominator);
    integer_parts.push_back(product / denominator);

    // Finish the rest of the base conversion.
    range_pair range;
    range = frac_convert(numerators, denominators, integer_parts, new_base);
    if (range.range_start == -1 || range.range_end == -1) {
        periodic = false;
    }

    // Print the result.
    std::cout << "\n" << numerator << " / " << denominator << " in base-";
    std::cout << new_base << ": 0.";
    print_result(integer_parts, periodic, range.range_start, range.range_end);
    return 0;
}


// Prints limitations for the integer base conversion algorithm.
void print_limitations_int(void) {
    std::cout << "Limitations:\n";
    
    std::cout << "- Maximum string length is " << MAX_LENGTH << " chars ";
    std::cout << "(configurable in base_conversion.h).\n";
    std::cout << "- Maximum base of 36.\n";
    return;
}


// Prints limitations for the decimal fraction base conversion algorithm.
void print_limitations_frac(void) {
    std::cout << "Limitations:\n";
    
    std::cout << "- Time complexity O(n^2) so choose OLD_MAX_ITER (";
    std::cout << "configurable in base_conversion.h) carefully.\n- This prog";
    std::cout << "ram may be reduced to O(n * log(n)) time complexity later.\n";
    std::cout << "- This program may not always produce the simplest possible ";
    std::cout << "period.\n";
    std::cout << "- Does not tolerate fractions larger than or equal to 1.\n";
    std::cout << "- No protections from integer overflow.\n\n";
    return;
}


// Prints all characters and what number they represent.
void print_characters() {
    for (int i = 0; i < 26; ++i) {
        if (i > 0 && i % 6 == 0) {
            std::cout << '\n';
        } else if (i > 0) {
            std::cout << '\t';
        }

        char ch = 'A' + i;
        std::cout << ch << " = " << i + 10;
    }

    std::cout << "\n\n";
    return;
}


// Reads and validates input for integer base conversion.
void take_input_int(str &in, int &old_base, int &new_base, int_vec &digits) {
    std::cout << "Enter a positive integer: ";
    std::cin >> in;
    if (in.length() > MAX_LENGTH) {
        std::cerr << RED << "Error: integers this large may cause integer ";
        std::cerr << "overflow.\n" << RESET;
        exit(EXIT_FAILURE);
    }

    std::cout << "This number is in base: ";
    std::cin >> old_base;
    if (old_base < 2 || old_base > MAX_BASE) {
        std::cerr << RED << "Error: invalid base.\n" << RESET;
        digits.~vector();
        exit(EXIT_FAILURE);
    }
    check_string(in, old_base, digits);

    std::cout << "Convert to base: ";
    std::cin >> new_base;
    if (new_base < 2 || new_base > MAX_BASE) {
        std::cerr << RED << "Error: invalid base.\n" << RESET;
        digits.~vector();
        exit(EXIT_FAILURE);
    }

    return;
}


// Checks if a string is a valid number in its base, and stores the decimal
// digits in a vector.
void check_string(str input, int base, int_vec &digits) {
    for (char ch : input) {    
        // Convert letters to numbers.
        int digit;
        if (isdigit(ch)) {
            digit = ch - '0';
        } else if (islower(ch)) {
            digit = ch - 'a' + 10;
        } else if (isupper(ch)) {
            digit = ch - 'A' + 10;
        } else {
            std::cerr << RED << "Error: invalid digit '" << ch << "'.\n";
            std::cerr << RESET;
            digits.~vector();
            exit(EXIT_FAILURE);
        }

        if (digit >= base) {
            std::cerr << RED << "Error: cannot have digit '" << ch << "' = ";
            std::cerr << digit << " in base-" << base << "." << '\n';
            std::cerr << RESET;
            digits.~vector();
            exit(EXIT_FAILURE);
        }

        digits.push_back(digit);
    }
    
    return;
}


// Convert to decimal.
int to_decimal(int_vec digits, int base) {
    int result = 0;
    
    int power = 0;
    while (digits.size()) {
        // Take the last digit remaining and raise to the right power.
        int new_digit = digits[digits.size() - 1];
        digits.pop_back();
        result += new_digit * pow(base, power);
        ++power;
    }

    return result;
}


// Convert decimal to specified base.
int_vec dec_to_base_digits(int decimal, int new_base) {
    int_vec new_digits;
    int number = decimal;
    int quotient = 9999999999;

    while (quotient != 0) {
        quotient = number / new_base;
        int remainder = number % new_base;
        if (!check_remainder(remainder)) {
            new_digits.~vector();
            exit(EXIT_FAILURE);
        }
        new_digits.push_back(remainder);
        number = quotient;
    }
    
    return new_digits;
}


// Checks validity of remainders.
bool check_remainder(int remainder) {
    if (remainder < 0) {
        std::cerr << RED << "Error: negative remainder produced. This might";
        std::cerr << " have been produced by integer overflow.\n" << RESET;
        return false;
    }
    return true;
}


// Converts digits into a number in the specified base.
str digits_to_str(int_vec in_v, int new_base) {
    str result = "";
    while (in_v.size()) {
        // Take the last digit remaining.
        int new_digit = in_v[in_v.size() - 1];
        
        char new_character = '\0';
        if (new_digit >= new_base) {
            std::cerr << RED << "Error: invalid digit " << new_digit;
            std::cerr << " produced when converting to base-" << new_base;
            std::cerr << ".\n" << RESET;
            in_v.~vector();
            exit(EXIT_FAILURE);
        } else if (new_digit < 10) {
            new_character = new_digit + '0';
        } else {
            new_character = new_digit - 10 + 'A';
        }

        result += new_character;
        in_v.pop_back();
    }

    return result;
}


// Reads and validates user input for the fraction base conversion algorithm.
void take_input_frac(int &num, int &den, int &base) {
    std::cout << "This program terminates after " << OLD_MAX_ITER;
    std::cout << " iterations.\n\n";
    
    // Read the numerator.
    std::cout << "Enter base-10 numerator: ";
    std::cin >> num;
    if (num > MAX_INT) {
        std::cerr << RED << "Error: numerator too large.\n" << RESET;
        exit(EXIT_FAILURE);
    }

    // Read the denominator.
    std::cout << "Enter base-10 denominator: ";
    std::cin >> den;
    if (den > MAX_INT || den <= num) {
        std::cerr << RED << "Error: denominator too large.\n" << RESET;
        exit(EXIT_FAILURE);
    }
    
    // Read the new base.
    std::cout << "Enter base to convert to (2 - 10): ";
    std::cin >> base;
    if (base < 2 || base > 10) {
        std::cerr << RED << "Error: invalid base.\n" << RESET;
        exit(EXIT_FAILURE);
    }

    return;
}


// Performs the base conversion algorithm on fractional parts.
range_pair frac_convert(int_vec &num, int_vec &den, int_vec &ints, int base) {
    range_pair result;
    
    // OLD_MAX_ITER prevents infinite looping.
    while (num.size() < OLD_MAX_ITER && num[num.size() - 1]) {
        int product = num[num.size() - 1] * base;
        int new_numer = product % den[den.size() - 1];
        int new_denom = den[den.size() - 1];
        int new_integer_part = product / new_denom;

        num.push_back(new_numer);
        den.push_back(new_denom);
        ints.push_back(new_integer_part);

        int repeat_index = old_is_repeat(new_numer, new_denom, num, den);
        if (repeat_index >= 0) {
            std::cout << "\nThis base conversion is periodic. The periodic ";
            std::cout << "part will be highlighted in " << BLUE << "blue";
            std::cout << RESET << ".\n";
            result.range_start = repeat_index;
            result.range_end = ints.size() - 1;
            return result;
        }
    }

    if (num.size() == OLD_MAX_ITER) {
        std::cout << RED << "\nTerminated prematurely after " << OLD_MAX_ITER;
        std::cout << " iterations.\n" << RESET;
    } else {
        std::cout << "\nThis base conversion is terminating.\n";
    }

    result.range_start = -1;
    result.range_end = -1;
    return result;
}


// Checks if a numerator-denominator pair has appeared before. Returns true if
// they are found, or false otherwise.
int old_is_repeat(int test_num, int test_den, int_vec num, int_vec den) {
    // Check that numerators and denominators are both same size.
    assert(num.size() == den.size());

    // Search for a match and return true if a match is found.
    for (size_t index = 0; index < num.size() - 1; ++index) {
        if (num[index] == test_num && den[index] == test_den) {
            return index;
        }
    }

    // No match found.
    return -1;
}


// Prints the integer parts obtained from the fractional base conversion
// algorithm.
void print_result(int_vec int_parts, bool periodic, int start, int end) {  
    if (periodic) {
        // Print the non-periodic part.
        for (int index = 0; index <= start; ++index) {
            std::cout << int_parts[index];
        }

        // Print the periodic part in blue.
        std::cout << BLUE;
        for (int index = start + 1; index <= end; ++index) {
            std::cout << int_parts[index];
        }
        
        std::cout << RESET;
    } else {
        for (int value : int_parts) {
            std::cout << value;
        }
    }

    // Print error message if the program had to stop at OLD_MAX_ITER.
    if (int_parts.size() == OLD_MAX_ITER) {
        std::cerr << "\n\n" << RED << "Terminated prematurely after ";
        std::cerr << OLD_MAX_ITER << " iterations.\n\n" << RESET;
        return;
    }

    std::cout << "\n\n";
}
