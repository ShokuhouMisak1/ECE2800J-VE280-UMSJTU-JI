#!/bin/bash

# test_calc.sh

# Compile calc.cpp
g++ -o calc calc.cpp 2> compile_errors.txt
if [ $? -ne 0 ]; then
    echo "Compilation failed:"
    cat compile_errors.txt
    exit 1
fi

# Initialize test counters
total_tests=0
passed_tests=0

# Function to run a test case
run_test() {
    test_desc="$1"
    input="$2"
    expected_output="$3"
    total_tests=$((total_tests + 1))

    echo -n "Running test: $test_desc... "

    # Run calc with the input
    actual_output=$(echo -e "$input" | ./calc)

    # Compare the actual output with expected output
    if [ "$actual_output" == "$expected_output" ]; then
        echo "Passed"
        passed_tests=$((passed_tests + 1))
    else
        echo "Failed"
        echo "Expected output:"
        echo "$expected_output"
        echo "Actual output:"
        echo "$actual_output"
    fi
}

# Test cases

# Addition test
run_test "Addition" "2 3 + p q" "5"

# Subtraction test
run_test "Subtraction" "5 2 - p q" "3"

# Multiplication test
run_test "Multiplication" "4 5 * p q" "20"

# Division test
run_test "Division" "10 2 / p q" "5"

# Division by zero test
run_test "Division by zero" "5 0 / q" "Divide by zero"

# Negate test
run_test "Negate" "5 n p q" "-5"

# Duplicate test
run_test "Duplicate" "8 d p q" "8"

# Reverse test
run_test "Reverse" "1 2 r p q" "1"

# Print all test
run_test "Print all" "3 4 5 a q" "5 4 3"

# Clear test
run_test "Clear" "7 8 c a q" ""

# Invalid input test
run_test "Invalid input" "abc q" "Bad input"

# Not enough operands test
run_test "Not enough operands" "+ q" "Not enough operands"

# Negative numbers test
run_test "Negative numbers" "-2 -3 + p q" "-5"

# Edge case: zero division with zero numerator and denominator
run_test "Zero division numerator zero" "0 5 / p q" "0"
run_test "Zero division denominator zero" "5 0 / q" "Divide by zero"

# Large number test
run_test "Large numbers" "2147483646 1 + p q" "2147483647"

# Leave stack unchanged when not enough operands
run_test "Leave stack unchanged when not enough operands" "1 + p q" "Not enough operands"$'\n'"1"
run_test "Leave stack unchanged when not enough operands" "0 * p q" "Not enough operands"$'\n'"0"
run_test "Leave stack unchanged when not enough operands" "114 / p q" "Not enough operands"$'\n'"114"
run_test "Leave stack unchanged when not enough operands" "514 - p q" "Not enough operands"$'\n'"514"

# Stress test
long_input=""
for i in $(seq 0 999); do
    long_input="$long_input$i "
done
long_input="$long_input a q"
expected_output=""
for i in $(seq 999 -1 0); do
    expected_output="$expected_output$i"
    if [ $i -ne 0 ]; then
        expected_output="$expected_output "
    fi
done
run_test "Stress test" "$long_input" "$expected_output"

# Summary
echo "Passed $passed_tests out of $total_tests tests."