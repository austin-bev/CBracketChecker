/*
FILE: Main.c
Author: Austin Bevacqua
StudentID: 2016289
Unit: Unix and C Programming
Purpose: The entry point to the bracketCheck algorithm. Verifies that the arguments and imported file are valid.
Last modified: 23/10/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char* argv[])
{
    /* If there are an incorrect number of arguments, the program ends and notified the user*/
    if(argc != 2) 
    {
        printf("Format: ./ <textfile>\n <textfile> can be .txt, .c, ect...\n");
    }
    else 
    {
        FILE* inFile;   
        LinkedList* fileLines;

        /*The file is opened by fopen */
        inFile = fopen(argv[1], "r");
        if (inFile == NULL) { /*If there file pointer is null, the file has not been read propertly, and an error will be displayed oto the screen */
            perror("Error opening file: ");
        }
        else { /*If the file it not null, we pass it to te fileLines function, which will put every line of the file into a linked list.*/
            fileLines = createLinkedList(); /*The linked list is created */
            readFile(inFile, fileLines); /*The contents of the file is inserted into a linked list */
            if(ferror(inFile)) { /*If there are any detected errors, they are displayed to the screen and the algorithm does not continue */
                perror("Error reading from file: ");
            }
            else { /*If there are no problems, the linked list containing all lines from the file is passed to the output function, which will check every character for brackers and output the results to the screen. */
                output(fileLines);
            }
            /*The fileLines linked list and all of its elements are freed */
            freeLinkedList(fileLines, &freeEntry);
            fclose(inFile); /*The opened file is closed */
        }
        
    }
    return 0;   
}
