#!/bin/bash

# Compile the C++ program
g++ -o 	main main.cpp -lncurses

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Running TODO-CLI..."
    # Run the compiled program
    ./main
else
    echo "Compilation failed. Please check your code."
fi

