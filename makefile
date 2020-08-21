COMPILER = gcc
FLAGS = -Wall -ansi -pedantic

match: match.o
	$(COMPILER) -g $(FLAGS) match.o -o match

match.o: match.c match.h
	$(COMPILER) -c $(FLAGS) match.c -o match.o
