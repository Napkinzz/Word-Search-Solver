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
  Name: puzzle2D.h
  Author: Lukas Waschuk
  OneCard: 1660570
  CCID: lwaschuk
  Instructor: Ildar Akhmetov 
  Lecture Section: B1
  Lab Section: H04
  2021-03-19
*********************************/
#define MAX_WORD_LEN 101
#define MIN_ASCII 32
#define MAX_ASCII 126
#define MAX_N 101
#define P 7079
#define D 256

#ifndef PUZZLE2D
#define PUZZLE2D
int horizontal(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size);
int vertical(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size);
int up_right_daigonal(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size);
int up_left_daigonal(char puzzle[][MAX_N], int n, char *word, int ans_array[][4], int word_count, int current_word, int puzzle_size);
char* reverse(char* str);
int RKA(char pat[], char txt[], int q);
void search_puzzle(char puzzle[][MAX_N], int puzzle_size, char words[][MAX_WORD_LEN], int ans_array[][4], int word_count);
#endif