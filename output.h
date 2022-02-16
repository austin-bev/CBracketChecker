/* 
FILE: Output.h
Author: Austin Bevacqua
StudentID: 20162896
Unit: Unix and C Programming
Purpose: A header file for output.c
Last modified: 19/09/2020
*/
#ifndef OUTPUT_H
#define OUTPUT_H

/* Typedef for the interator struct */
typedef struct {
    int line;
    int position;
    char* message;
} Iterator;

#include "charComp.h"
#include "colors.h"
#include "newSleep.h"
#include "linkedlist.h"

/* FUNCTION PROTOTYPES */
/* Output.c */
void output(LinkedList*);
void printStack(LinkedList*);
void outputBody(Iterator*, LinkedList*, LinkedList*);
LinkedListNode* matchLine(LinkedListNode*, LinkedListNode*, int);
void printPointer(Iterator*);
void whiteSpace(int);
void printSuccess();
void printStackNotEmpty(LinkedList*);
char findOppositeBrac(char*);
Iterator* setIterator();

/* Macros */
#define CLEAR (system("clear"))

#endif
