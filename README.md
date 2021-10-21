# ASSIGNMENT 2
## The Information of the Creator:

***ASSIGNMENT 2***                                                           
  **Author:** Lukas Waschuk    
  **CCID:** lwaschuk   
  **Date:** 03-20-2021                               

### The Purpose of Your Program:
This program was created to help solve a NxN word search within the blink of a eye (under 0.3 seconds at most). This program will search all 8 possible directions and output a text file (or print into an existing file of the users choice) containing the locations and directions of all the words. 

### The Exact Commands We Need to Run Your Code:
The program was written in C and is optimally compiled using GNU compiler (GCC). The program is ran by simply typing make in the command line while will create all the required files and it will create an executable called wordSearch2D. To run the executable type:  


           <./wordSearch2D -p *puzzle_file* -l word_length -w wordlist_file [-o solution_file]>   



into the command line. You will need to supply a NxN puzzle file, a word list containing all the words you seek. All the words must be the same length and must not exceed the length of the puzzle file you entered. For the final flag <-l> you must specify the length of the words you are attempting to search. Assuming you met all the above specifications the output file will be created as "output.txt" or it can be given a name using the -o flag.

### The Structure of the Solution File:
The solution file will contain a list of locations along with the directions of the input word list, in the same order they were entered.   
Format:    
**x-coordinate** = *columns*  
**y-coordinate** = *rows* 

    word;(y,x);direction 

### The Files Submitted In Your Assignment, How They Are Structured, And What They Do:
The files uploaded are:  
**wordSearch2D.c**  is the main program which will extract all the information from the input text files, error check them, and save the output to the text file.    
**puzzle2D.c** is the logic behind solving the puzzle by travering every direction and comparing substrings of a line using the Rabin-Karp string comparison algorithm.    
**puzzle2D.h** is the header file to link the functions of *puzzle2D.c* into *wordSearch2D.c.*   
**Makefile** is the file that links and compiles the program and headers together, by typing **make** in the command line.   
**puzzle.txt** is a puzzle text file to sample the program.    
**wordlist.txt** is a wordlist file to use with the above puzzle to sample the program.    
**expected_soln.txt** is the solution that the program will give.    
**sample_test.sh** is the script that can be used to run the program after is it compiled.  

### References (e.g., any online resources you used in accordance to the course policy):
My references come from CMPUT 201 lecture slides, the textbook C PROGRAMMING by K N KING, and my Kabin-Karp Algorithm was sourced and heavily referenced from the CMPUT 204 textbook **CRLS: Introduction to Algorithms.**
