/*
FILE: Colors.c
Author: Austin Bevacqua
StudentID: 2016289
Unit: Unix and C Programming
Purpose: A class which provides functionality for the modifing of text colors through ANSI codes
Date: 19/09/2020 (Originally submitted for UCP Assignment One)
Last modified: 23/10/2020
*/

#include <stdio.h>
#include "colors.h"

/* Function: getColor
Purpose: Assigns a INT color to an imported string
Imports: color (String)
Exports: colorValue (int) */
int getColor(char* color) 
{
    int colorValue;
    /* We convert the imported string to uppercase to acheive case-insensitive text matching */
    strToUpper(color); 
    if COMP("RED", color)
        colorValue = RED;
    else if COMP("GREEN", color)
        colorValue = GREEN;
    else if COMP("YELLOW", color)
        colorValue = YELLOW;
    else if COMP("BLUE", color)
        colorValue = BLUE;
    else if COMP("MAGENTA", color)
        colorValue = MAGENTA;
    else if COMP("CYAN", color)
        colorValue = CYAN;
    else if COMP("WHITE", color)
        colorValue = WHITE;
    else if COMP("BLACK", color)
        colorValue = BLACK;
    else {
        colorValue = WHITE;
    }
    return colorValue;
}

/* Function: setTextColor
Purpose: Sets the ANSI text color to the colorValue parameter
Imports: colorValue (int)
Exports: none */
void setTextColor(int colorValue) {
    printf("\033[1;%dm", colorValue);
}

/* Function: setBgColor
Purpose: Sets the ANSI background text color to the colorValue parameter
Imports: colorValue (int)
Exports: none */
void setBgColor(int colorValue) {
    printf("\033[1;%dm", colorValue + BACKGROUND);
}

/* Function: setUnderline
Purpose: Sets the ANSI text color and underline to colorValue parameter
Imports: colorValue (int)
Exports: none */
void setUnderline(int colorValue) {
    printf("\033[4;%dm\033[1;%dm", colorValue, colorValue);
}

/* Function: resetColor
Purpose: Sets the ANSI text color back to its default values
Imports: none
Exports: none */
void resetColor() {
    printf("\033[0m");
}

