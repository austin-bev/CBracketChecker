/*
FILE: charComp.c
Author: Austin Bevacqua
StudentID: 2016289
Unit: Unix and C Programming
Purpose: Functions for comparing characters and adding found matches to linked lists.
Date: 19/09/2020 (Originally submitted for Assignment One)
Last modified: 23/10/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charComp.h"

/*Function: strToUpper
Purpose: Converts a string to all uppercase values
Parametres: string (String)
Last modified: 19/09/2020 */
void strToUpper(char* string)
{
    int i = 0;
    char curr;

    while ((*(string+i)) != '\0') /* Loop continues until string ends */
    {
        curr = *(string+i);
        if ((curr >= 97) && (curr <= 122)) /*ASCII values for lowercase characters. If a char falls into this range, it is changed*/
        {
            *(string+i) = (curr - 32); /*By subtracting 32 from the ASCII value, we get a character's uppercase equivalent*/
        }
        i++;
    }
}

/*Function: strComp
Purpose: Compares if two strings are identical
Parametres: strOne (String), strTwo (String)
Last modified: 19/09/2020 */
int strComp(char* strOne, char* strTwo)
{
    int similar = TRUE;
    int i = 0;

    while(((strOne[i]!='\0') || (strTwo[i]!='\0')) && (similar == TRUE))
    {
        if(strOne[i]!=strTwo[i])
        {
            similar = FALSE;
        }
        i++;
    }

    return similar;
}

/*Function: charToLower
Purpose: Converts a character into its lowercase equivalent
Imports: character (char)
Last Modified: 19/09/2020 */
char charToLower(char character)
{
    char newChar;
    /* If the character lies between the ASCII values for uppercase values */
    if ((character >= 65) && (character <= 90))
    {
        /* We add 32 to find the characters lowercase ASCII equivalent */
        newChar = character + 32;
    }
    else
    {
        newChar = character;
    }
    return newChar;
}

/*Function: checkBrackets
Purpose: Checks a character. If it is a bracket, various actions are performed. 
Imports: currChar (char), itr (Iterator struct), matches (Linked list struct), currBrackets (Linked list struct)
Last Modified: 23/09/2020 */
void checkBrackets(char currChar, Iterator* itr, LinkedList* matches, LinkedList* currBrackets) {
    /* We check to see if the imported character is a bracket */
    switch(currChar) {
        /* In all cases, if a match is found is it stored in the "matches" linked list */
        /* If an OPENING BRACKET is found, it is added to the "stack" and list of all matches (linked list) */
        case '(': 
            /* Macro "PUSHTOSTACK" calls function pushCharToStack, which adds the current character to the top of the stack & to the end of the list of total matches */
            PUSHTOSTACK(CREATEMATCH("YELLOW"));
        break;
        case '<':
            PUSHTOSTACK(CREATEMATCH("MAGENTA"));
        break;
        case '{':
            PUSHTOSTACK(CREATEMATCH("BLUE"));
        break;
        case '[':
            PUSHTOSTACK(CREATEMATCH("CYAN"));
        break;
        /* If a CLOSING BRACKET is found, the top item is removed from the stack */
        case ')':
             /* Macro COMPARESTACK checks to see if the item at the top of the stack is equal to the expected result. 
                In the case of '(', it will check to see if the last opening bracket was ')'. If it is not equal, an error is created */
            COMPARESTACK('(');
            /* We add the closing bracket to the end of the "all matches" linked list */
            INSERTLAST(CREATEMATCH("YELLOW"));
        break;
        case '>':
            COMPARESTACK('<');
            INSERTLAST(CREATEMATCH("MAGENTA"));
        break;
        case '}':
            COMPARESTACK('{');
            INSERTLAST(CREATEMATCH("BLUE"));
        break;
        case ']':
            COMPARESTACK('[');
            INSERTLAST(CREATEMATCH("CYAN"));
        break;
        /* There is no need for a default statement, as if no matches are found nothing is changed */
    }   
}

/*Function: createMatch
Purpose: Creates a copy of the current character as a struct.
Author: Austin Bevacqua (20162896)
Last Modified: 19/09/2020 */
CharMatch* createMatch(Iterator* itr, LinkedList* matches, char* inColor){
    CharMatch* newMatch;
    newMatch = (CharMatch*)malloc(sizeof(CharMatch));
    
    /* Classfields are initalised as the iterators current position */
    newMatch->line = itr->line;
    newMatch->position = itr->position;
    /* Color is set depending on imported parameter */
    newMatch->color = getColor(inColor);
    /* By default, value hasMatch is set to TRUE. If the bracket is an opening bracket, this is changed to FALSE in function pushCharToStack */
    newMatch->hasMatch = TRUE;
    return newMatch;
}


/*Function: compareStack
Purpose: Checks to see if the value at the top of the "stack" is equal to the expected result. If not, an error is created
Author: Austin Bevacqua (20162896)
Last Modified: 23/09/2020 */
void compareStack(Iterator* itr, char expected, LinkedList* currBrackets, LinkedList* matches) {
    CharMatch* lastMatch;
    StackBracket* actual;

    /* If the stack is empty, then it is the case that there is NO opening bracket before the closing bracket */
    if (currBrackets->count == 0) {
        itr->message = (char*)malloc(sizeof(char) * 22); /* Error message is created */
        sprintf(itr->message, "'%c' Expected before this", expected);
    }
    else {
        /* We remove the first element off the currBrackets linked list, using it as a stack */
        actual = (StackBracket*) removeStart(currBrackets);
        /* If the EXPECTED result differs from the ACTUAL result, an error is created */ 
        if (expected != actual->bracChar[0]) {
            itr->message = (char*)malloc(sizeof(char) * 13);
            sprintf(itr->message, "'%c' Expected", expected);
        }
        else {
            /* If there are no problems, the top value of the stack is set to have a match (hasMatch), and is now highlighted in output */
            lastMatch = actual->bracketStruct;
            lastMatch->hasMatch = TRUE;
        }
        /* Values in the stack are freed, as they are not accessed / used after this point */
        free(actual->bracChar);
        free(actual);
    }
}

/*Function: pushCharToStack
Purpose: Adds a character to a stack as a StackBracket struct 
Author: Austin Bevacqua (20162896)
Last Modified: 23/09/2020 */
void pushCharToStack(char inChar, LinkedList* inStack, CharMatch* inMatch, LinkedList* matches) {
    StackBracket* newStackEntry;
    newStackEntry = (StackBracket*)malloc(sizeof(StackBracket));

    newStackEntry->bracChar = (char*)malloc(sizeof(char));
    memcpy(newStackEntry->bracChar, &inChar, sizeof(char)); /* The value of the current character is copied into the struct */
    
    /* As only opening brackets are added to the "stack", the "hasMatch" value is set to be FALSE, as the bracket does not currently have a matching closing bracket */
    inMatch->hasMatch = FALSE;
    newStackEntry->bracketStruct = inMatch; /*The memory location of the bracket is stored in the stack entry, we so we refer back to it once we have found a matching bracket */

    INSERTLAST(inMatch); /* Inserts the new entry into the last location in the linked list */
    insertStart(inStack, newStackEntry); /*Pushes the new entry to the top of the stack */
}
