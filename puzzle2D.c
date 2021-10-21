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
  Name: puzzle2D.c
  Author: Lukas Waschuk
  OneCard: 1660570
  CCID: lwaschuk
  Instructor: Ildar Akhmetov 
  Lecture Section: B1
  Lab Section: H04
  2021-03-20
  NOTE: FOUND THE RABIN KARP ALGORITHM PSUEDOCODE IN MY CMPUT 204 TEXTBOOK CRLS AND MADE ONLY MINOR CHANGES FOR RETURNS VALUES
*********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LEN 101
#define MAX_N 101
#define P 7079
#define D 256

//prototypes
int horizontal(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size);
int vertical(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size);
int up_right_daigonal(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size);
int up_left_daigonal(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size);
char* reverse(char* str);
int RKA(char pat[], char txt[], int q);
void search_puzzle(char puzzle[][MAX_N], int puzzle_size, char words[][MAX_WORD_LEN], int ans_array[][4], int word_count);

//start of functions
void search_puzzle(char puzzle[][MAX_N], int puzzle_size, char words[][MAX_WORD_LEN], int ans_array[][4], int word_count) {
/*  Purpose: The **MAIN** of this file, will call every searching direction and those funtions will write the answer to ans_array
             1 - hor right 
             2 - hor left 
             3 - vert down 
             4 - vert up
             5 - Top left ----> Bottom right
             6 - bottom right ----> top left
             7 - bottom left ----> top right
             8 - top right ----> bottom left
    Para: Char: puzzle (array)
                words (array)
          Int:  puzzle_size
                ans_array (array)
                word_count
    Returns: None
*/
    for (int i = 0; i < word_count; i++) {
        if (horizontal(puzzle, puzzle_size, words[i], ans_array, word_count, i, puzzle_size) == 1) {
            continue;
        }
        if (vertical(puzzle, puzzle_size, words[i], ans_array, word_count, i, puzzle_size) == 1) {
            continue;
        }
        if (up_right_daigonal(puzzle, puzzle_size, words[i], ans_array, word_count, i, puzzle_size) == 1) {
            continue;
        }
        if (up_left_daigonal(puzzle, puzzle_size, words[i], ans_array, word_count, i, puzzle_size) == 1) {
            continue;
        }
    }
}

int horizontal(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size){
/*  Purpose: Checks all the substrings in the horizontal direction 
    Para:  Char: puzzle (array)
                 word (input string to compare to the puzzle)
           Int:  n = max length of the puzzle
                 ans_array (array)
                 word_count
                 current_word ----> index of the current word in char*word[i]
                 puzzle_size
    Returns: 1: if the given words was matched
             0: if the word was not found
*/
    char line[puzzle_size+1];
    int y_coord, x_coord, direction;
    int string_index;

    for (int i=0; i <= n; i++){
        line[i] = '\0';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            line[j] = puzzle[i][j];
        }

        string_index = RKA(word, line, P);
        y_coord = i;
        x_coord = string_index;
        direction = 1;

        if ((string_index != -100)){
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }
    
        // REVERSE THE STRING AND MAKE DIR 2 
        string_index = RKA(word, reverse(line), P);
        y_coord = i;
        x_coord = (puzzle_size-1) - string_index;
        direction = 2;

        if ((string_index != -100)){
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }
    } return 0;
}

int vertical(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size){
/*  Purpose: Checks all the substrings in the vertical direction 
    Para:  Char: puzzle (array)
                 word (input string to compare to the puzzle)
           Int:  n = max length of the puzzle
                 ans_array (array)
                 word_count
                 current_word ----> index of the current word in char*word[i]
                 puzzle_size
    Returns: 1: if the given words was matched
             0: if the word was not found
*/
    char line[puzzle_size+1];
    int y_coord, x_coord, direction;
    int string_index;

    for (int i=0; i <= n; i++){
        line[i] = '\0';
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++){
            line[i] = puzzle[i][j];
        }
    
        string_index = RKA(word, line, P);
        y_coord = string_index;
        direction = 3;
        x_coord = j;

        if ((string_index != -100)){
            //printf("WENT IN\n");
            //printf("FOUND @ %d\n", y_coord);
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }

        // REVERSE THE STRING AND MAKE DIR 2 
        string_index = RKA(word, reverse(line), P);
        y_coord = (puzzle_size-1)-string_index;
        direction = 4;
        x_coord = j;

        if ((string_index != -100)){
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }
    } return 0;
}


int up_left_daigonal(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size){
/*  Purpose: Checks all the substrings in the bottom right ----> top left and top left ----> bottom right direction 
    Para:  Char: puzzle (array)
                 word (input string to compare to the puzzle)
           Int:  n = max length of the puzzle
                 ans_array (array)
                 word_count
                 current_word ----> index of the current word in char*word[i]
                 puzzle_size
    Returns: 1: if the given words was matched
             0: if the word was not found
*/
    //THIS WILL WORK FOR DOWN RIGHT DIAGONAL TOO AS WE WILL JUST REVERSE STRING 
    int y_coord, x_coord, direction;
    int string_index = 0;
    int i, j, k;
    int count = 0;
    //THIS WILL WORK FOR DOWN RIGHT DIAGONAL TOO AS WE WILL JUST REVERSE STRING 
    char line[puzzle_size+1];

    for (int i=0; i <= n; i++){
        line[i] = '\0';
    }

    //first half up to word len n
    for (k=0; k < n; k++){
        i = n-1-k;
        j = 0;
        
        while (j <= k) {
            line[j] = puzzle[i][j];
            i++;
            j++;
        }
        // every thing above creates the line 
        // to move coordinates back one 
        i--;
        j--;

        // HERE IS WHERE WE WANT HASH TO GO
        string_index = RKA(word, line, P);
        y_coord = string_index + (n-1) - k;
        x_coord = string_index;
        direction = 5;
        
        if ((string_index != -100)){
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }
        
        string_index = RKA(word, reverse(line), P);
        y_coord = i - string_index;
        x_coord = j - string_index;
        direction = 6;

        if ((string_index != -100)){
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }
    }

    for (k = 1; k < n; k++){ // start @ k=1 becuase we did the middle row above
        i = 0;
        j = k;
        count = 0;
        while (j < n) {
            line[count] = puzzle[i][j];
            i++;
            j++;
            count++;
        }
        // reverse the last iteration of the loop
        i--;
        j--;
        
        if (count != n){
            line[count] = '\0'; // to end the string becuase we are starting at len n-1 to len 1.
        }

        string_index = RKA(word, line, P);
        y_coord = string_index;
        x_coord = string_index + k;
        direction = 5;
        
        if ((string_index != -100)){
            //printf("WENT IN\n");
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }

        // REVERSE THE STRING AND MAKE DIR 8
        string_index = RKA(word, reverse(line), P);
        y_coord = i - string_index;
        x_coord = j - string_index;
        direction = 6;

        if ((string_index != -100)){
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }
    } return 0;            
}

int up_right_daigonal(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size){
/*  Purpose: Checks all the substrings in the bottom left ---> top right and top right ----> bottom left direction 
    Para:  Char: puzzle (array)
                 word (input string to compare to the puzzle)
           Int:  n = max length of the puzzle
                 ans_array (array)
                 word_count
                 current_word ----> index of the current word in char*word[i]
                 puzzle_size
    Returns: 1: if the given words was matched
             0: if the word was not found
*/
    //THIS WILL WORK FOR DOWN LEFT DIAGONAL TOO AS WE WILL JUST REVERSE STRING 
    int y_coord, x_coord, direction;
    int string_index;
    char line[puzzle_size+1];
    int i, j, k;
    int count = 0;

    for (int i=0; i <= n; i++){
        line[i] = '\0';
    }
    //printf("LINE char 4 before loop %c\n", line[4]);
    //first half up to word len n
    for (k=0; k < n; k++){
        i = k;
        j = 0;
        
        while (i >= 0) {
            line[j] = puzzle[i][j];
            i--;
            j++;
        }
        // every thing above creates the line 
        // HERE IS WHERE WE WANT HASH TO GO
        string_index = RKA(word, line, P);
        x_coord = string_index;
        y_coord = k - string_index;
        direction = 7;

        if (string_index != -100){
            //printf("FOUND @ %d\n", y_coord);
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }

        // REVERSE THE STRING AND MAKE DIR 8
        string_index = RKA(word, reverse(line), P);
        x_coord = k - string_index;
        y_coord = string_index;
        direction = 8;

        if (string_index != -100){
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }
    }
    
    // from word len n+1 to 1 
    for (k=1; k < n; k++){ // start @ k=1 becuase we did the middle row above
        i = n-1;
        j = k;
        count = 0;
        while (j < n) {
            line[count] = puzzle[i][j];
            i--;
            j++;
            count++;
        }
        if (count != n){
            line[count] = '\0'; // to end the string becuase we are starting at len n-1 to len 1.
        } 
        // undo the last changes inside the above loop
        i++;
        j--;

        // HERE IS WHERE WE WANT HASH TO GO
        string_index = RKA(word, line, P);
        x_coord = k + string_index;
        y_coord = (puzzle_size-1) - string_index;
        direction = 7;

        if (string_index != -100){
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }
        // REVERSE THE STRING AND MAKE DIR 8
        string_index = RKA(word, reverse(line), P);
        x_coord = j - string_index;
        y_coord = i + string_index;
        direction = 8;

        if (string_index != -100){
            ans_array[current_word][0] = 1; 
            ans_array[current_word][1] = direction;
            ans_array[current_word][2] = y_coord;
            ans_array[current_word][3] = x_coord;
            return 1;
        }
    } return 0;
}
 

int RKA(char pat[], char txt[], int q){
/*  Purpose: Rabin Karp algorithm. *NOTE* FOUND THIS CODE IN MY CMPUT 204 TEXTBOOK CRLS. made minor changes for the return values.
    Para: char: pat (the pattern to be looked for)
                txt (the line or string we will be looking in)
          int: q (the prime number we will be using)
    Returns: the index of the txt (string / line) where the matched pattern begins
*/
    int M = strlen(pat); 
    int N = strlen(txt); 
    int i, j; 
    int p = 0; // hash value for pattern 
    int t = 0; // hash value for txt 
    int h = 1; 

    // The value of h would be "pow(d, M-1)%q" 
    for (i = 0; i < M-1; i++) {
        h = (h*D)%q; 
    }
    // Calculate the hash value of pattern and first 
    // window of text 
    for (i = 0; i < M; i++) { 
        p = (D*p + pat[i])%q; 
        t = (D*t + txt[i])%q; 
    } 
    // Slide the pattern over text one by one 
    for (i = 0; i <= N - M; i++) { 
        // Check the hash values of current window of text 
        // and pattern. If the hash values match then only 
        // check for characters on by one 
        if ( p == t ) { 
            /* Check for characters one by one */
            for (j = 0; j < M; j++) { 
                if (txt[i+j] != pat[j]) 
                    break; 
            } 
            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1] 
            if (j == M) {
                return i;
            }
        } 
  
        // Calculate hash value for next window of text: Remove 
        // leading digit, add trailing digit 
        if ( i < N-M ) { 
            t = (D*(t - txt[i]*h) + txt[i+M])%q; 
  
            // We might get negative value of t, converting it 
            // to positive 
            if (t < 0) {
                t = (t + q); 
            } 
        } 
    } return -100;
} 

char* reverse(char* str) {
/*  Purpose: To reverse a string / array of characters.
    Para: char: str: the string that will be reversed 
    Returns: char: the string that was reversed.
*/
    int len = strlen(str);

    int start = 0;
    int end = len - 1;
    char temp;
    while(start <= end){
            temp = str[start];
            str[start] = str[end];
            str[end] = temp;
            start+=1;
            end-=1;
    }
    return str;
}
    