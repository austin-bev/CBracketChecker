CC = gcc
CFLAGS = -Wall -pedantic -ansi
OBJ = main.o fileIO.o linkedlist.o newSleep.o charComp.o colors.o output.o
EXEC = bracketCheck

ifdef STACK
CFLAGS += -D STACK
STACK : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) -c -g linkedlist.c $(CFLAGS)

newSleep.o : newSleep.c newSleep.h
	$(CC) -c -g newSleep.c $(CFLAGS)

colors.o : colors.c colors.h charComp.c charComp.h
	$(CC) -c -g colors.c $(CFLAGS)

fileIO.o : fileIO.c fileIO.h linkedlist.c linkedlist.h
	$(CC) -c -g fileIO.c $(CFLAGS)

main.o : main.c main.h linkedlist.c linkedlist.h fileIO.c fileIO.h output.c output.h
	$(CC) -c -g main.c $(CFLAGS)

output.o : output.c output.h colors.c colors.h linkedlist.c linkedlist.h newSleep.c newSleep.h charComp.c charComp.h
	$(CC) -c -g output.c $(CFLAGS)	

charComp.o : charComp.c charComp.h linkedlist.c linkedlist.h colors.c colors.h output.c output.h
	$(CC) -c -g charComp.c $(CFLAGS)

	
clean :
	rm -f $(OBJ)

clear :
	rm -f $(EXEC) $(OBJ)
