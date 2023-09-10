#!/bin/bash

# Check if the correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <buffer_size> <target_addr>"
    exit 1
fi

# Capture the arguments
buffer_size="$1"
target_address="$2"

# Run the Python script with the provided arguments and capture its output
output=$(python3 createPayload.py "$buffer_size" "$target_address")

# Use echo -e to interpret and print the output
echo -e "$output" > input

