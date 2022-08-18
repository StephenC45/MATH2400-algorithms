/*
Implementation of Euclidean algorithm functions.

Written by Stephen Chuang.
Last updated 6 July 2022.
*/


#include "euclidean.h"


// The main code that runs the Euclidean algorithm.
int do_euclidean(void) {
    print_limitations_ea();
    // Read two numbers from the user.
    int num1;
    int num2;
    std::cout << "Enter 2 positive integers (space separated): ";
    std::cin >> num1 >> num2;

    // Input validation.
    if (num1 <= 0 || num2 <= 0 || num1 > MAX_INT_64 || num2 > MAX_INT_64) {
        std::cerr << "Error: invalid input.\n";
        exit(EXIT_FAILURE);
    }

    // Determine width for formatted printing.
    int width = log10(max(num1, num2)) + 1;

    // Run the Euclidean algorithm, storing the result in a variable.
    int result;
    if (num1 > num2) {
        result = euclidean(num1, num2, width);
    } else {
        result = euclidean(num2, num1, width);
    }

    // Print the GCD and terminate the program.
    std::cout << "GCD is: " << result << "\n\n";
    return 0;
}


// The main code that runs the extended Euclidean algorithm.
int do_extended_euclidean(void) {
    print_limitations_eea();
    // Read and validate user input. Then determine width of formatted printing.
    int input1;
    int input2;
    take_input_eea(input1, input2);
    int width = log10(max(input1, input2)) + 1;

    // Vectors to store quotients, remainders, x values, and y values.
    int_v q;
    int_v r;
    int_v x;
    int_v y;

    // Perform the extended Euclidean algorithm.
    setup_eea(q, r, x, y, input1, input2);
    extended_euclidean(q, r, x, y, width);

    // Check and show the results.
    width = log10(max(input1, input2)) + 2;
    if (check_success(q, r, x, y, width)) {
        show_full_result(q, r, x, y, width);
        std::cout << "GCD = " << r[r.size() - 2] << '\n';
        std::cout << "  x = " << x[x.size() - 2] << '\n';
        std::cout << "  y = " << y[y.size() - 2] << '\n';
        std::cout << "\nGCD = " << x[x.size() - 2] << " * " << input1 << " + ";
        std::cout << y[y.size() - 2] << " * " << input2 << "\n\n";
        return 0;
    }

    return EXIT_FAILURE;
}


// Prints limitations for the Euclidean algorithm.
void print_limitations_ea(void) {
    std::cout << "Limitations:\n";

    std::cout << "- Maximum input should be around 9 * 10^18 to avoid integer ";
    std::cout << "overflow.\n";
    std::cout << "- No protection from integer overflow.\n\n";

    return;
}


// Prints limitations for the extended Euclidean algorithm.
void print_limitations_eea(void) {
    std::cout << "Limitations:\n";

    std::cout << "- Maximum inputs of 10^9 to avoid integer overflow.\n\n";

    return;
}


// Returns the larger of two numbers.
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}


// Runs the Euclidean algorithm to calculate the standard GCD, prints out each
// step, and then returns the GCD.
int euclidean(int a, int b, int output_width) {
    // Keep track of quotient and remainder only.
    int quotient;
    int remainder;
    std::cout << "\n";

    // First iteration.
    remainder = a % b;
    quotient = a / b;
    print_step(a, b, quotient, remainder, output_width);
    int iteration_count = 1;

    // Keep iterating until remainder is zero.
    while (remainder != 0) {
        a = b;
        b = remainder;
        remainder = a % b;
        quotient = a / b;
        print_step(a, b, quotient, remainder, output_width);
        ++iteration_count;
    }

    std::cout << "\nNumber of iterations: " << iteration_count << '\n';
    return b;
}


// Prints a single step of the Euclidean algorithm.
void print_step(int a, int b, int q, int r, int width) {
    // Print a statement of the form 'a = q * b + r'.
    std::cout << std::setw(width) << a << " = ";
    std::cout << std::setw(width) << q << " * ";
    std::cout << std::setw(width) << b << " + ";
    std::cout << std::setw(width) << r << '\n';
    return;
}


// Reads and validates input for the extended Euclidean algorithm.
void take_input_eea(int &num1, int &num2) {
    // Read input.
    std::cout << "Enter 2 positive integers (space separated): ";
    std::cin >> num1 >> num2;

    // Validate input.
    if (num1 <= 0 || num2 <= 0) {
        std::cerr << RED << "Error: invalid input.\n" << RESET;
        exit(EXIT_FAILURE);
    } else if (num1 > 1e9 || num2 > 1e9) {
        std::cerr << RED;
        std::cerr << "Error: inputs this large can cause integer overflow.\n";
        std::cerr << RESET;
        exit(EXIT_FAILURE);
    }

    // Swap input order if needed. Uncomment line below if you need this.
    // swap_if_needed(num1, num2);
    return;
}


// Swaps two integers.
void swap_if_needed(int &num1, int &num2) {
    if (num2 > num1) {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
    return;
}


// Sets up the extended Euclidean algorithm.
void setup_eea(int_v &q, int_v &r, int_v &x, int_v &y, int n1, int n2) {
    // Allocate memory to store values.
    q.reserve(45);
    r.reserve(45);
    x.reserve(45);
    y.reserve(45);
    
    // Start with two elements already in r, x, and y.
    r.push_back(n1);
    r.push_back(n2);
    x.push_back(1);
    x.push_back(0);
    y.push_back(0);
    y.push_back(1);
    return;
}


// Performs extended Euclidean algorithm.
xy_pair extended_euclidean(int_v &q, int_v &r, int_v &x, int_v &y, int width) {
    // Fill quotients and remainders using normal Euclidean algorithm.
    int iteration_count = normal_euclidean(q, r, width);

    // Fill in the rows for x and y.
    for (int i = 0; i < iteration_count; ++i) {
        x.push_back(x[x.size() - 2] - (q[x.size() - 2] * x[x.size() - 1]));
        y.push_back(y[y.size() - 2] - (q[y.size() - 2] * y[y.size() - 1]));
    }

    xy_pair result;
    result.x = x[x.size() - 2];
    result.y = y[y.size() - 2];
    return result;
}


// Performs normal Euclidean algorithm to get quotients and remainders.
// Returns the number of iterations, not the GCD.
int normal_euclidean(int_v &q, int_v &r, int width) {
    int iteration_count = 0;
    
    // Initialise arbitrary values for remainder and quotient, print newline to
    // make output look neater.
    int remainder = 1;
    int quotient = 0;
    std::cout << "\n";

    while (remainder != 0) {
        // Update quotient and remainder vectors, printing steps along the way.
        quotient = r[r.size() - 2] / r[r.size() - 1];
        remainder = r[r.size() - 2] % r[r.size() - 1];
        int a = r[r.size() - 2];
        int b = r[r.size() - 1];
        print_step(a, b, quotient, remainder, width);

        q.push_back(quotient);
        r.push_back(remainder);
        ++iteration_count;
    }

    return iteration_count;
}


// Prints the result from the extended Euclidean algorithm in full.
void show_full_result(int_v q, int_v r, int_v x, int_v y, int width) {
    std::cout << '\n';

    // Leave two blank entries to make quotients line up.
    std::cout << "q: || ";
    std::cout << std::setw(width) << "" << " | ";
    std::cout << std::setw(width) << "" << " | ";
    format_print_vector(q, width);

    // Print the remainders.
    std::cout << "r: || ";
    format_print_vector(r, width);

    // Print the x values.
    std::cout << "x: || ";
    format_print_vector(x, width);

    // Print the y values.
    std::cout << "y: || ";
    format_print_vector(y, width);

    std::cout << '\n';
}


// Formatted printing of vector.
void format_print_vector(int_v v, int width) {
    for (int value : v) {
        std::cout << std::setw(width) << value << " | ";
    }
    std::cout << '\n';
    return;
}


// Checks the result from the extended Euclidean algorithm.
bool check_success(int_v q, int_v r, int_v x, int_v y, int width) {
    // Get the initial input and the penultimate element of r, x, and y.
    int num1 = r[0];
    int num2 = r[1];
    int gcd = r[r.size() - 2];
    int x_result = x[x.size() - 2];
    int y_result = y[y.size() - 2];

    if (gcd != (x_result * num1 + y_result * num2)) {
        int result = x_result * num1 + y_result * num2;
        std::cerr << RED << "\nError: wrong answer produced." << "\n\n";

        std::cerr << "GCD = " << gcd << '\n';
        std::cerr << "  x = " << x_result << "\n  y = " << y_result << "\n\n";

        std::cerr << "Expected result: x * " << num1;
        std::cerr << " + y * " << num2 << " = " << gcd << '\n';

        std::cerr << "  Actual result: x * " << num1;
        std::cerr << " + y * " << num2 << " = " << result << "\n\n";

        show_full_result(q, r, x, y, width);
        std::cerr << RESET;
        return false;
    }

    return true;
}
