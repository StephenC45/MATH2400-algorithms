# Compiles all .c and .cpp files in the current directory.
# Does not work with programs that use multiple files.

# Adapted from the Makefiles used by various Stack Overflow users.

#------------------------------------------------------------------------------#

# Executables from C files have no file extension.
C=gcc
CWARNFLAGS=-x c -Wall -Wextra -Wshadow
COTHERFLAGS=-pedantic-errors -g
CBIN=$(patsubst %.c, %, $(wildcard *.c))

# Executables from C++ files have no file extension.
CPP=g++
CPPWARNFLAGS=-x c++ -Wall -Wextra -Weffc++ -Wshadow
CPPOTHERFLAGS=-pedantic-errors -std=c++17 -g
CPPBIN=$(patsubst %.cpp, %, $(wildcard *.cpp))

#------------------------------------------------------------------------------#

all: $(CPPBIN) $(CBIN)

# C++
%: %.cpp Makefile
	$(CPP) $(CPPWARNFLAGS) $(CPPOTHERFLAGS) $< -o $@

# C
%: %.c Makefile
	$(C) $(CWARNFLAGS) $(COTHERFLAGS) $< -o $@ -lm
