/*
Header implementation of benchmark functions.

Written by Stephen Chuang.
Last upated 23 August 2022.
*/


#include "benchmark.h"



// The main code that runs the benchmark.
int32_t main(void) {
    // Generate input for benchmark. Print I/O speed of program as well.
    print_benchmark_info();

    // Read input.
    std::cout << "Attempting to open input file...\n";
    std::ifstream input ("benchmark_input.txt");
    if (!input.is_open()) {
        // Only generate input if needed.
        std::cout << "Failed to open input file.\n";
        generate_input();
        std::cout << "Rerun this benchmark.\n\n";
        exit(EXIT_FAILURE);
    } else {
        std::cout << "Input file opened successfully.\n\n";
    }

    // Start measuring time.
    auto start = std::chrono::high_resolution_clock::now();

    // Run benchmark for Euclidean algorithm.
    std::cout << "Running Euclidean algorithm...\n";
    for (int i = 0; i < EUCLID_ITER; ++i) {
        int a;
        int b;
        if (input >> a >> b) {
            benchmark_euclidean(a, b);
        } else {
            print_input_error_message();
        }
    }

    // Run benchmark for extended Euclidean algorithm.
    std::cout << "Running extended Euclidean algorithm...\n";
    for (int i = 0; i < EEA_ITER; ++i) {
        int a;
        int b;
        if (input >> a >> b) {
            benchmark_eea(a, b);
        } else {
            print_input_error_message();
        }
    }

    // Run benchmark for integer base conversion.
    std::cout << "Running integer base conversion...\n";
    for (int i = 0; i < INT_BASE_ITER; ++i) {
        str input_int;
        int old_base;
        int new_base;
        if (input >> input_int >> old_base >> new_base) {
            benchmark_int_base(input_int, old_base, new_base);
        } else {
            print_input_error_message();
        }
    }

    // Run benchmark for fractional base conversion.
    std::cout << "Running fraction base conversion...\n";
    for (int i = 0; i < FRAC_BASE_ITER; ++i) {
        int num;
        int den;
        int base;
        if (input >> num >> den >> base) {
            benchmark_frac_base(num, den, base);
        } else {
            print_input_error_message();
        }
    }

    // Run benchmark for continued fraction convergents.
    std::cout << "Running continued fraction convergent calculation...\n";
    for (int i = 0; i < CONVERGENT_ITER; ++i) {
        int numerator;
        int denominator;
        if (input >> numerator >> denominator) {
            benchmark_convergents(numerator, denominator);
        } else {
            print_input_error_message();
        }
    }

    // Run benchmark for linear Diophantine solver.
    std::cout << "Running linear Diophantine solver...\n";
    for (int i = 0; i < DIOPHANTINE_ITER; ++i) {
        int x_coeff;
        int y_coeff;
        int constant;
        if (input >> x_coeff >> y_coeff >> constant) {
            benchmark_diophantine(x_coeff, y_coeff, constant);
        } else {
            print_input_error_message();
        }
    }

    // Run benchmark for sieve of Eratosthenes.
    std::cout << "Running sieve of Eratosthenes up to 2.5 billion...\n";
    int sieve_input;
    if (input >> sieve_input) {
        benchmark_eratosthenes(sieve_input);
    } else {
        print_input_error_message();
    }

    // Record finishing time and show results.
    auto end = std::chrono::high_resolution_clock::now();
    int time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    show_benchmark_result(time);
    input.close();

    return 0;
}



// Input generator for the benchmark.
void generate_input(void) {
    // Record start time.
    std::cout << "Generating input (1.56 GB)...\n";
    auto start = std::chrono::high_resolution_clock::now();
    
    // Open a file to store generated input.
    std::ofstream outfile ("benchmark_input.txt");
    if (!outfile.is_open()) {
        std::cerr << RED << "Error: could not write to file." << RESET << "\n";
        exit(EXIT_FAILURE);
    }

    // Generate input for Euclidean algorithm and extended Euclidean algorithm.
    generate_repeat_input(outfile, EUCLID_ITER, EUCLID_INPUT);
    generate_repeat_input(outfile, EEA_ITER, EEA_INPUT);

    // Generate input for base conversions.
    generate_repeat_input(outfile, INT_BASE_ITER, INT_BASE_INPUT);
    generate_repeat_input(outfile, FRAC_BASE_ITER, FRAC_BASE_INPUT);

    // Generate input for continued fraction convergents.
    generate_repeat_input(outfile, CONVERGENT_ITER, CONVERGENT_INPUT);

    // Generate input for Diophantine solver.
    generate_repeat_input(outfile, DIOPHANTINE_ITER, DIOPHANTINE_INPUT);
    
    // Generate input for sieve of Eratosthenes.
    outfile << ERATOSTHENES_INPUT;

    // Print time taken and I/O speed.
    auto end = std::chrono::high_resolution_clock::now();
    int time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    show_io_speed(time, INPUTFILE_SIZE);
    
    outfile.close();
    return;
}


// Generates repeated input.
void generate_repeat_input(std::ofstream &outfile, int count, str input) {
    for (int i = 0; i < count; ++i) {
        outfile << input;
    }
    return;
}


// Calculates the I/O speed.
void show_io_speed(int time_microsec, int bytes) {
    // Show time taken and how many byts were generated.
    std::cout << "\nTook " << time_microsec << " microseconds to generate ";
    std::cout << bytes << " bytes of input.\n";
    
    // Calculate bytes per microsecond and convert into MB per second.
    double bytes_per_us = double(bytes) / time_microsec;
    int bytes_per_sec = bytes_per_us * 1000000;
    int megabytes_per_sec = bytes_per_sec / 1000000;
    std::cout << "I/O speed: " << megabytes_per_sec << " MB/s\n\n";
    
    return;
}


// Prints information about the benchmark.
void print_benchmark_info(void) {
    std::cout << "\nBenchmark begins in 20 seconds.\n\n";
    
    std::cout << "Welcome.\n\n";

    std::cout << "This is a single-threaded benchmark that uses 1.56 GB of ";
    std::cout << "input and will test test your CPU performance in a few ";
    std::cout << "mathematical algorithms.\n\n";

    std::cout << "On most devices, this should finish in 1 to 5 minutes.\n\n";

    std::cout << "An Intel Core i5-1135G7 (28 W, 4.2 GHz) should score close ";
    std::cout << "to 1000.";
    std::cout << "\n\n";

    // Give user time to read the information.
    SLEEP_COMMAND;

    return;
}


// Benchmark function for normal Euclidean algorithm.
void benchmark_euclidean(int a, int b) {
    // Keep track of quotient and remainder only.
    int remainder;

    // First iteration.
    remainder = a % b;

    // Keep iterating until remainder is zero.
    while (remainder != 0) {
        a = b;
        b = remainder;
        remainder = a % b;
    }

    return;
}


// Benchmark function for extended Euclidean algorithm.
void benchmark_eea(int a, int b) {
    int_v q;
    int_v r;
    int_v x;
    int_v y;
    auto_silent_eea(q, r, x, y, a, b);
    return;
}


// Benchmark function for integer base conversion.
void benchmark_int_base(str input, int old_base, int new_base) {
    // Check that the digits entered are valid.
    int_vec digits;
    check_string(input, old_base, digits);

    // Convert input to individual digits.
    int decimal_val = to_decimal(digits, old_base);
    
    // Convert decimal number to new base.
    int_vec result_v = dec_to_base_digits(decimal_val, new_base);
    str result = digits_to_str(result_v, new_base);

    return;
}


// Benchmark function for fraction base conversion.
void benchmark_frac_base(int original_num, int denominator, int new_base) {
    // Calculate the integer part and set numerator to numerator of fractional
    // part only.
    int int_part = original_num / denominator;
    int numerator = original_num % denominator;

    // Perform base conversion on integer part.
    str converted_int = auto_dec_int_conversion(int_part, new_base);

    // Vectors to store the integer and fractional parts after multiplying by
    // the base.
    int_vec num;
    int_vec den;
    int_vec integer_parts;
    num.reserve(MAX_ITERATIONS);
    den.reserve(MAX_ITERATIONS);
    integer_parts.reserve(MAX_ITERATIONS);

    // Perform first iteration.
    int product = numerator * new_base;
    num.push_back(product % denominator);
    den.push_back(denominator);
    integer_parts.push_back(product / denominator);

    // Finish the rest of the base conversion.
    int conv_product;
    int new_numer;
    int new_denom;
    
    // MAX_ITERATIONS prevents infinite looping.
    while (num.size() < MAX_ITERATIONS && num[num.size() - 1]) {
        // Multiply numerator by the base.
        conv_product = num[num.size() - 1] * new_base;
        new_numer = product % den[den.size() - 1];
        new_denom = den[den.size() - 1]; // Same as previous denominator.
        int new_integer_part = conv_product / new_denom;

        num.push_back(new_numer);
        den.push_back(new_denom); // Same as previous denominator.
        integer_parts.push_back(new_integer_part);
    }

    // Search for cycles. If a cycle is found, the expansion is periodic.
    find_repeat(num);

    return;
}


// Benchmark function for continued fraction convergents.
void benchmark_convergents(int numerator, int denominator) {
    // Vectors to be used in converting to continued fraction and calculating
    // convergents and error bounds.
    int_v q;
    int_v r;
    int_v x;
    int_v y;

    // Convert to continued fraction using extended Euclidean algorithm.
    auto_silent_eea(q, r, x, y, numerator, denominator);

    // Calculate convergents silently. Use of index here refers to the index in
    // vector q.
    for (size_t index = 0; index < q.size(); ++index) {
        // Terminate program if necessary to prevent integer overflow.
        if (x[index + 2] > MAX_INPUT || y[index + 2] > MAX_INPUT) {
            return;
        }

        // Check that index is valid before calculating error bound.
        if ((index + 1) >= q.size() || (index + 2) >= x.size()) {
            return;
        }
    }

    return;
}


// Benchmark function for linear Diophantine solver.
void benchmark_diophantine(int x_coeff, int y_coeff, int constant) {
    // Perform extended Euclidean algorithm.
    int_v q;
    int_v r;
    int_v x;
    int_v y;
    auto_silent_eea(q, r, x, y, x_coeff, y_coeff);

    // Solve the Diophantine equation using the output from the extended
    // Euclidean algorithm. GCD is second last element of remainders.
    int gcd = r[r.size() - 2];

    // Error checking - ensure that constant divides the gcd of x and y 
    // coefficients.
    if (constant % gcd != 0) {
        return;
    }

    // Convert k coefficients to absolute values.
    int xk = abs(xk);
    int yk = abs(yk);

    return;
}


// Benchmark function for sieve of Eratosthenes.
void benchmark_eratosthenes(int input) {
    int_vec sieve_output = eratosthenes(input);
    return;
}


// Prints error message for invalid input.
void print_input_error_message(void) {
    std::cerr << RED << "Error: invalid input. This is most likely caused by ";
    std::cerr << "a malformed benchmark_input.txt file." << RESET << "\n";
    exit(EXIT_FAILURE);
}


// Prints result for the entire benchmark.
void show_benchmark_result(int time) {
    // Calculate score based on reference time. A doubling of score indicates
    // a doubling in single-threaded performance.
    int score = REFERENCE_TIME * 1000.0 / double(time);
    std::cout << "\nBenchmark took " << time << " microseconds.\n";
    std::cout << "Your score is " << score << ".\n\n"; 
}
