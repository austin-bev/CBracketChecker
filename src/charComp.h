/* 
FILE: StringTools.h
Author: Austin Bevacqua
StudentID: 20162896
Unit: Unix and C Programming
Purpose: A header file for stringTools.c
Last modified: 19/09/2020
*/

/* Header Guard */
#ifndef CHARCOMP_H
#define CHARCOMP_H

#include "output.h"
#include "linkedlist.h"
#include "colors.h"

/* Constants */
#define TRUE 0
#define FALSE 1

/* Typedefs for structs */
typedef struct {
    int line;
    int position;
    int color;
    int hasMatch;
} CharMatch;

typedef struct {
    CharMatch* bracketStruct;
    char* bracChar;
} StackBracket;

/* Functuon Declariations */
void strToUpper(char*);
int strComp(char*, char*);
char charToLower(char);
void checkBrackets(char, Iterator*, LinkedList*, LinkedList*);
CharMatch* createMatch(Iterator*, LinkedList*, char*);
void compareStack(Iterator*, char, LinkedList*, LinkedList*);
void pushCharToStack(char, LinkedList*, CharMatch*, LinkedList*);

/* Macros */
#define INSERTLAST(x) (insertLast(matches, x))
#define CREATEMATCH(x) (createMatch(itr, matches, x))
#define COMPARESTACK(x) (compareStack(itr, x, currBrackets, matches))
#define PUSHTOSTACK(x) (pushCharToStack(currChar, currBrackets, x, matches))

#endif
