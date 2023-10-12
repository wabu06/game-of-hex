CC = clang++ -std=gnu++17
#CC = clang++ -std=gnu++17 -g -O0
#CC = g++


hpINC = graph.h MinPQ.h dPath.h bfs.h dfs.h HexPlayer.h
#hbINC = ${hpINC} HexBoard.h
hbINC = HexBoard.h
geINC = ${hpINC} HexBoard.h HexExecutor.h HexConsoleExec.h HexCurseExec.h HexGameEngine.h

OBJs = main.o dPath.o HexBoard.o HexExecutor.o HexConsoleExec.o HexCurseExec.o ComputerPlayer.o HexGameEngine.o

all: hex

hex:	${OBJs}
	${CC} ${OBJs} -o hex -lncurses

main.o: ${geINC} main.cpp
	${CC} -c main.cpp

dPath.o: graph.h MinPQ.h dPath.h dPath.cpp
		${CC} -c dPath.cpp

HexBoard.o:	${hbINC} HexBoard.cpp
	${CC} -c HexBoard.cpp

HexExecutor.o:	HexExecutor.h HexGameEngine.h HexExecutor.cpp
	${CC} -c HexExecutor.cpp

HexConsoleExec.o:	${hpINC} ${hbINC} HexExecutor.h HexConsoleExec.h HexGameEngine.h HexConsoleExec.cpp
	${CC} -c HexConsoleExec.cpp

HexCurseExec.o:	${hpINC} ${hbINC} HexExecutor.h HexCurseExec.h HexGameEngine.h HexCurseExec.cpp
	${CC} -c HexCurseExec.cpp

ComputerPlayer.o:	${geINC} ComputerPlayer.cpp
	${CC} -c ComputerPlayer.cpp

HexGameEngine.o:	${geINC} HexGameEngine.cpp
	${CC} -c HexGameEngine.cpp

clean:
	rm hex *.o

