#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void arg_len_check(int argc, int *include_solution); 
void puzzle_file_valid(FILE *filename, char *argv[], int *location);
void wordlist_file_valid(FILE *filename, char *argv[], int *location);
void word_length_valid(char **argv, int *location);
void assign_flags(int *puzzle_file_location, int *word_length_location, int *wordlist_file_location, \
                  int *solution_file_location, int *arg_check, int *include_solution, int argc, char **argv);

int main(int argc, char **argv) {
    int puzzle_file_location = 0, word_length_location = 0, wordlist_file_location = 0, solution_file_location = 0;
    int arg_check = 0, include_solution = 0;

    int *puzzle_file_location_pointer = &puzzle_file_location, *word_length_location_pointer = &word_length_location;
    int *wordlist_file_location_pointer = &wordlist_file_location, *solution_file_location_pointer = &solution_file_location;
    int *arg_check_pointer = &arg_check, *include_solution_pointer = &include_solution;

    /*
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
        }
    }
    */
   assign_flags(puzzle_file_location_pointer, word_length_location_pointer, wordlist_file_location_pointer, \
                     solution_file_location_pointer, arg_check_pointer, include_solution_pointer, argc, argv);

    arg_len_check(argc, include_solution_pointer);
    
    // opening the puzzle text file 
    FILE *puzzle_file = fopen(argv[*puzzle_file_location_pointer], "r");
    puzzle_file_valid(puzzle_file, argv, puzzle_file_location_pointer);

    // opening the wordlist text file 
    FILE *wordlist_file = fopen(argv[*wordlist_file_location_pointer], "r");
    wordlist_file_valid(wordlist_file, argv, wordlist_file_location_pointer);

    //checking validity of the word length argument
    word_length_valid(argv, word_length_location_pointer);








    // DEBUG 
    printf("PUZZLE FILE IS: %d\n", *puzzle_file_location_pointer);
    printf("word length is: %d\n", *word_length_location_pointer);
    printf("worldlist file is: %d\n", *wordlist_file_location_pointer);
    
    printf("INCLUDE SOLUTION: %d\n", *include_solution_pointer);
    printf("ARGCHECK: %d\n", *arg_check_pointer);
    printf("ARGC: %d\n", argc);


    printf("PUZZLE FILE IS: %s\n", argv[*puzzle_file_location_pointer]);
    printf("word length is: %s\n", argv[*word_length_location_pointer]);
    printf("worldlist file is: %s\n", argv[*wordlist_file_location_pointer]);

    if (*include_solution_pointer == 1) {
        printf("solution FILE IS: %d\n", *solution_file_location_pointer);
        printf("solution FILE IS: %s\n", argv[*solution_file_location_pointer]);
    }
    
    return 0;
}

void arg_len_check(int argc, int *include_solution){
/*  Purpose: To check if the command line inputs are equal to 7, or 9 if the user wants a solution file 
    Para: Integer: argc, include solution 
    Returns: None, it will exit using error code 7 if there are not 7 arguments.
*/
    if (*include_solution == 0){
        if (argc != 7) {
            fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
            exit(6);
        } 
    }
    else {
        if (argc != 9) {
            fprintf(stderr, "Usage: ./wordSearch2D -p <puzzle_file> -l <word_length> -w <wordlist_file> [-o <solution_file>]\n");
            exit(6);
        }
    } return;
}

void puzzle_file_valid(FILE *filename, char *argv[], int *location){
/*  Purpose: To check if a file (.csv or .txt) exists and can be opened
    Para: FILE: the filename to be opened (checking if it equals NULL)
          char: argv[], from command line 
          int: location, where in argv[] the file is located (i.e argv[location])
    
    Returns: None, will exit on code 3 if the file cannot be opened
*/ 
    if(filename == NULL) {
        fprintf(stderr, "Error: Puzzle file %s does not exist\n", argv[*location]);
        exit(4); 
    } return;
}

void wordlist_file_valid(FILE *filename, char *argv[], int *location){
/*  Purpose: To check if a file (.csv or .txt) exists and can be opened
    Para: FILE: the filename to be opened (checking if it equals NULL)
          char: argv[], from command line 
          int: location, where in argv[] the file is located (i.e argv[location])
    
    Returns: None, will exit on code 3 if the file cannot be opened
*/ 
    if(filename == NULL) {
        fprintf(stderr, "Error: Wordlist file %s does not exist\n", argv[*location]);
        exit(5); 
    } return;
}

void word_length_valid(char **argv, int *location) {
    int length = 0; 
    length = atoi(argv[*location]);
    fprintf(stderr, "len = %d\n", length);
    if (length < 1){
        fprintf(stderr, "Encountered error\n");
        exit(7);
    } return;
}


void assign_flags(int *puzzle_file_location, int *word_length_location, int *wordlist_file_location, \
                  int *solution_file_location, int *arg_check, int *include_solution, int argc, char **argv){
    
    for (int i=0; i < argc; i++) {
        if ((strcmp(argv[i], "-p")) == 0) { // output of strcmp will be 0 if they match
            *puzzle_file_location = i+1;
            *arg_check = *arg_check + 1;
        } else if ((strcmp(argv[i], "-l")) == 0) {
            *word_length_location = i+1;
            *arg_check = *arg_check + 1;
        } else if ((strcmp(argv[i], "-w")) == 0) {
            *wordlist_file_location = i+1;
            *arg_check = *arg_check + 1;
        } else if ((strcmp(argv[i], "-o")) == 0) {
            *solution_file_location = i+1;
            *include_solution = 1;
        }
    }


    return;
}