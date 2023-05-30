# tool macros
CC = gcc
C_FLAGS	= -Wall -pedantic -std=c11 -pthread

# source files & object files
SOURCES	= demo.c Part_A.c Part_B.c Part_C.c Part_D.c
HEADERS	= Part_A.h Part_B.h Part_C.h Part_D.h
MAIN_OBJECT = objects/main.o
DEMO_OBJECT = objects/demo.o
OBJECTS	= objects/Part_A.o objects/Part_B.o objects/Part_C.o objects/Part_D.o


.PHONY: all
all: st_pipeline

run: demo
	./$^

st_pipeline: $(MAIN_OBJECT) $(OBJECTS)
	$(CC) $(C_FLAGS) $^ -o st_pipeline

mem_test: demo
	valgrind ./$^

demo: $(DEMO_OBJECT) $(OBJECTS)
	$(CC) $(C_FLAGS) $^ -o demo

objects/%.o: %.c $(HEADERS)
	$(CC) $(C_FLAGS) --compile $< -o $@

clean:
	rm -f $(OBJECTS) $(DEMO_OBJECT) $(MAIN_OBJECT) *.o demo st_pipeline