CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
IFLAGS=

all: dgl

dgl: main.o GraphNode.o GraphNodeParameters.o GraphNodeSet.o Bezier.o Bond.o DGLLoader.o
	$(CC) main.o GraphNode.o GraphNodeParameters.o GraphNodeSet.o Bezier.o Bond.o DGLLoader.o -o dgl $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) $(IFLAGS) main.cpp

GraphNode.o: GraphNode.cpp
	$(CC) $(CFLAGS) $(IFLAGS) GraphNode.cpp

GraphNodeParameters.o: GraphNodeParameters.cpp
	$(CC) $(CFLAGS) $(IFLAGS) GraphNodeParameters.cpp

GraphNodeSet.o: GraphNodeSet.cpp
	$(CC) $(CFLAGS) $(IFLAGS) GraphNodeSet.cpp

Bezier.o: Bezier.cpp
	$(CC) $(CFLAGS) $(IFLAGS) Bezier.cpp

Bond.o: Bond.cpp
	$(CC) $(CFLAGS) $(IFLAGS) Bond.cpp

DGLLoader.o: DGLLoader.cpp
	$(CC) $(CFLAGS) $(IFLAGS) DGLLoader.cpp

clean:
	rm -rf *o dgl
