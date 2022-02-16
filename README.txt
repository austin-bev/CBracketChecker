Bracket Check

Author: Austin Bevacqua

Prerequisites
    The program requires a instaliation of the gcc C compiler.

Overall design and functionality
    An imported file is checked to see if brackets are consistent. 
    Works with bracket pairs [] <> () and {}
    ANSI codes are used to manipulte the output text

Compiling the program
    Simple run "make" to compile the program
    Optionally, run "make STACK=1" to enable the output of the current bracket stack
    Furthermore, run "make clean" to delete all .o files.

Running the program
    The algorithm must run with the following arguments
    ./bracketCheck <filename>    
        For example: ./bracketCheck fileIO.c

    
