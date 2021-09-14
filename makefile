CC = clang++
#CC = g++

all: hex

hex: main.o graph.o priorityQueue.o dPath.o hex.o
	${CC} main.o graph.o priorityQueue.o dPath.o hex.o -o hex

main.o: graph.h priorityQueue.h dPath.h hex.h main.cpp
	${CC} -c main.cpp

graph.o: graph.h graph.cpp
	${CC} -c graph.cpp

priorityQueue.o: priorityQueue.h priorityQueue.cpp
		${CC} -c priorityQueue.cpp

dPath.o: graph.h priorityQueue.h dPath.h dPath.cpp
		${CC} -c dPath.cpp

hex.o:	graph.h priorityQueue.h dPath.h hex.h hex.cpp
	${CC} -c hex.cpp

clean:
	rm hex *.o
