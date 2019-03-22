/* Program 2 -- Futoshiki puzzle
 * Usage: Futoshiki puzzle <filename>
 * This program accepts file pointer to <filename> and will print a solution to a futoshiki puzzle if it exists
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

    //this function was just for my debugging to show me what's in the arrays
    //printJustArrays(puzzle, constraints, size);

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


/* Name: readPuzzle
 * Function: this function reads contents of <filename> and generates arrays with specific values from the file
 * Arguments: char *name, int **puzzle, int **constraints, int *size
 * Returns: zero when file could not be read
 *          1 when file is read successfully
  * */
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


/* Name: printPuzzle
 * Function: this function prints to std out contents of arrays in futoshiki puzzle form
 * Arguments: const int *puzzle, const int *constraints, int size
 * Returns: void
  * */
void printPuzzle(const int *puzzle, const int *constraints, int size) {
    int i = 0;
    int j;
    int lineNumber = 2;
    bool incrementLineNumber = 0;
    bool exitDoWhile = 0;

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
            if ((j == size-1) && i == (size*size-1)){ //last character of puzzle
                exitDoWhile  = !exitDoWhile ;
                break;
            }
            if(incrementLineNumber){
                lineNumber++;
                incrementLineNumber = !incrementLineNumber;
            }

            i++;
        }
        if(exitDoWhile) break;
    }while(i < (size*size)-1);
}

/* Name: solve
 * Function: this function recursively solves the futoshiki puzzle
 * Arguments: int *puzzle, const int *constraints, int size
 * Returns: zero when no solution exists for current iteration of puzzle
 *          1 when solution exists for current iteration of puzzle
  * */
int solve(int *puzzle, const int *constraints, int size) {
    int i = 0; //number to try
    int element = 0; //puzzle element
    int col = 0; //tracker for columns
    int row = 0;

    for(col = 0; col < size; col++){
        if((col == size-1) && puzzle[element] != 0){ //check if start of new row
            row++;
            col = (col - size);
        }
        if(puzzle[element] == 0){  //check if there is already a number if so, move on to next element
            break;
        }
        if(element == size*size) return 1; //if at end of array and no zero elements, puzzle solved
        element++;
    }

    for (i = 1; i <= size; i++) {
        if (isLegal(row, col, i, puzzle, constraints, size)) {
            puzzle[element] = i;  //if legal, place the number in the box and see if it solved the puzzle
            if (solve(puzzle, constraints, size)) {
                return 1;
            } else {
                puzzle[element] = 0;
            }
        }
    }
    return 0;
}

/* Name: isLegal
 * Function: this function checks conditions that a number, num satisfies rules of futoshiki puzzle
 * Arguments: int row, int col, int num, const int *puzzle, const int *constraints, int size
 * Returns: zero when num is illegal
 *          1 when num is legal
  * */
int isLegal(int row, int col, int num, const int *puzzle, const int *constraints, int size) {
    int E = 0;
    int e;
    int colTraverse;
    int rowTraverse;

    //define element and copy values before they are modified
    E = (row*size)+col; //define which element we're at base on row and column
    e = E;
    colTraverse = col;
    rowTraverse = row;

    //check left
    while(colTraverse > 0){
        e--;
        if (puzzle[e] == num) return 0;
        colTraverse--;
    }

    e = E;  //reset e to the element we're checking
    colTraverse = col;
    //check right
    while(colTraverse < size){
        e++;
        if (puzzle[e] == num) return 0;
        colTraverse++;
    }
    e = E;
    //check up
    while(rowTraverse > 0){
        e -= size;
        if (puzzle[e] == num) return 0;
        rowTraverse--;
    }
    e = E;
    rowTraverse = row;
    //check down
    while(rowTraverse < (size-1)){
        e += size;
        if (puzzle[e] == num) return 0;
        rowTraverse++;
    }

    //RELATIONAL CHECKS
    //if box of interest is non-zero and constraint is not met, then not legal
    e = E;
    //check box to the left for constraint and that it's satisfied
    if(col> 0 && constraints[E-1]){
        switch(constraints[E-1]){
            case 1 :  // <
                if (puzzle[e-1] !=0 && !(num > puzzle[e-1])) return 0;
                break;
            case 2 :  // >
                if(puzzle[e-1] !=0 && !(num < puzzle[e-1])) return 0;
                break;
            case 5 :  // < and  ^
                if(puzzle[e-1] != 0 && !(num > puzzle[e-1])) return 0;
                break;
            case 6 :  // > and  ^
                if(puzzle[e-1] != 0 && !(num < puzzle[e-1])) return 0;
                break;
            case 9 :  // < and  v
                if(puzzle[e-1] != 0 && !(num > puzzle[e-1])) return 0;
                break;
            case 10 :  // > and  v
                if(puzzle[e-1] != 0 && !(num < puzzle[e-1])) return 0;
                break;
        }
    }
    //check box above for constraint and that it's satisfied
    if(row > 0 && constraints[E-size]){
        switch(constraints[E-size]){
            case 4 :  //  ^
                if(puzzle[e-size] != 0 && !(num > puzzle[e-size])) return 0;
                break;
            case 5 :  // < and  ^
                if(puzzle[e-size] != 0 && !(num > puzzle[e-size])) return 0;
                break;
            case 6 :  // > and  ^
                if(puzzle[e-size] != 0 && !(num > puzzle[e-size])) return 0;
                break;
            case 8 :  //  v
                if(puzzle[e-size] != 0 && !(num < puzzle[e-size])) return 0;
                break;
            case 9 :  // < and  v
                if(puzzle[e-size] != 0 && !(num < puzzle[e-size])) return 0;
                break;
            case 10 :  // > and  v
                if(puzzle[e-size] != 0 && !(num < puzzle[e-size])) return 0;
                break;
        }
    }

    switch(constraints[E]){
        case 1 :  // <
            if (puzzle[e+1] !=0 && !(num < puzzle[e+1])) return 0;
            break;
        case 2 :  // >
            if(puzzle[e+1] !=0 && !(num > puzzle[e+1])) return 0;
            break;
        case 4 :  //  ^
            if(puzzle[e+size] != 0 && !(num < puzzle[e+size])) return 0;
            break;
        case 5 :  // < and  ^
            if(puzzle[e+1] != 0 && !(num < puzzle[e+1])) return 0;
            if(puzzle[e+size] != 0 && !(num < puzzle[e+size])) return 0;
            break;
        case 6 :  // > and  ^
            if(puzzle[e+1] != 0 && !(num > puzzle[e+1])) return 0;
            if(puzzle[e+size] != 0 && !(num < puzzle[e+size])) return 0;
            break;
        case 8 :  //  v
            if(puzzle[e+size] != 0 && !(num > puzzle[e+size])) return 0;
            break;
        case 9 :  // < and  v
            if(puzzle[e+1] != 0 && !(num < puzzle[e+1])) return 0;
            if(puzzle[e+size] != 0 && !(num > puzzle[e+size])) return 0;
            break;
        case 10 :  // > and  v
            if(puzzle[e+1] != 0 && !(num > puzzle[e+1])) return 0;
            if(puzzle[e+size] != 0 && !(num > puzzle[e+size])) return 0;
            break;
    }

    return 1; // is a legal number for this spot
}

/* Name: filterAsciiChar
 * Function: this function accepts an ascii character and returns a decimal digit
 * Arguments: char asciiChar
 * Returns: integers ranging from -3 t 9, depending on which char is recieved
  * */
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

/* Name: retConstraintChars
 * Function: this function accepts constraint array, and a row number (linenumber), and returns the appropriate ascii character
 * for the purpose of printing to std out
 * Arguments: const int *constraints, int lineNumber
 * Returns: range of ascii characters depending on which decimal is in the current constraint element
 *          1 when no there is no constraint associated with the current element
  * */
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


/*
 * //function made strictly for debugging to easily view contents of arrays
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
*/