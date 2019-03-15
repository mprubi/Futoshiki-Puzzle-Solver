/* Program 2 -- Futoshiki puzzle
 * Usage: Futoshiki puzzle
 * This program
 *
 * Mark Rubianes
 * ECE 209 001
 * 02/22/2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int solve(int puzzle[], const int constraints[], int size);
int readPuzzle(const char *name, int **puzzle, int **constraints, int *size);
void printPuzzle(const int puzzle[], const int constraints[], int size);
int isLegal(int row, int col, int num, const int puzzle[], const int constraints[], int size);
int filterAsciiChar(char asciiChar);
char retConstraintChars(const int constraints[], int lineNumber);

#ifndef NOMAIN   /* ignore: this is to remove the main function for testing purposes */

int main() {
    char filename[20];
    int *puzzle;       /* array for puzzle numbers */
    int *constraints;  /* array for puzzle constraints */
    int size;          /* size of puzzle */
    int i = 0;
    int j = 0;


    printf("Puzzle file: ");
    fflush(stdout);
    scanf("%20s", filename);

    if (!readPuzzle(filename, &puzzle, &constraints, &size)) {
        printf("Unable to open puzzle file: %s\n", filename);
        return 1;
    }
    printf("PUZZLE:\n");

    //this block is my extra debugging code to see what is in th array
    {
        for(i = 0; i < (size)*(size); i++){
            printf("%d ", puzzle[i]);
        }

        printf("\n\n");

        for(j = 0; j < (size)*(size); j++){
            if(constraints[j]){
                printf("%c ", retConstraintChars(&constraints[j], 0));
            }
            else{
                printf("%d ", constraints[j]);
            }

        }
        printf("\n\n");
    }


    printPuzzle(puzzle, constraints, size);

    printf("\nSOLUTION:\n");
    if (solve(puzzle, constraints, size)) {
        printPuzzle(puzzle, constraints, size);
    }
    else {
        printf("No solution exists.\n");
    }
    return EXIT_SUCCESS;
}

#endif  /* ignore */


/* function header comment goes here */
int readPuzzle(const char *name, int **puzzle, int **constraints, int *size) {
    char tempbuff;
    int check;
    int lineNumber = 2;
    bool breakKforloop = false;
    bool conditionFlag = false;
    int i = 0;
    int k = 0; //indexes for referencing puzzle and constraint arrays
    int *p;  //declare my pointers to arrays
    int *c;

    FILE* in;
    in = fopen(name, "r");

    if (in == NULL){
        //printf("\nMY error: file did not open successfully");
        return 0;
    }

    fscanf(in, "%d", &*size);  //read first decimal digit from file into the variable 'size'


    c = (int*) malloc((*size)*(*size)*sizeof(int));  //re-size c array according to first digit read from file (for my use to manipulated the array within this function)
    p = (int*) malloc((*size)*(*size)*sizeof(int)); //re-size p array according to first digit read from file (for my use to manipulated the array within this function)
    *puzzle = p;   //these pointers are just for main to see the same array I'm manipulating
    *constraints = c;  //these pointers are just for main to see the same array I'm manipulating

    //initialize all elements of both arrays to zeroes
    for(i = 0; i < ((*size)*(*size)); i++){
        p[i] = 0;
        c[i] = 0;
    }

    for (i = 0; i < ((*size)*(*size)); i++) {   //from i = 0 to size squared (very element of the puzzle and constraint arrays
        for (k = 0; k < 2; k++) {           //iterate every two spaces (this groups every two characters together within the bars of each line)
            do {                            //do while loop keeps scanning until we get to the first desired character of the row
                fscanf(in, "%c", &tempbuff);
                check = filterAsciiChar(tempbuff);
                if(tempbuff == 'v' || tempbuff == '^' || tempbuff == '<' || tempbuff == '>')
                    conditionFlag = !conditionFlag;
                if((lineNumber%2 == 0) && (i%2 != 0) && (check == -3)){ // -3 is BAR
                    //if we're on the last index of i on row for the puzzle values, and the character is a BAR, then break the k for loop so i increments to the next element
                    if(i == ((*size)*(*size)-1)) break;
                    i = i-(*size);  //reset i to use index 0-3 a second time for the constraint row
                    lineNumber++; //increment lineNumber to know what row of the text file I'm on
                    break;
                }
                if (lineNumber%2 != 0 && (i%2 != 0) && (check == -3)){  // -3 is BAR
                    //if we're on the last index of i on the constraints row (every odd line in the file), and the character is a BAR, then break the k for loop so i increments to the next element
                    breakKforloop = !breakKforloop;
                    lineNumber++; //increment lineNumber to know what row of the text file I'm on
                    break;
                }
            } while (check == -1 || check == -3);    //keep scanning until we get to first bar of each row
            if (breakKforloop){
                breakKforloop = !breakKforloop;
                break;
            }
            if (check >= 0 && check <= 9 && !(conditionFlag)) {
                p[i] = check;  //store character in ith index of array
            }
            if ((check == 1 || check == 2) && (conditionFlag)){  //if < or > and conditionFlag was set, put this value in constraints array
                c[i] = c[i] | check;
                conditionFlag = !conditionFlag; //turn this flag off for re-use during next condition check
            }
            if((check == 4 || check == 8) && (conditionFlag)){ //if ^ or v and conditionFlag was set, put this value in constraints array
                c[i] = c[i] | check;
                conditionFlag = !conditionFlag; //turn this flag off for re-use during next condition check
            }
        }
    }
    fclose(in);
    return 1;
}

/* function header comment goes here */
void printPuzzle(const int *puzzle, const int *constraints, int size) {
    int i = 0;
    int j;
    int lineNumber = 2;
    bool incrementLineNumber = 0;

    do{ //handles every single element of each array
        for (j = 0; j < size*2; j++){  // handles every elements of 'size' (each row)

            //if we're on a constraint line, move i back to the corresponding index
            if(j == 2*size-size){
                i = i-size;
            }

            //handle the starting elements of each new row here
            if ((j == 0 || j == (size)) && lineNumber%2 == 0){  //if line number is even (value row) and it's the first element of the row
                if(constraints[i]){
                    printf("\n|%d%c", puzzle[i], retConstraintChars(&constraints[i], lineNumber));  //switch these constraints out to return the characters based on the value
                }
                else{
                    printf("\n|%d ", puzzle[i]);
                }
            }
            if ((j == 0 || j == (size)) && lineNumber%2 != 0){  //if line number is odd (constraint row) and it's the first element of the row
                if(constraints[i]){
                    printf("\n|%c ", retConstraintChars(&constraints[i], lineNumber));
                }
                else{
                    printf("\n|  ");
                }
            }

            // handle the middle elements here
            if(j != 0 && j != (2*size)-(size+1) && j != (size) && j != (2*size-1) && lineNumber%2 == 0){  //if one of middle elements and on a VALUE line
                if(constraints[i]){
                    printf("%d%c", puzzle[i], retConstraintChars(&constraints[i], lineNumber));
                }
                else{
                    printf("%d ", puzzle[i]);
                }
            }
            if(j != 0 && j != (2*size)-(size+1) && j != (size) && j != (2*size-1) && lineNumber%2 != 0) {  //if one of middle elements and on a CONSTRAINT line
                if (constraints[i]) {
                    printf("%c ", retConstraintChars(&constraints[i], lineNumber));
                }
                else{
                    printf("  ");
                }
            }

            //handle the ending elements of each row here
            if((j == size-1 || j == (2*size-1)) && lineNumber%2 == 0){ //if one of end elements of a text line and on a VALUE line
                printf("%d|", puzzle[i]);
                incrementLineNumber = !incrementLineNumber;
            }

            if((j == size-1 || j == (2*size-1)) && lineNumber%2 != 0) { //if one of end elements of a text line and on a CONSTRAINT line
                if (constraints[i]) {
                    printf("%c|", retConstraintChars(&constraints[i], lineNumber));
                    incrementLineNumber = !incrementLineNumber;
                } else {
                    printf(" |");
                    incrementLineNumber = !incrementLineNumber;
                }
            }
            if ((j == size-1) && i == size*size){ //last character of puzzle
                incrementLineNumber = !incrementLineNumber;
            }
            if(incrementLineNumber){
                lineNumber++;
                incrementLineNumber = !incrementLineNumber;
            }

            i++;
        }
    }while(i < size*size);
}

/* function header comment goes here */
int solve(int *puzzle, const int *constraints, int size) {
    return 0;
}

/*function header comment goes here */
int isLegal(int row, int col, int num, const int *puzzle, const int *constraints, int size) {
    return 0;
}

int filterAsciiChar(char asciiChar){

    switch(asciiChar) {
        case 45  :
            return 0;  //- hyphen
        case 48  :
            return 0;
        case 49 :
            return 1;
        case 50  :
            return 2;
        case 51 :
            return 3;
        case 52  :
            return 4;
        case 53 :
            return 5;
        case 54  :
            return 6;
        case 55 :
            return 7;
        case 56  :
            return 8;
        case 57 :
            return 9;
        case 94  :
            return 4; // ^
        case 118  :
            return 8;  // V
        case 60  :
            return 1; // <
        case 62  :
            return 2; // >
        case 32  :
            return -2; // SPACE
        case 124  :
            return -3; // |
        default :
            return -1;
    }
}

char retConstraintChars(const int *constraints, int lineNumber){
    if(lineNumber%2 == 0){
        switch (*constraints) {
            case 1 :
                return '<';
            case 2 :
                return '>';
            case 5 :
                return '<';
            case 6 :
                return '>';
            case 9 :
                return '<';
            case 10 :
                return '>';
            default :
                return ' ';
        }
    }
    else if(lineNumber%2 != 0){
        switch (*constraints) {
            case 4 :
                return '^';
            case 8 :
                return 'v';
            case 9 :
                return '^';
            case 10 :
                return 'v';
            default :
                return ' ';
        }
    }
    return 1;
}
