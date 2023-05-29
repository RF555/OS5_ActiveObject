OBJECT_PATH = objects
OBJECTS	= objects/Part_A.o objects/Part_B.o objects/main.o
#OBJECTS	= Part_A.o Part_B.o main.o
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
#
#main.o: main.c
#	$(CC) $(FLAGS) main.c -std=c11
#
#Part_A.o: Part_A.c
#	$(CC) $(FLAGS) Part_A.c -std=c11
#
#Part_B.o: Part_B.c
#	$(CC) $(FLAGS) Part_B.c -std=c11

$(OBJECT_PATH)/%.o: $(SOURCE) $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@


clean:
	rm -f $(OBJECTS) *.o main $(OBJECT_PATH)/*.o