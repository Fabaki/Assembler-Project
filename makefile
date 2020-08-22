COMPILER = gcc
FLAGS = -Wall -ansi -pedantic

assembler: main.o
	$(COMPILER) -g $(FLAGS) match.o -o match

main.o: main.c match.h
	$(COMPILER) -c $(FLAGS) match.c -o match.o
