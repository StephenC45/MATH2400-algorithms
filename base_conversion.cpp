/*
Implementation of base conversion functions.

This is the newer version where decimal fraction base conversion is fast enough
to perform 2.5 million iterations (instead of the old 25,000) but almost never
produces a result with the simplest possible period.

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
    numerators.reserve(MAX_ITERATIONS);
    denominators.reserve(MAX_ITERATIONS);
    integer_parts.reserve(MAX_ITERATIONS);

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
    if (!periodic && integer_parts.size() == MAX_ITERATIONS) {
        std::cout << RED << "\n\nTerminated prematurely after ";
        std::cout << MAX_ITERATIONS << " iterations.\n" << RESET;
    }
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
    
    std::cout << "- This program rarely produces the simplest possible ";
    std::cout << "period.\n- Do your own checking by writing out the periodic ";
    std::cout << "part a few times to find the simplest possible period.\n";
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
    std::cout << "This program terminates after " << MAX_ITERATIONS;
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
    int product;
    int new_numer;
    int new_denom;
    
    // MAX_ITERATIONS prevents infinite looping.
    while (num.size() < MAX_ITERATIONS && num[num.size() - 1]) {
        product = num[num.size() - 1] * base;
        new_numer = product % den[den.size() - 1];
        new_denom = den[den.size() - 1]; // Same as previous denominator.
        int new_integer_part = product / new_denom;

        num.push_back(new_numer);
        den.push_back(new_denom); // Same as previous denominator.
        ints.push_back(new_integer_part);
    }

    result = find_repeat(num);
    if (result.range_start != -1 && result.range_end != -1) {
        std::cout << "\nThis base conversion is periodic. The periodic ";
        std::cout << "part will be highlighted in " << BLUE << "blue";
        std::cout << RESET << ".\n";
    } else if (num.size() < MAX_ITERATIONS) {
        std::cout << "\nThis base conversion is terminating.\n";
    }

    return result;
}


// Finds if there are any repeats of the first numerator.
range_pair find_repeat(int_vec num) {    
    // A range_pair store the return value.
    range_pair return_val;
    // Two pointers.
    size_t tortoise_index = 1;
    size_t hare_index = 2;
    //std::cout << "T: " << tortoise_index << ":" << num[tortoise_index] << "   H: " << hare_index << ":" << num[hare_index] << "\n";
    while (tortoise_index < num.size()
    && num[tortoise_index] != num[hare_index]) {
        // Increment tortoise by 1, hare by 2. If hare goes beyond end of the
        // vector, make it return to the start.
        ++tortoise_index;
        hare_index += 2;
        if (hare_index >= num.size()) {
            hare_index %= num.size();
        }
        //std::cout << "T: " << tortoise_index << ":" << num[tortoise_index] << "   H: " << hare_index << ":" << num[hare_index] << "\n";
    }
    //std::cout << "\n";

    // Tortoise and hare algorithm has finished.
    if (tortoise_index == num.size()) {
        // No match found.
        return_val.range_start = -1;
        return_val.range_end = -1;
        return return_val;
    } else {
        // Repeat found.
        return_val = subsequence_repeat(num, hare_index);
    }
    return return_val;
}


// Finds the earliest repeat in a sequence and returns the indices of the
// start and end.
range_pair subsequence_repeat(int_vec sequence, size_t end) {
    // Store the return value. Initialised later.
    range_pair result;

    // Move the tortoise back to the start to search for the start of the 
    // repeating cycle.
    size_t tortoise_index = 0;
    size_t hare_index = end;
    while (hare_index < sequence.size()
    && sequence[tortoise_index] != sequence[hare_index]) {
        // Move both at same speed until a match is found.
        ++tortoise_index;
        ++hare_index;
    }

    if (hare_index == sequence.size()) {
        // No repeat found.
        result.range_start = -1;
        result.range_end = -1;
        return result;
    } else {
        // Tortoise and hare have same value. Find the first instance of the
        // repeat.
        int test_number = sequence[tortoise_index];
        result.range_start = tortoise_index;
        result.range_end = second_repeat(test_number, sequence) - 1;
        return result;
    }
}


// Finds the earliest repeat of an element in the sequence.
size_t second_repeat(int test_num, int_vec values) {
    size_t index = 0;
    int repeat_count = 0;
    while (index < values.size() && repeat_count < 2) {
        if (values[index] == test_num) {
            ++repeat_count;
        }
        ++index;
    }

    return index;
}


// Prints the integer parts obtained from the fractional base conversion
// algorithm.
void print_result(int_vec int_parts, bool periodic, int start, int end) {  
    if (periodic) {
        print_periodic(int_parts, start, end);
    } else {
        for (int value : int_parts) {
            std::cout << value;
        }
    }

    if (!periodic && int_parts.size() == MAX_ITERATIONS) {
        // The algorithm was stopped due to reaching maximum number of 
        // iterations.
        std::cerr << RED << "\n\nTerminated prematurely after ";
        std::cerr << MAX_ITERATIONS << " iterations.\n" << RESET;
    } else {
        std::cout << "\n";
    }

    std::cout << "\n";
    return;
}


// Prints the result if periodic.
void print_periodic(int_vec int_parts, int start, int end) {
    // Print the non-periodic part in default colour.
    for (int index = 0; index <= start; ++index) {
        std::cout << int_parts[index];
    }

    // Print the periodic part in blue.
    std::cout << BLUE;
    for (int index = start + 1; index <= end; ++index) {
        std::cout << int_parts[index];
    }
    std::cout << RESET;
}
