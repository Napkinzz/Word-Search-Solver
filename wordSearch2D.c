/*CMPUT 201 Student Submission License Version 2.0

Copyright 2021 Lukas Waschuk

Unauthorized redistribution is forbidden under all circumstances. Use of this software without explicit authorization from the 
author and the CMPUT 201 Instructor is prohibited.

This software was produced as a solution for an assignment or lab in the course CMPUT 201 - Practical Programming Methodology 
at the University of Alberta, Canada. This solution is confidential and remains confidential after it is submitted for grading. 
The course staff has the right to run plagiarism-detection tools on any code developed under this license, even beyond the 
duration of the course.

Copying any part of this solution without including this copyright notice is illegal.

If any portion of this software is included in a solution submitted for grading at an educational institution, the submitter will 
be subject to the plagiarism sanctions at that institution.

This software cannot be publicly posted under any circumstances, whether by the original student or by a third party. If this 
software is found in any public website or public repository, the person finding it is kindly requested to immediately report, 
including the URL or other repository locating information, to the following email addresses:

//nadi@ualberta.ca
//ildar@ualberta.ca
*/
/*********************************
  Name: wordSearch2D.c
  Author: Lukas Waschuk
  OneCard: 1660570
  CCID: lwaschuk
  Instructor: Ildar Akhmetov 
  Lecture Section: B1
  Lab Section: H04
  2021-03-19
*********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzle2D.h"
#define MAX_WORD_LEN 101
#define MAX_N 101

void arg_len_check(int argc, int include_solution, int arg_check){
/*  Purpose: To check if the command line inputs are equal to 7, or 9 if the user wants a solution file 
    Para: Integer: argc, include solution 
    Returns: None, it will exit using error code 7 if there are not 7 arguments.
*/
    if (include_solution == 0){
        if ((argc != 7) || (arg_check != 3)){
            fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
            exit(6);
        } 
    }
    else {
        if ((argc != 9) || (arg_check != 4)) {
            fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
            exit(6);
        }
    } return;
}

void puzzle_file_valid(FILE *filename, char *argv[], int location){
/*  Purpose: To check if a file (.csv or .txt) exists and can be opened
    Para: FILE: the filename to be opened (checking if it equals NULL)
          char: argv[], from command line 
          int: location, where in argv[] the file is located (i.e argv[location])
    
    Returns: None, will exit on code 3 if the file cannot be opened
*/ 
    if(filename == NULL) {
        fprintf(stderr, "Error: Puzzle file %s does not exist\n", argv[location]);
        exit(4); 
    } return;
}

void wordlist_file_valid(FILE *filename, char *argv[], int location){
/*  Purpose: To check if a file (.csv or .txt) exists and can be opened
    Para: FILE: the filename to be opened (checking if it equals NULL)
          char: argv[], from command line 
          int: location, where in argv[] the file is located (i.e argv[location])
    
    Returns: None, will exit on code 3 if the file cannot be opened
*/  
    
    if(filename == NULL) {
        fprintf(stderr, "Error: Wordlist file %s does not exist\n", argv[location]);
        exit(5); 
    } return;
}

int number_of_words(FILE *filename) {
/*  Purpose: To count the number of words in the input file so we can allotcate memory and make a array to store them.
             rewinds the FP after.
    Para: FILE*: Filename 
    Returns: int: word_count
*/
    char word[MAX_WORD_LEN];
    int word_count = 0;
    while (fgets(word, MAX_WORD_LEN, filename) != NULL){
        word_count++;
    } rewind(filename); // put back at the top of the file
    return word_count;
}

int word_length_valid(char **argv, int location, int puzzle_size) {
/*  Purpose: To make sure that the words inside the word array are atleast 1 and at most the size of the horizonal on the puzzle.
    Para: char**: argv
          int: location
               puzzle_size
    Returns: int: length of the words
*/
    int length = 0; 
    length = atoi(argv[location]);
    if ((length < 1) || (length > puzzle_size)){
        fprintf(stderr, "Encountered error\n");
        exit(7);
    } return length;
}

void validate_wordlist(char words[][MAX_WORD_LEN], int word_count, int word_len) {
/*  Purpose: Check ascii codes, and make sire every newline is cahnged to null here
    Para: char: words
          int: word_count
               word_len
    Returns: NULL
*/
    // goes through every letter of every words to make sure they are acceptable 
    for (int i = 0; i < word_count; i++){
        for (int j = 0; j < word_len; j++){
            if (words[i][j] == 10){ // changing the new line character to NULL 
                words[i][j] = 0;
            }
            else if ((words[i][j] == 0)) { // skip if its a NULL
                continue;
            }
            else if (((words[i][j] <= 32) || (words[i][j] >= 126))){
                fprintf(stderr, "Encountered Error\n");
                exit(7);
            }
        }
    }return;
}

void populate_word_array(FILE *wordlist_file, char words[][MAX_WORD_LEN], int word_count, int word_len) {
/*  Purpose: Add all the words from the text file into a array while checking their lengths that was specified in the cmd line
    Para: FILE*: wordlist_file
          char: words
          int: Word_count
               world_len
    Returns: NULL
*/
    for (int i = 0; i < word_count; i++) {
        fgets(words[i], MAX_WORD_LEN, wordlist_file);
        if (i < word_count -1){ // if the current string is not the last index of i
            if (strlen(words[i]) != word_len ) { // to account for the \n
                fprintf(stderr, "Encountered Error\n");
                exit(7);
            }
        } 
        else { // if it is the last index it will not have the \n character 
            if ((i == word_count-1) && (words[i][word_len-1] != 10)){
                if (strlen(words[i]) != word_len-1) {
                    fprintf(stderr, "Encountered Error\n");
                    exit(7);
                }
            }  
        }
    } return;
}


void populate_puzzle_array(FILE *puzzle_file, char puzzle[][MAX_N], int n){
/*  Purpose: To put everything from the puzzle text file into a array
    Para: FILE*: puzzle_file
          char: puzzle (array)
          int: n (size of array)
    Returns: NULL
*/
    for (int i = 0; i <= n; i++){
        fgets(puzzle[i], MAX_WORD_LEN+1, puzzle_file);
    }rewind(puzzle_file);
    return;
}

int get_puzzle_len(FILE *puzzle_file) {
/*  Purpose: To get the NxN size of the puzzle, takes the len of the first line since we know it is NxN
    Para: FILE*: puzzle_file
    Returns: int: len
*/
    char string[MAX_WORD_LEN];
    int len;

    fgets(string, MAX_WORD_LEN+1, puzzle_file);
    len = strlen(string);
    rewind(puzzle_file);
    return len;
}



int main(int argc, char **argv) {
/*  Purpose: Main function to set up all the arrays and do the error checking, calls a function from puzzle2D.c and then prints the 
             solution to either output.txt or a file name specified in the cmd line.
*/
    int word_count;
    int word_len;

    // checking and assigning arguments from the command line 
    int puzzle_file_location, word_length_location, wordlist_file_location, solution_file_location;
    int arg_check = 0, include_solution = 0; // counter used to make sure we have the exact 3 flags input.
    for (int i=0; i < argc; i++) {
        if ((strcmp(argv[i], "-p")) == 0) { // output of strcmp will be 0 if they match
            puzzle_file_location = i+1;
            arg_check++;
        } else if ((strcmp(argv[i], "-l")) == 0) {
            word_length_location = i+1;
            arg_check++;
        } else if ((strcmp(argv[i], "-w")) == 0) {
            wordlist_file_location = i+1;
            arg_check++;
        } else if ((strcmp(argv[i], "-o")) == 0) {
            solution_file_location = i+1;
            include_solution++;
            arg_check++;
        }
    }

    arg_len_check(argc, include_solution, arg_check);
    
    // opening the puzzle text file 
    FILE *puzzle_file = fopen(argv[puzzle_file_location], "r");
    puzzle_file_valid(puzzle_file, argv, puzzle_file_location);

    // opening the wordlist text file 
    FILE *wordlist_file = fopen(argv[wordlist_file_location], "r");
    wordlist_file_valid(wordlist_file, argv, wordlist_file_location);

    // get puzzle size 
    int puzzle_size;
    puzzle_size = get_puzzle_len(puzzle_file)-1; // -1 to account for the NULL / NEWLINE 

    //checking validity of the word length argument
    word_len = word_length_valid(argv, word_length_location, puzzle_size) + 1; 
    word_count = number_of_words(wordlist_file); // counts the number of words in the word list file 
    int ans_array[word_count][4];

    // create the word array, populate it and validate it.
    char words[word_count][MAX_WORD_LEN];
    populate_word_array(wordlist_file, words, word_count, word_len);
    validate_wordlist(words, word_count, word_len); // will exit if there is a problem 
    
    // populate the puzzle array so we can make substrings in every direction 
    char puzzle[MAX_N][MAX_N];
    populate_puzzle_array(puzzle_file, puzzle, puzzle_size); // creates the 2D PUZZLE from the file 
    search_puzzle(puzzle, puzzle_size, words, ans_array, word_count); // puts information in ans_array

    // writing the solutions to a text file
    if (include_solution == 1){ // if the -o was entered 
        FILE *fp = fopen(argv[solution_file_location], "w");
        for (int i = 0; i < word_count; i++) {
        if (ans_array[i][0] == 1){
            fprintf(fp, "%s;(%d,%d);%d\n", words[i], ans_array[i][2], ans_array[i][3], ans_array[i][1]);
        } else{
            ans_array[i][0] = 0; 
            ans_array[i][1] = 0;
            ans_array[i][2] = 0;
            ans_array[i][3] = 0;
            fprintf(fp, "%s;(%d,%d);%d\n", words[i], ans_array[i][2], ans_array[i][3], ans_array[i][1]);
            }
        }
    } else { // if -o was not entered
        FILE *fp = fopen("output.txt", "w");
        for (int i = 0; i < word_count; i++) {
        if (ans_array[i][0] == 1){
            fprintf(fp, "%s;(%d,%d);%d\n", words[i], ans_array[i][2], ans_array[i][3], ans_array[i][1]);
        } else{
            ans_array[i][0] = 0; 
            ans_array[i][1] = 0;
            ans_array[i][2] = 0;
            ans_array[i][3] = 0;
            fprintf(fp, "%s;(%d,%d);%d\n", words[i], ans_array[i][2], ans_array[i][3], ans_array[i][1]);
            }
        }
    }
    return 0;
}
