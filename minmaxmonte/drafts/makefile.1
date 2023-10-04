CC = clang++ -std=gnu++17
#CC = clang++ -std=gnu++17 -g -O0
#CC = g++


hpINC = graph.h MinPQ.h dPath.h bfs.h dfs.h HexPlayer.h
hbINC = ${hpINC} HexBoard.h
geINC = ${hbINC} HexUI.h HexConsoleUI.h HexGameEngine.h

all: hex

hex: main.o dPath.o HexBoard.o ComputerPlayer.o HexConsoleUI.o HexGameEngine.o
	${CC} main.o dPath.o HexBoard.o ComputerPlayer.o HexConsoleUI.o HexGameEngine.o -o hex

main.o: ${geINC} main.cpp
	${CC} -c main.cpp

dPath.o: graph.h MinPQ.h dPath.h dPath.cpp
		${CC} -c dPath.cpp

HexBoard.o:	${hbINC} HexBoard.cpp
	${CC} -c HexBoard.cpp

HexConsoleUI.o:	${hbINC} HexUI.h HexConsoleUI.h HexGameEngine.h HexConsoleUI.cpp
	${CC} -c HexConsoleUI.cpp

ComputerPlayer.o:	${geINC} ComputerPlayer.cpp
	${CC} -c ComputerPlayer.cpp

HexGameEngine.o:	${geINC} HexGameEngine.cpp
	${CC} -c HexGameEngine.cpp

clean:
	rm hex *.o

