/*
Implementation of linear Diophantine equation functions.

Written by Stephen Chuang.
Last updated 19 August 2022.
*/


#include "linear_diophantine.h"


// The main code that runs the linear Diophantine equastion solver.
int do_solve_lde(void) {
    // Read input from user.
    print_limitations_solve_lde();
    int x_coeff;
    int y_coeff;
    int constant;
    take_input_solve_lde(x_coeff, y_coeff, constant);

    // Perform extended Euclidean algorithm.
    int_v q;
    int_v r;
    int_v x;
    int_v y;
    auto_eea(q, r, x, y, x_coeff, y_coeff);

    // Solve the Diophantine equation using the output from the extended
    // Euclidean algorithm.
    solve_diophantine(constant, r, x, y);

    return 0;
}


// Prints limitations for solving linear Diophantine equations.
void print_limitations_solve_lde(void) {
    std::cerr << "Limitations:\n";
    
    std::cerr << "- Maximum coefficient and constant should be 10^9.\n\n";
    return;
}


// Reads user input.
void take_input_solve_lde(int &x_coeff, int &y_coeff, int &c) {
    // Inform user how to provide input.
    std::cerr << "Solves equations of the form ax + by = c.\n";
    
    // Read the numerator.
    std::cerr << "Enter coefficient of x: ";
    if (std::cin >> x_coeff) {
        // x coefficient read successfully.
        if (x_coeff > EEA_MAX_INT) {
            std::cerr << RED << "Error: input too large." << RESET << "\n";
            exit(EXIT_FAILURE);
        }
    } else {
        std::cerr << RED << "Error reading x coefficient." << RESET << "\n";
        exit(EXIT_FAILURE);
    }

    // Read the y coefficient.
    std::cerr << "Enter coefficient of y: ";
    if (std::cin >> y_coeff) {
        if (y_coeff > EEA_MAX_INT) {
            std::cerr << RED << "Error: input too large.\n" << RESET;
            exit(EXIT_FAILURE);
        }
    } else {
        std::cerr << RED << "Error reading y coefficient." << RESET << "\n";
        exit(EXIT_FAILURE);
    }
    
    // Read the constant c.
    std::cerr << "Enter value of c: ";
    if (std::cin >> c) {
        if (c > EEA_MAX_INT) {
            std::cerr << RED << "Error: input too large.\n" << RESET;
            exit(EXIT_FAILURE);
        }
    } else {
        std::cerr << RED << "Error reading c." << RESET << "\n";
        exit(EXIT_FAILURE);
    }
}


// Solves the Diophantine equation given the value of c, remainders, x values,
// and y values from performing extended Euclidean algorithm.
void solve_diophantine(int c, int_v r, int_v x, int_v y) {
    // GCD is second last element of remainders.
    int gcd = r[r.size() - 2];

    // Read second to last values of x and y.
    int second_last_x = x[x.size() - 2];
    int second_last_y = y[y.size() - 2];

    // Read last values of x and y. 
    int last_x = abs(x[x.size() - 1]);
    int last_y = abs(y[y.size() - 1]);

    // Error checking - ensure that c divides the gcd of x and y coefficients.
    if (c % gcd != 0) {
        std::cerr << RED << "Error: GCD " << gcd << " does not divide ";
        std::cerr << c << ". There are no solutions." << RESET << "\n\n";
        return;
    }

    // Calculate constant terms in both x and y solutions.
    int x_const = (c / gcd) * second_last_x;
    int y_const = (c / gcd) * second_last_y;

    // Calculate k coefficient for both x and y solutions.
    int xk_coeff = last_x;
    int yk_coeff = last_y;

    // Print solution.
    show_diophantine_soln(x_const, y_const, xk_coeff, yk_coeff);
    return;
}


// Prints solution to Diophantine equation.
void show_diophantine_soln(int x_const, int y_const, int xk, int yk) {
    // Convert k coefficients to absolute values.
    xk = abs(xk);
    yk = abs(yk);

    // Print solution in form of x = x_const + xk * k.
    std::cout << "x = " << x_const << " + " << xk << "k\n";
    std::cout << "y = " << y_const << " - " << yk << "k\n\n";
    return;
}
