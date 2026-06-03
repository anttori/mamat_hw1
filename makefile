CC = gcc
CFLAGS = -g -Wall -std=c99
CCLINK = gcc
OBJS = main.o student.o stack.o
EXEC = prog.exe
RM = rm -rf

$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)
	
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c -o stack.o
	
student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c -o student.o
	
main.o: main.c student.h stack.h
	$(CC) $(CFLAGS) -c main.c -o main.o
	
clean:
	$(RM) $(OBJS) $(EXEC)
