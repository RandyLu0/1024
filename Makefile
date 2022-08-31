CC = g++ -std=c++11
CFLAGS  = -g -Wall

all: run
run:  TestBoard.o Board.o 
	$(CC) $(CFLAGS) -o run TestBoard.o Board.o
TestBoard.o:  TestBoard.cpp
	$(CC) -c TestBoard.cpp
Board.o:  Board.cpp
	$(CC) -c Board.cpp
clean: 
	$(RM) run *.o *~

