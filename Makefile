# tool macros
CC = gcc
C_FLAGS	= -Wall -std=c11

# source files & object files
SOURCES	= demo.c Part_A.c Part_B.c
HEADERS	= Part_A.h Part_B.h
OBJECTS	= objects/demo.o objects/Part_A.o objects/Part_B.o


.PHONY: all
all: demo

run: demo
	./$^

mem_test: demo
	valgrind ./$^

demo: $(OBJECTS)
	$(CC) $(C_FLAGS) $^ -o demo

objects/%.o: %.c $(HEADERS)
	$(CC) $(C_FLAGS) --compile $< -o $@

clean:
	rm -f $(OBJECTS) *.o demo