/*
FILE: Output.c
Author: Austin Bevacqua
StudentID: 2016289
Unit: Unix and C Programming
Purpose: Provides functions for outputting text the screen for the bracketMatch program
Last modified: 19/10/2020
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include "output.h"

/* Funcction: output
Purpose: Controls the overall "loop" of the program. Calls functions to do comparisons, printing to screen, ect...
Imports: fileLines (Linked List struct) - Contains every line of an imported file
Author: Austin Bevacqua (20162896)
Last Modified: 23/10/2020 */
void output(LinkedList* fileLines)
{
    /* Initalising the structs needed */
    LinkedList* matches;
    LinkedListNode* currNode;
    LinkedList* stack; /* Although just a linked list, if only the insertFirst and removeFirst functions are used, it has the same functionality as a stack */
    char* currLine;
    Iterator* itr;

    /* Functions which initalise the default values for the sructs */
    itr = setIterator();
    matches = createLinkedList();
    stack = createLinkedList();
    currNode = getHead(fileLines);
    currLine = (char*) currNode->data;
    
    /*We iterate over every character in the the imported linked list.
        The loop ends once the current line counter exceeded the number of lines in a file (We have found end of file)
        The loop ends if the iterator contains an error message. It will remain as null if there are no erros */
    while((itr->line < fileLines->count) && (itr->message == NULL)) {
        /*If the current character is a newline character, we enter the new line, setting the iterator at the first character */
        if ((*(currLine + itr->position) == '\n') || (*(currLine + itr->position) == '\0'))  {
            itr->line += 1; /* Next Line */
            itr->position = 0; /* First character of new line */
            currNode = getNext(currNode);
            if (currNode != NULL) {
                currLine = (char*) currNode->data;
            }
        }
        else {
            /* We sent the current character (determined by the iterator) to a function to determine wheter it is a bracket 
                If it is a bracket, we update out linked list, stack and potentially the error message (in itr) */
            checkBrackets(*(currLine + itr->position), itr, matches, stack);
            CLEAR;
            outputBody(itr, matches, fileLines);
            /* If the conditional compliation of STACK is defined, the current stack is printed, line by line, after the file */
            #ifdef STACK 
            printStack(stack);
            #endif
            newSleep(0.2);  /*As per assignent spec, the program is paused for 0.2 seconds */
            itr->position += 1;
        }
    }

    /* Once we exit the loop, we check whether the program reached the EOF or ended due to an error.
        If it reached the EOF, we check to see if there are any unfinished brackets */
    if (itr->message == NULL) {
        if (stack->count != 0){
            printStackNotEmpty(stack);
        }
        /* If the stack IS empty, we have no possible errors and can print a success message to the screen */
        else {
            printSuccess();
       }
    }
    else {
        free(itr->message);
    }

    /* All malloced structs are freed, preventing any memory leaks*/
    freeLinkedList(matches, &freeEntry);
    freeLinkedList(stack, &freeEntry);
    free(itr);
}

/* Function: printStack
Purpose: Prints the current bracket stack, with each element being on a new line 
Author: Austin Bevacqua (20162896)
Last Modified: 23/10/2020 */
void printStack(LinkedList* currBrackets) {
    LinkedListNode* currNode;
    StackBracket* brac;

    currNode = currBrackets->head;
    printf("Current Stack:\n");
    while (currNode != NULL) {
        brac = (StackBracket*)currNode->data;
        printf("%s\n", brac->bracChar);
        currNode = getNext(currNode);
    }
}

/* Function: outputBody
Purpose: Outputs the updated string with any matches shown in a different color
Parametres: itr (Iterator struct) - The current character and line we are processing
            matches (Linked List struct) - A linked list containing the locations of all valid matches
            fileLines (Linked List struct) - All the lines in the imported file
Author: Austin Bevacqua (20162896)
Last Modidied: 19/10/2020 */
void outputBody(Iterator* itr, LinkedList* matches, LinkedList* fileLines)
{
    LinkedListNode* currNode;
    LinkedListNode* nextMatch;
    int currLine;
    CharMatch* match;

    currNode = getHead(fileLines);
    nextMatch = getHead(matches);
    currLine = 0;
    /* Loop continues until we reach a NULL line; meaning we have reached the end of file */
    while(currNode != NULL) {
        /*If there are NO MORE MATCHES we print the lines out in full, as there is no need to highlight any individual characters */
        if(nextMatch == NULL) {
            printf("%s", (char*) currNode->data);
        }
        else {
            match = (CharMatch*)nextMatch->data;
            /* If the next bracket is located in a line AFTER the current line, we print out the current line in full,
                There is no matches in this line and no need to highlight any individual characters */
            if(match->line > currLine) {
                printf("%s", (char*) currNode->data);
            }
            /* The only remaining valid option is there is a match on the CURRENT LINE. In this instance, we print every character individually 
                and highlight the matching characters */
            else{
                nextMatch = matchLine(currNode, nextMatch, currLine);
            }
        }

        /* If we are at the ccurrent "pointed at" line, we print the "^" character on a newline
            If there is an error, we insert it under the "^" character */
        if(currLine == itr->line) {
            printPointer(itr);
        }
        currLine++;
        currNode = getNext(currNode);
    }
    
}

/* Function: matchLine
Purpose: Iterates through every character to determine whether it has been labeled as a "match" by the algorithm
        If it is a valid match, it is highlighted in an appropriate color 
Imports: currNode (LinkedListNode) - The current line in the file
         nextMatch (LinkedListNode) - The next valid match within the file
         currLine (int) - The current line being printed in the file
Author: Austin Bevacqua (20162896)
Last modified: 20/10/20 */
LinkedListNode* matchLine(LinkedListNode* currNode, LinkedListNode* nextMatch, int currLine) {
    int currPosition;
    char* lineText;
    CharMatch* match;
    lineText = (char*) currNode->data;
    match = (CharMatch*) nextMatch->data;
 
    for(currPosition = 0; (*(lineText + currPosition) != '\n'); currPosition++) {
    /* We check that the next match is on the CURRENT LINE and NOT NULL & 
        If the next match is at the index of the current character.
        If all three statements are satisfied, we have found a match, and will print it in a different color */
        lineText = (char*) currNode->data;
        if ((nextMatch != NULL) && (currLine == match->line) && (currPosition == match->position)) {
            if(match->hasMatch == TRUE) {
                setBgColor(match->color); /* The color is set to be the color stored in te struct */
            }
            else {
                setTextColor(match->color);
            }
            printf("%c", *(lineText + currPosition));
            resetColor();
            nextMatch = getNext(nextMatch); /* We iterate to the next match, as it could appear in the same line */
            if (nextMatch != NULL) {
                match = (CharMatch*) nextMatch->data;
            }
        }
        /* If there is no match, we print out the character in regular text */
        else {
            printf("%c", *(lineText + currPosition));
        }
    }
    printf("\n");
    return nextMatch;
}

/* Funcction: printPointer
Purpose: Produces a line of whitespace equal to "iter" characters long, then the "^" character and any error message present 
Imports: itr (Iterator struct)
Author: Austin Bevacqua (20162896)
Last Modified: 19/10/2020 */
void printPointer(Iterator* itr) {
    /* Whitespace before the pointer */
    whiteSpace(itr->position);
    printf("^");
    /* If there is an error message, we print the whitespace, then the error in red font */
    if(itr->message != NULL) {
        printf("\n");
        whiteSpace(itr->position);
        setBgColor(getColor("RED"));
        printf("%s", itr->message);
        resetColor();
    }
    printf("\n");
}

/* Funcction: whiteSpace
Purpose: Prints blank space characters. Number of spaces depends on imported int
Author: Austin Bevacqua (20162896)
Last Modified: 19/10/2020 */
void whiteSpace(int position) {
    int i;
    for (i = 0; i < position; i++) {
        printf(" ");
    }
}

/* Funcction: printSuccess
Purpose: Prints a success message if there are no errors present. 
Author: Austin Bevacqua (20162896)
Last Modified: 19/10/2020 */
void printSuccess() {
    setTextColor(getColor("GREEN"));
    printf("All Good!\n");
    resetColor();
}

/* Funcction: printStackNotEmpty
Purpose: Prints an error message if the stack is not empty once the output loop has stopped.
Author: Austin Bevacqua (20162896)
Last Modified: 23/10/2020 */
void printStackNotEmpty(LinkedList* stack) {
    LinkedListNode* currNode;

    setBgColor(getColor("RED"));
    printf("Expected ");
    currNode = getHead(stack);
    /* Prints every value of the linked list, freeing them from memory once printed */
    while (currNode != NULL) {
        printf("%c ", findOppositeBrac(((StackBracket*)currNode->data)->bracChar));
        free(((StackBracket*)currNode->data)->bracChar);
        currNode = getNext(currNode);
    }
    printf("before file end\n");
    resetColor();
}

/* Funcction: findOppositeBrac
Purpose: Finds closing bracket to an opening bracket
Author: Austin Bevacqua (20162896)
Last Modified: 23/10/2020 */
char findOppositeBrac(char* inChar) {
    char opposite;
    switch(inChar[0]){
        case '(':
            opposite = ')';
        break;
        case '{':
            opposite = '}';
        break;
        case '<':
            opposite = '>';
        case '[':
            opposite = ']';
        break;
    }
    return opposite;
}

/* Funcction: setIterator
Purpose: Sets the default values of the iterator struct
Author: Austin Bevacqua (20162896)
Last Modified: 19/10/2020 */
Iterator* setIterator(){
    Iterator* itr;
    itr = (Iterator*)malloc(sizeof(Iterator));

    itr->line = 0;
    itr->position = 0;
    itr->message = NULL;
    return itr;
}
