# Compiles to produce an executable, 2400, that helps with checking your answers
# to some types of MATH2400 problems.

#------------------------------------------------------------------------------#

# Compile settings, with some optimisation for speed.
# If you want to modify the code, it's best to change these to the following:
# - WARN_FLAGS: the same as below, add any extra flags you want to use.
# - OTHER_FLAGS: remove -O3, add -g and any other flags you want to use.

CPP=g++
WARN_FLAGS=-Wall -Wextra -Wshadow
OTHER_FLAGS=-pedantic-errors -std=c++17 -O3
SUPPORTING_FILES=debug.cpp euclidean.cpp base_conversion.cpp crt.cpp continued_fractions.cpp linear_diophantine.cpp

#------------------------------------------------------------------------------#

all: Makefile 2400.cpp $(SUPPORTING_FILES)
	$(CPP) $(WARN_FLAGS) $(OTHER_FLAGS) $(SUPPORTING_FILES) 2400.cpp -o 2400
