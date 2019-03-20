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
void printJustArrays(const int puzzle[], const int constraints[], int size);

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

    //this function is for my debugging to show me what's in the arrays
    printJustArrays(puzzle, constraints, size);

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
    char tempBuff;
    int arrayDigit;
    int element = -1;
    int lineNumber = 2;
    bool iterateI = false;
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

    //re-size p and c arrays according to first digit read from file (for my use to manipulated the array within this function)
    //the p and c pointers are just for main to see the same array I'm manipulating
    c = (int*) malloc((*size)*(*size)*sizeof(int));
    p = (int*) malloc((*size)*(*size)*sizeof(int));
    *puzzle = p;
    *constraints = c;

    //initialize all elements of both arrays to zeroes
    for(i = 0; i < ((*size)*(*size)); i++){
        p[i] = 0;
        c[i] = 0;
    }

    //handle every element of puzzle and constraint arrays from 0 to size^2
    for (i = 0; i < ((*size)*(*size)); i++) {
        element++;
        //group every two consecutive characters within an element of the array
        for (k = 0; k < 2; k++) {
            //continue scanning until we get to the first desired character of the row
            do {
                fscanf(in, "%c", &tempBuff);
                arrayDigit = filterAsciiChar(tempBuff);
                if(tempBuff == 'v' || tempBuff == '^' || tempBuff == '<' || tempBuff == '>')
                    conditionFlag = !conditionFlag;
                //reset i to zero for constraints array if I'm at ending BAR of the puzzle line (every even lineNumber); -3 is BAR
                if((lineNumber%2 == 0) && (element == (*size)-1) && (arrayDigit == -3)){
                    if(i == ((*size)*(*size)-1)) break;
                    i = i-(*size);  //take i to -1 to iterate to zero when I come around
                    element = element - *size;
                    lineNumber++;
                    break;
                }
                //iterate i if I'm at a the ending BAR of the constraints line (every odd lineNumber)
                if (lineNumber%2 != 0 && (element == (*size)-1) && (arrayDigit == -3)){
                    iterateI = !iterateI;
                    lineNumber++;
                    element = element - *size;
                    break;
                }
            } while (arrayDigit == -1 || arrayDigit == -3);
            if (iterateI){
                iterateI = !iterateI;
                break;
            }
            if (arrayDigit >= 0 && arrayDigit <= 9 && !(conditionFlag)) {
                p[i] = arrayDigit;
            }
            /*
             * 1 = <
             * 2 = >
             * 4 = ^
             * 8 = v
             * */
            if ((arrayDigit == 1 || arrayDigit == 2) && (conditionFlag)){
                c[i] = c[i] | arrayDigit;
                conditionFlag = !conditionFlag;
            }
            if((arrayDigit == 4 || arrayDigit == 8) && (conditionFlag)){
                c[i] = c[i] | arrayDigit;
                conditionFlag = !conditionFlag;
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
    int i = 0; //number to try
    int element = 0; //puzzle element
    int col = 0; //tracker for columns
    int row = 0;

        for(col = 0; col < size; col++){
            if(element == size*size) return 1; //no zero elements, puzzle solved
            if(col==(size-1)){
                row++;
            }
            if(puzzle[element] == 0){
                break;
            }
            element++;
        }

    for (i = 0; i < size; i++) {
        if (!isLegal(row, col, i, puzzle, constraints, size)) {
            break;
        } else {
            puzzle[element] = i;
            if (solve(puzzle, constraints, size)) {
                return 1;
            } else {
                puzzle[element] = 0;
            }
        }
    }
    return 0;
}

/*function header comment goes here */
int isLegal(int row, int col, int num, const int *puzzle, const int *constraints, int size) {
    int E = 0;
    int e;
    int travCol;
    int travRow;

    //define element and copy values before they are modified
    E = (row*size)+col;
    e = E;
    travCol = col;
    travRow = row;

    //check left
    while(travCol > 0){
        e--;
        if (puzzle[e] == num) return 0;
        travCol--;
    }

    e = E;
    travCol = col;
    //check right
    while(travCol < size){
        e++;
        if (puzzle[e] == num) return 0;
        travCol++;
    }
    e = E;
    //check down
    while(travRow > 0){
        e -= size;
        if (puzzle[e] == num) return 0;
        travRow--;
    }
    e = E;
    travRow = row;
    //check up
    while(travRow < (size-1)){
        e += size;
        if (puzzle[e] == num) return 0;
        travRow++;
    }

    //RELATIONAL CHECKS
    switch(constraints[e]){
        case 1 :  // <
            if (!(num < puzzle[e+1])) return 0;
        case 2 :  // >
            if(!(num > puzzle[e+1])) return 0;
        case 4 :  //  ^
            if(!(num < puzzle[e+size])) return 0;
        case 5 :  // < and  ^
            if(!((num < puzzle[e+1]) && (num < puzzle[e+size]))) return 0;
        case 6 :  // > and  ^
            if(!((num > puzzle[e+1]) && (num < puzzle[e+size]))) return 0;
        case 8 :  //  v
            if(!(num > puzzle[e+size])) return 0;
        case 9 :  // < and  v
            if(!((num < puzzle[e+1]) && (num > puzzle[e+size]))) return 0;
        case 10 :  // > and  v
            if(!((num > puzzle[e+1]) && (num > puzzle[e+size]))) return 0;
    }

    return 1;
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
                return 'v';
            case 10 :
                return 'v';
            case 5 :
                return '^';
            case 6 :
                return '^';
            default :
                return ' ';
        }
    }
    return 1;
}

void printJustArrays(const int puzzle[], const int constraints[], int size){
    int i = 0;
    int j = 0;
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
}
