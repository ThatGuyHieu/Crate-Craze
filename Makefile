CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: Sokoban Sokoban.a

Sokoban: main.o Sokoban.o
	$(CC) $(CFLAGS) -o Sokoban main.o Sokoban.o $(LIB)

Sokoban.a: Sokoban.o main.o
	ar rcs Sokoban.a Sokoban.o main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

lint:
	cpplint --filter=-build/include_what_you_use *.cpp *.hpp

Sokoban.o: Sokoban.cpp Sokoban.hpp
	$(CC) $(CFLAGS) -c Sokoban.cpp

clean:
	rm *.o *.a Sokoban