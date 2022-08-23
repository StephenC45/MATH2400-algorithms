# About This Repository
The code in this repository is a command-line tool that implements various mathematical algorithms and can help check your answers to problems from the MATH2400 (Finite Mathematics) course at UNSW.

**Current algorithms include:**
- Euclidean algorithm
- Extended Euclidean algorithm
- Integer base conversion (up to and including base-36)
- Decimal fraction base conversion (from decimal to another base)
- Converting simple fractions into continued fractions
- Showing continued fraction convergents of a simple fraction
- Linear Diophantine equation solver
- Chinese remainder theorem for simultaneous linear congruences of the form x = k (mod m)
- Sieve of Eratosthenes

**Coming soon:**
- N/A

# Instructions (Linux)
1. Clone this repository.
2. Change into the repository.
3. If you want to use the older version of decimal fraction base conversion, you need to edit the Makefile and replace ```base_conversion.cpp``` in ```SUPPORTING_FILES``` with ```old_base_conversion.cpp```.
4. Save the Makefile if you edited it in the previous step.
5. Compile all files by typing ```make```.
6. Run the program using ```./2400``` and enjoy.
7. If you want to run the benchmark instead, use ```./benchmark```.

# Instructions (Windows, No C++ Compiler Installed)
1. If you haven't already, install a C++ compiler (this guide uses TDM-GCC) here: https://jmeubank.github.io/tdm-gcc/
2. Clone this repository.
3. Open PowerShell and change into the repository.
4. Compile all files using one of the compilation commands below.
5. Run the program using ```./2400.exe```
7. If you want to run the benchmark instead, use ```./benchmark.exe```.

Compilation command for using ```base_conversion.cpp```:

```g++ -Wall -Wextra -Wshadow -pedantic-errors -std=c++17 -O3 debug.cpp euclidean.cpp base_conversion.cpp crt.cpp continued_fractions.cpp linear_diophantine.cpp sieve.cpp 2400.cpp -o 2400.exe```

Compilation command for using ```old_base_conversion.cpp```:

```g++ -Wall -Wextra -Wshadow -pedantic-errors -std=c++17 -O3 debug.cpp euclidean.cpp old_base_conversion.cpp crt.cpp continued_fractions.cpp linear_diophantine.cpp sieve.cpp 2400.cpp -o 2400.exe```

Benchmark compilation command: ```g++ -Wall -Wextra -Wshadow -pedantic-errors -std=c++17 -O3 debug.cpp euclidean.cpp base_conversion.cpp crt.cpp continued_fractions.cpp linear_diophantine.cpp sieve.cpp benchmark.cpp -o benchmark```


# Feedback
Report bugs, suggest features, and give feedback using this link: https://forms.gle/DpoX1eTry7V9yewV7
