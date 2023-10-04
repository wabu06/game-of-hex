CC = clang++ -std=gnu++17
#CC = clang++ -std=gnu++17 -g -O0
#CC = g++


hpINC = graph.h MinPQ.h dPath.h bfs.h dfs.h HexPlayer.h
#hbINC = ${hpINC} HexBoard.h
hbINC = HexBoard.h HexGameEngine.h
geINC = ${hpINC} HexBoard.h HexUI.h HexConsoleUI.h HexCurseUI.h HexGameEngine.h

OBJs = main.o dPath.o HexBoard.o ComputerPlayer.o HexConsoleUI.o HexCurseUI.o HexGameEngine.o

all: hex

hex:	${OBJs}
	${CC} ${OBJs} -o hex -lncurses

main.o: ${geINC} main.cpp
	${CC} -c main.cpp

dPath.o: graph.h MinPQ.h dPath.h dPath.cpp
		${CC} -c dPath.cpp

HexBoard.o:	${hbINC} HexBoard.cpp
	${CC} -c HexBoard.cpp

HexConsoleUI.o:	HexUI.h HexConsoleUI.h HexGameEngine.h HexConsoleUI.cpp
	${CC} -c HexConsoleUI.cpp

HexCurseUI.o:	HexUI.h HexCurseUI.h HexGameEngine.h HexCurseUI.cpp
	${CC} -c HexCurseUI.cpp

ComputerPlayer.o:	${geINC} ComputerPlayer.cpp
	${CC} -c ComputerPlayer.cpp

HexGameEngine.o:	${geINC} HexGameEngine.cpp
	${CC} -c HexGameEngine.cpp

clean:
	rm hex *.o

