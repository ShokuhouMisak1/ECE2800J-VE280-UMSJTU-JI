#!/bin/bash

# test_call.sh

# Compile call.cpp
g++ -o call call.cpp 
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Initialize test counters
total_tests=0
passed_tests=0

# Function to run a test case
run_test() {
    test_desc="$1"
    input_content="$2"
    expected_output="$3"
    total_tests=$((total_tests + 1))

    echo -n "Running test: $test_desc... "

    # Write input content to a file
    echo "$input_content" > test_input.txt

    # Run the program
    ./call < test_input.txt > actual_output.txt

    # Read actual output
    actual_output=$(cat actual_output.txt)

    # Compare actual output with expected output
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

# Test 1: Simple test (Sample Input)
input1="3
0 Andrew gold 2
0 Chris regular 1
1 Brian silver 1"
expected_output1="Starting tick #0
Call from Andrew a gold member
Call from Chris a regular member
Answering call from Andrew
Starting tick #1
Call from Brian a silver member
Starting tick #2
Answering call from Brian
Starting tick #3
Answering call from Chris
Starting tick #4"

run_test "Simple test" "$input1" "$expected_output1"

# Test 2: Zero callers
input2="0"
expected_output2="Starting tick #0"

run_test "Zero callers" "$input2" "$expected_output2"

# Test 3: Single caller
input3="1
0 Alice platinum 1"
expected_output3="Starting tick #0
Call from Alice a platinum member
Answering call from Alice
Starting tick #1"

run_test "Single caller" "$input3" "$expected_output3"

# Test 4: All callers at same time, different statuses
input4="4
0 Alice platinum 2
0 Bob gold 1
0 Carol silver 3
0 Dave regular 1"
expected_output4="Starting tick #0
Call from Alice a platinum member
Call from Bob a gold member
Call from Carol a silver member
Call from Dave a regular member
Answering call from Alice
Starting tick #1
Starting tick #2
Answering call from Bob
Starting tick #3
Answering call from Carol
Starting tick #4
Starting tick #5
Starting tick #6
Answering call from Dave
Starting tick #7"

run_test "All callers at same time, different statuses" "$input4" "$expected_output4"

# Test 5: All callers at same time, same status
input5="3
0 Alice silver 1
0 Bob silver 1
0 Carol silver 1"
expected_output5="Starting tick #0
Call from Alice a silver member
Call from Bob a silver member
Call from Carol a silver member
Answering call from Alice
Starting tick #1
Answering call from Bob
Starting tick #2
Answering call from Carol
Starting tick #3"

run_test "All callers at same time, same status" "$input5" "$expected_output5"

# Test 6: Callers with long durations
input6="3
0 Alice platinum 5
1 Bob gold 1
2 Carol silver 1"
expected_output6="Starting tick #0
Call from Alice a platinum member
Answering call from Alice
Starting tick #1
Call from Bob a gold member
Starting tick #2
Call from Carol a silver member
Starting tick #3
Starting tick #4
Starting tick #5
Answering call from Bob
Starting tick #6
Answering call from Carol
Starting tick #7"

run_test "Callers with long durations" "$input6" "$expected_output6"

# Test 7: Agent busy with long call, other callers queue
input7="6
0 Agent platinum 10
1 Caller1 regular 1
2 Caller2 regular 1
3 Caller3 regular 1
4 Caller4 regular 1
5 Caller5 regular 1"
expected_output7="Starting tick #0
Call from Agent a platinum member
Answering call from Agent
Starting tick #1
Call from Caller1 a regular member
Starting tick #2
Call from Caller2 a regular member
Starting tick #3
Call from Caller3 a regular member
Starting tick #4
Call from Caller4 a regular member
Starting tick #5
Call from Caller5 a regular member
Starting tick #6
Starting tick #7
Starting tick #8
Starting tick #9
Starting tick #10
Answering call from Caller1
Starting tick #11
Answering call from Caller2
Starting tick #12
Answering call from Caller3
Starting tick #13
Answering call from Caller4
Starting tick #14
Answering call from Caller5
Starting tick #15"

run_test "Agent busy with long call, other callers queue" "$input7" "$expected_output7"

# Test 8: Stress test with many callers
echo -n "Running test: Stress test with many callers... "
total_tests=$((total_tests + 1))
input8=$(echo "100"; for i in $(seq 0 99); do echo "$i Caller$i regular 1"; done)
echo "$input8" > test_input.txt
./call < test_input.txt > actual_output.txt
actual_output_lines=$(wc -l < actual_output.txt)
expected_lines=200 # 100 "Call from" messages and 100 ticks
if [ $actual_output_lines -ge $expected_lines ]; then
    echo "Passed"
    passed_tests=$((passed_tests + 1))
else
    echo "Failed"
    echo "Expected at least $expected_lines lines of output, got $actual_output_lines lines"
fi

# Test 10: Calls arriving after idle period
input10="2
5 Alice silver 1
7 Bob gold 1"
expected_output10="Starting tick #0
Starting tick #1
Starting tick #2
Starting tick #3
Starting tick #4
Starting tick #5
Call from Alice a silver member
Answering call from Alice
Starting tick #6
Starting tick #7
Call from Bob a gold member
Answering call from Bob
Starting tick #8"

run_test "Calls arriving after idle period" "$input10" "$expected_output10"

# Test 11: Call with long duration
input11="1
0 Alice platinum 1000"
expected_output11="Starting tick #0
Call from Alice a platinum member
Answering call from Alice"
for ((i=1; i<=1000; i++)); do
    expected_output11+="
Starting tick #$i"
done

run_test "Call with long duration" "$input11" "$expected_output11"

# Summary
echo "Passed $passed_tests out of $total_tests tests."