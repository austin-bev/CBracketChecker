/* 
FILE: Colors.h
Author: Austin Bevacqua
StudentID: 20162896
Unit: Unix and C Programming
Purpose: A header file for colors.c which defines macros and function declariations
Last modified: 19/09/2020
*/

/* Header guard */
#ifndef COLORS_H
#define COLORS_H

#include "charComp.h"

/*Defines all the ANSI values of the font colurs*/
#define BLACK 30
#define RED 31
#define GREEN 32  
#define YELLOW 33 
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define WHITE 37

/*Defines all ANSI value that is added to change text color to background color*/
#define BACKGROUND 10

/* Color.c function declariations */
int getColor(char*);
void setTextColor(int);
void setBgColor(int);
void setUnderline(int);
void resetColor();

/* Macros */
#define COMP(A,B) ((strComp(A, B) == TRUE))

#endif
