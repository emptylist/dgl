CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

all: dgl

dgl: main.o GraphNode.o Bond.o
	$(CC) main.o GraphNode.o Bond.o -o dgl $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

GraphNode.o: GraphNode.cpp
	$(CC) $(CFLAGS) GraphNode.cpp

Bond.o: Bond.cpp
	$(CC) $(CFLAGS) Bond.cpp

clean:
	rm -rf *o dgl