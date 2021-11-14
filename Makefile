#
# This is an example Makefile for 1024 game project. 
# This program uses Board and TestBoard modules.
# Typing 'make' or 'make run' will create the executable file.

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++ -std=c++11
#CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
all: run

# To create the executable file run we need the object files
# RunCompetition.o, Competition.o, Hare.o, Tortoise.o, and Road.o:
run:  TestBoard.o Board.o 
	$(CC) -o run TestBoard.o Board.o

# To create the object file RunCompetition.o, we need the source
# files RunCompetition.cpp, Competition.h 
TestBoard.o:  TestBoard.cpp
	$(CC) -c TestBoard.cpp

# To create the object file Competition.o, we need the source
# files Competition.cpp and Competition.h 
#
Board.o:  Board.cpp
	$(CC) -c Board.cpp

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) run *.o *~

