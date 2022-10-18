CC = clang++
#CC = g++

all: hex

hex: main.o graph.o priorityQueue.o dPath.o HexBoard.o HexGameEngine.o
	${CC} main.o graph.o priorityQueue.o dPath.o HexBoard.o HexGameEngine.o -o hex

main.o: hex.h dPath.h graph.h priorityQueue.h HexGameEngine.h HexPlayer.h HexBoard.h main.cpp
	${CC} -c main.cpp

graph.o: graph.h graph.cpp
	${CC} -c graph.cpp

priorityQueue.o: priorityQueue.h priorityQueue.cpp
		${CC} -c priorityQueue.cpp

dPath.o: graph.h priorityQueue.h dPath.h dPath.cpp
		${CC} -c dPath.cpp

#HexPlayer.o:	hex.h graph.h priorityQueue.h dPath.h HexPlayer.h HexPlayer.cpp
#	${CC} -c HexPlayer.cpp

HexBoard.o:	hex.h HexBoard.h HexBoard.cpp
	${CC} -c HexBoard.cpp

HexGameEngine.o:	hex.h dPath.h graph.h priorityQueue.h HexPlayer.h HexBoard.h HexGameEngine.h HexGameEngine.cpp
	${CC} -c HexGameEngine.cpp

clean:
	rm hex *.o

