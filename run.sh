#!/bin/bash
# Command to compile c++ program. Here I used a common one
g++ main.cpp -o main
# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the compiled binary
    ./main
    exit 0
else
    # Print an error message if compilation failed
    echo "Compilation failed"
fi
exit 0