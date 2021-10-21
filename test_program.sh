#!/bin/bash

readonly ERROR="\e[31;1mERROR:\x1b[0m"
readonly SUCCESS="\e[92mTest passed!\x1b[0m"

readonly ERROR_USAGE_MSG="Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]"



# First, check that there are no warnings or errors (although you should run check_general_requirements.sh before this
make clean
output="$(make -B 2>&1)"
make_result=$?

if grep "warning:" <<<"${output}"; then
    echo -e $ERROR "Your program compiles with warnings. Please fix before trying to run this script."
    exit 2
fi

if [ $make_result -ne 0 ]
then
    echo -e $ERROR "make failed. Your program has compilation errors. Please fix before trying to run this script"
    exit 2
fi

# Check that executable exists and is executable
if [ ! -x wordSearch2D ]
then
    echo -e $ERROR "wordSearch2D could not be found or is not executable (maybe check the name of the executable in your Makefile)"
    exit 1
fi

# Testing wrong arguments
echo -e "Testing wrong arguments..."
output=$(./wordSearch2D -o puzzle.txt 2>&1 > /dev/null)
return_val=$?
# Check that return value of above argument is indeed 6
if [ $return_val -ne 6 ]
then
    echo -e $ERROR "Expected return value of 6 but received $return_val"
    exit 2
fi
# Verify correct error message
diff -Z -b -B -q <(echo $ERROR_USAGE_MSG) <(echo $output) > /dev/null
diff_exit=$?
if [ $diff_exit -ne 0 ]
then
    echo -e $ERROR "Incorrect error message"
    echo "Program output:"
    echo $output
    exit 2
fi
if [ $return_val -eq 6 ] && [ $diff_exit -eq 0 ]
then
    echo -e $SUCCESS
fi

echo ""

# Test student test case
echo "Testing your own test case..."
if [ ! -f puzzle.txt ] || [ ! -f wordlist.txt ] || \
    [ ! -f expected_soln.txt ] || [ ! -f sample_test.sh ]
then
    echo -e $ERROR "Files needed for student-provided test case missing"
    exit 2
else
    ./sample_test.sh
    diff -Z -q output.txt expected_soln.txt
    if [ $? -ne 0 ]
    then
        echo -e $ERROR "Test failed.  The output of your program is different that the expected output you provide"
        exit 2
    else
        echo -e $SUCCESS
    fi
fi


echo ""

# Sample test cases 1
echo "Sample test case 1"

echo "Running as... ./wordSearch2D -p SampleTests/student_1_table.txt -l 4 -w SampleTests/student_1_wordlist.txt -o output1.txt"
./wordSearch2D -p SampleTests/student_1_table.txt -l 4 -w SampleTests/student_1_wordlist.txt -o output1.txt
diff -Z -q output1.txt SampleTests/student_1_sols.txt
if [ $? -ne 0 ]
then
    echo -e $ERROR "test failed"
    exit 2
else
    echo -e $SUCCESS
fi

echo ""

# Sample test case 2
echo "Sample test case 2"

echo "Running as... ./wordSearch2D -p SampleTests/student_2_table.txt -l 6 -w SampleTests/student_2_wordlist.txt -o output2.txt"
./wordSearch2D -p SampleTests/student_2_table.txt -l 6 -w SampleTests/student_2_wordlist.txt -o output2.txt
diff -Z -q output2.txt SampleTests/student_2_sols.txt
if [ $? -ne 0 ]
then
    echo -e $ERROR "test failed"
    exit 2
else
    echo -e $SUCCESS
fi

echo ""
