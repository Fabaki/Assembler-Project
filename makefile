COMPILER = gcc
FLAGS = -Wall -ansi -pedantic

assembler: main.o errors.o externals.o first_pass.o input_manipulator.o memory_structure.o opcodes.o output.o second_pass.o string_manipulation.o symb_table.o
	$(COMPILER) -g $(FLAGS) main.o errors.o externals.o first_pass.o input_manipulator.o memory_structure.o opcodes.o output.o second_pass.o string_manipulation.o symb_table.o -o assembler

main.o: main.c input_manipulator.h passes.h output.h errors.h
	$(COMPILER) -c $(FLAGS) main.c -o main.o

errors.o: errors.c errors.h
	$(COMPILER) -c $(FLAGS) errors.c -o errors.o

externals.o: externals.c externals.h
	$(COMPILER) -c $(FLAGS) externals.c -o externals.o

first_pass.o: first_pass.c passes.h input_manipulator.h string_manipulation.h memory_structure.h opcodes.h symb_table.h errors.h
	$(COMPILER) -c $(FLAGS) first_pass.c -o first_pass.o

input_manipulator.o: input_manipulator.c input_manipulator.h
	$(COMPILER) -c $(FLAGS) input_manipulator.c -o input_manipulator.o

memory_structure.o: memory_structure.c memory_structure.h
	$(COMPILER) -c $(FLAGS) memory_structure.c -o memory_structure.o

opcodes.o: opcodes.c opcodes.h
	$(COMPILER) -c $(FLAGS) opcodes.c -o opcodes.o

output.o: output.c output.h symb_table.h externals.h memory_structure.h errors.h passes.h
	$(COMPILER) -c $(FLAGS) output.c -o output.o

second_pass.o: second_pass.c passes.h input_manipulator.h string_manipulation.h memory_structure.h output.h symb_table.h externals.h
	$(COMPILER) -c $(FLAGS) second_pass.c -o second_pass.o

string_manipulation.o: string_manipulation.c string_manipulation.h
	$(COMPILER) -c $(FLAGS) string_manipulation.c -o string_manipulation.o

symb_table.o: symb_table.c symb_table.h
	$(COMPILER) -c $(FLAGS) symb_table.c -o symb_table.o

clean:
	rm -f *.o
