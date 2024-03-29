/*
Implementation of base conversion functions.

This is the newer version where decimal fraction base conversion is fast enough
to perform 2.5 million iterations (instead of the old 25,000) but may not 
produce the result with the shortest period.

Written by Stephen Chuang.
Last updated 27 March 2023.
*/


#include "base_conversion.h"


// The main code that runs integer base conversion.
int do_integer_base_conversion(void) {
    print_limitations_int();
    // Tell user how to input their string.
    std::cerr << "\nCharacters represent the following base-10 numbers:\n";
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
    std::cout << "\n" << input <<  " in base-" << new_base << ": " << result;
    std::cout << "\n\n";
    return 0;
}


// The main code that runs decimal fraction base conversion.
int do_fraction_base_conversion(void) {
    // Read user input for numerator and denominator.
    print_limitations_frac();
    int original_num;
    int denominator;
    int new_base;
    bool periodic = true;
    take_input_frac(original_num, denominator, new_base);

    // Calculate the integer part and set numerator to numerator of fractional
    // part only.
    int int_part = original_num / denominator;
    int numerator = original_num % denominator;

    // Perform base conversion on integer part.
    str converted_int = auto_dec_int_conversion(int_part, new_base);

    // Vectors to store the integer and fractional parts after multiplying by
    // the base.
    int_vec numerators;
    int_vec integer_parts;
    numerators.reserve(MAX_ITERATIONS);
    integer_parts.reserve(MAX_ITERATIONS);

    // Perform first iteration.
    int product = numerator * new_base;
    numerators.push_back(product % denominator);
    integer_parts.push_back(product / denominator);

    // Finish the rest of the base conversion.
    range_pair range;
    range = frac_convert(numerators, denominator, integer_parts, new_base);
    if (range.range_start == -1 || range.range_end == -1) {
        periodic = false;
    }

    // Print the result.
    if (!periodic && integer_parts.size() == MAX_ITERATIONS) {
        std::cout << RED << "\n\nTerminated prematurely after ";
        std::cout << MAX_ITERATIONS << " iterations.\n" << RESET;
    }
    std::cout << "\n" << original_num << " / " << denominator << " in base-";
    std::cout << new_base << ": " << converted_int << ".";
    print_result(integer_parts, periodic, range.range_start, range.range_end);
    return 0;
}


// Prints limitations for the integer base conversion algorithm.
void print_limitations_int(void) {
    std::cerr << "Limitations:\n";
    
    std::cerr << "- Maximum string length is " << MAX_LENGTH << " chars ";
    std::cerr << "(configurable in base_conversion.h).\n";
    std::cerr << "- Maximum base of 36.\n\n";
    return;
}


// Prints limitations for the decimal fraction base conversion algorithm.
void print_limitations_frac(void) {
    std::cerr << "Limitations:\n";
    
    std::cerr << "- This program rarely produces the simplest possible ";
    std::cerr << "period.\n- Do your own checking by writing out the periodic ";
    std::cerr << "part a few times to find the simplest possible period.\n\n";
    return;
}


// Prints all characters and what number they represent.
void print_characters() {
    for (int i = 0; i < 26; ++i) {
        if (i > 0 && i % 6 == 0) {
            // Print new line on every 6th entry.
            std::cerr << '\n';
        } else if (i > 0) {
            // Otherwise, print a tab character to separate entries.
            std::cerr << '\t';
        }

        // Print the value the character represents.
        char ch = 'A' + i;
        std::cerr << ch << " = " << i + 10;
    }

    std::cerr << "\n\n";
    return;
}


// Reads and validates input for integer base conversion.
void take_input_int(str &in, int &old_base, int &new_base, int_vec &digits) {
    std::cerr << "Enter a positive integer: ";
    if (std::cin >> in) {
        // String read successfully. Check that it is a valid string.
        if (in.length() > MAX_LENGTH) {
            std::cerr << RED << "Error: integers this large may cause integer ";
            std::cerr << "overflow.\n" << RESET;
            exit(EXIT_FAILURE);
        }
    } else {
        std::cerr << RED << "Error reading integer." << RESET << "\n";
        exit(EXIT_FAILURE);
    }

    std::cerr << "This number is in base: ";
    if (std::cin >> old_base) {
        // Old base successfully read. Perform input validation.
        if (old_base < 2 || old_base > MAX_BASE) {
            std::cerr << RED << "Error: invalid base.\n" << RESET;
            digits.~vector();
            exit(EXIT_FAILURE);
        }
        check_string(in, old_base, digits);
    } else {
        std::cerr << RED << "Error reading old base." << RESET << "\n";
        exit(EXIT_FAILURE);
    }

    std::cerr << "Convert to base: ";
    if (std::cin >> new_base) {
        // New base successfully read. Perform input validation.
        if (new_base < 2 || new_base > MAX_BASE) {
            std::cerr << RED << "Error: invalid base.\n" << RESET;
            digits.~vector();
            exit(EXIT_FAILURE);
        }
    } else {
        std::cerr << RED << "Error reading new base." << RESET << "\n";
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

    // Keep iterating until quotient is zero.
    while (quotient != 0) {
        quotient = number / new_base;
        int remainder = number % new_base;
        if (!check_remainder(remainder)) {
            // Remainder obtained does not make sense.
            new_digits.~vector();
            exit(EXIT_FAILURE);
        }
        // Store the remainder.
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
            // Digit produced that is greater than or equal to new base.
            std::cerr << RED << "Error: invalid digit " << new_digit;
            std::cerr << " produced when converting to base-" << new_base;
            std::cerr << ".\n" << RESET;
            in_v.~vector();
            exit(EXIT_FAILURE);
        } else if (new_digit < 10) {
            // Digit has value less than 10.
            new_character = new_digit + '0';
        } else {
            // Digit has value greater than 10, represent with a letter.
            new_character = new_digit - 10 + 'A';
        }

        result += new_character;
        in_v.pop_back();
    }

    return result;
}


// Reads and validates user input for the fraction base conversion algorithm.
void take_input_frac(int &num, int &den, int &base) {
    std::cerr << "This program terminates after " << MAX_ITERATIONS;
    std::cerr << " iterations.\n\n";
    
    // Read the numerator.
    std::cerr << "Enter base-10 numerator: ";
    if (std::cin >> num) {
        // Numerator read successfully.
        if (num > MAX_INT) {
            std::cerr << RED << "Error: numerator too large." << RESET << "\n";
            exit(EXIT_FAILURE);
        }
    } else {
        std::cerr << RED << "Error reading numerator." << RESET << "\n";
        exit(EXIT_FAILURE);
    }

    // Read the denominator.
    std::cerr << "Enter base-10 denominator: ";
    if (std::cin >> den) {
        if (den > MAX_INT) {
            std::cerr << RED << "Error: denominator too large.\n" << RESET;
            exit(EXIT_FAILURE);
        }
    } else {
        std::cerr << RED << "Error reading denominator." << RESET << "\n";
        exit(EXIT_FAILURE);
    }
    
    // Read the new base.
    std::cerr << "Enter base to convert to (2 - 10): ";
    if (std::cin >> base) {
        if (base < 2 || base > 10) {
            std::cerr << RED << "Error: invalid base.\n" << RESET;
            exit(EXIT_FAILURE);
        }
    } else {
        std::cerr << RED << "Error reading base." << RESET << "\n";
        exit(EXIT_FAILURE);
    }

    return;
}


// Performs the base conversion algorithm on fractional parts.
range_pair frac_convert(int_vec &num, int den, int_vec &ints, int base) {
    range_pair result;
    int product;
    int new_numer;

    if (den < LARGE_THRESHOLD) {
        return frac_convert_set(num, den, ints, base);
    } else {
        // MAX_ITERATIONS prevents infinite looping.
        while (num.size() < MAX_ITERATIONS && num[num.size() - 1]) {
            // Multiply numerator by the base.
            product = num[num.size() - 1] * base;
            new_numer = product % den;
            int new_integer_part = product / den;

            num.push_back(new_numer);
            ints.push_back(new_integer_part);
        }

        // Search for cycles. If a cycle is found, the expansion is periodic.
        result = find_repeat(num);
        if (result.range_start != -1 && result.range_end != -1) {
            // Cycle found.
            std::cout << "\nThis base conversion is periodic. The periodic ";
            std::cout << "part will be highlighted in " << BLUE << "blue";
            std::cout << RESET << ".\n";
        } else if (num.size() < MAX_ITERATIONS) {
            // No cycle found.
            std::cout << "\nThis base conversion is terminating.\n";
        }

        return result;
    }
}


// Finds if there are any repeats of the first numerator.
range_pair find_repeat(int_vec num) {    
    // A range_pair store the return value.
    range_pair return_val;
    // Two pointers.
    size_t tortoise_index = 1;
    size_t hare_index = 2;
    
    while (tortoise_index < num.size()
    && num[tortoise_index] != num[hare_index]) {
        // Increment tortoise by 1, hare by 2. If hare goes beyond end of the
        // vector, make it return to the start.
        ++tortoise_index;
        hare_index += 2;
        if (hare_index >= num.size()) {
            hare_index %= num.size();
        }
    }

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


// Fraction base conversion, but using std::unordered_set to track repeated 
// numerators. Faster with smaller input.
range_pair frac_convert_set(int_vec &num, int den, int_vec &ints, int base) {
    std::unordered_set<int> seen_numerators;
    seen_numerators.emplace(num[0]);

    range_pair result = {-1, -1};
    int product;
    int new_numer;
    
    // MAX_ITERATIONS prevents infinite looping.
    while (num.size() < MAX_ITERATIONS && num[num.size() - 1]) {
        // Multiply numerator by the base.
        product = num[num.size() - 1] * base;
        new_numer = product % den;
        int new_integer_part = product / den;

        num.push_back(new_numer);
        ints.push_back(new_integer_part);

        if (seen_numerators.find(new_numer) != seen_numerators.end()) {
            find_first_two(result, num, new_numer);
            break;
        } else {
            seen_numerators.emplace(new_numer);
        }
    }

    if (result.range_start != -1 && result.range_end != -1) {
        // Cycle found.
        std::cout << "\nThis base conversion is periodic. The periodic ";
        std::cout << "part will be highlighted in " << BLUE << "blue";
        std::cout << RESET << ".\n";
    } else if (num.size() < MAX_ITERATIONS) {
        // No cycle found.
        std::cout << "\nThis base conversion is terminating.\n";
    }

    return result;
}


// Finds the indices of the first two instances of key in num.
void find_first_two(range_pair &rp, int_vec num, int key) {
    int first_index = -1;
    int second_index = -1;

    for (size_t index = 0; index < num.size(); ++index) {
        if (first_index == -1 && num[index] == key) {
            first_index = index;
        } else if (first_index != -1 && num[index] == key) {
            second_index = index;
            rp.range_start = first_index;
            rp.range_end = second_index;
            return;
        }
    }

    return;
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
        std::cerr << "\n\n" << RED << "Terminated prematurely after ";
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


// Performs decimal integer base conversion without having to read input from 
// the user.
str auto_dec_int_conversion(int value, int new_base) {
    // Perform integer base conversion algorithm and return result as a string.
    str result = "";

    // First iteration. Add remainder to string.
    int quotient = value / new_base;
    int remainder = value % new_base;
    result += (remainder + '0');

    // Keep performing further iterations until quotuent is zero.
    while (quotient != 0) {
        int new_value = quotient;
        quotient = new_value / new_base;
        remainder = new_value % new_base;
        result += (remainder + '0');
    }

    // Reverse string before returning it.
    result = reverse_string(result);
    return result;
}


// Reverses a string.
str reverse_string(str input_str) {
    str reversed = "";

    // Add elements to string in reverse order.
    for (int index = input_str.size() - 1; index >= 0; --index) {
        reversed += input_str[index];
    }

    return reversed;
}