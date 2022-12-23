CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = ppscheduler.c ppscheduler.h 
EXEC = PP_runner

$(EXEC) L $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

ppscheduler.o: ppscheduler.c ppscheduler.h
	$(CC) -c ppscheduler.c $(CFLAGS)

fileIO.o: fileIO.c fileIO.h
	$(CC) -c fileIO.c $(CFLAGS)

clean:
	rm -rf $(OBJ) $(EXEC)

runValgrind:
	valgrind ./$(EXEC) ppInput.txt