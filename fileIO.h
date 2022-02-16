/* 
FILE: Main.h
Author: Austin Bevacqua
StudentID: 20162896
Unit: Unix and C Programming
Purpose: A header file for main.c
Last modified: 19/09/2020
*/

/* Header Guard */
#ifndef FILEIO_H
#define FILEIO_H

#include "linkedlist.h"

/* Forward Declariations */
void readFile(FILE*, LinkedList*);
void freeEntry(void*);

#endif
