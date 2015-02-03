CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

all: dgl

dgl: main.o GraphNode.o GraphNodeParameters.o GraphNodeSet.o Bezier.o Bond.o
	$(CC) main.o GraphNode.o GraphNodeParameters.o GraphNodeSet.o Bezier.o Bond.o -o dgl $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

GraphNode.o: GraphNode.cpp
	$(CC) $(CFLAGS) GraphNode.cpp

GraphNodeParameters.o: GraphNodeParameters.cpp
	$(CC) $(CFLAGS) GraphNodeParameters.cpp

GraphNodeSet.o: GraphNodeSet.cpp
	$(CC) $(CFLAGS) GraphNodeSet.cpp

Bezier.o: Bezier.cpp
	$(CC) $(CFLAGS) Bezier.cpp

Bond.o: Bond.cpp
	$(CC) $(CFLAGS) Bond.cpp

clean:
	rm -rf *o dgl