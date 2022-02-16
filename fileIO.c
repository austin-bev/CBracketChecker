/* 
Author: Austin Bevacqua
Student ID: 20162896
File: FileIO.c
Purpose: Reads every line of an imported file into a linked list
Last modified: 23/10/20
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"

/********************
Function: Read File
Purpose: Inserts every line of a file into a linked list. Each line is a new entry
Assertion: Every line is less than 100 characters
Date: 14/10/20
Author: Austin Bevacqua
*********************/
void readFile(FILE* inFile, LinkedList* fileLines) {
    /*We set the max string length to 100 */
    /*The fgets function will return a null pointer once the EOF has been reached. */
    char* line = (char*)malloc(sizeof(char) * 100);
    while(fgets(line,100,inFile) != NULL) {
        insertLast(fileLines,line);
        line = (char*)malloc(sizeof(char) * 100);
        /*Once we reach the null pointer, we stop the loop as all lines have been read. */
        /*The string returned from fgets is inserted into the last location in the linked list */
    }
    free(line);
}
    
