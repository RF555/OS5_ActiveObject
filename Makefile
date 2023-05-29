OBJECTS	= main.o Part_A.o Part_B.o
SOURCE	= main.c Part_A.c Part_B.c
HEADER	= Part_A.h Part_B.h
OUT	= main
CC	 = gcc
FLAGS	 = -c -Wall
LFLAGS	 =

run: $(OUT)
	./$(OUT)

all: $(OBJECTS)
	$(CC) -g $(OBJECTS) -o $(OUT) $(LFLAGS)

#main: main.o
#	./main

main.o: main.c
	$(CC) $(FLAGS) main.c -std=c11

Part_A.o: Part_A.c
	$(CC) $(FLAGS) Part_A.c -std=c11

Part_B.o: Part_B.c
	$(CC) $(FLAGS) Part_B.c -std=c11


clean:
	rm -f $(OBJECTS) main