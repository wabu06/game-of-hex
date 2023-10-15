CC = clang++ -std=gnu++17
#CC = clang++ -std=gnu++17 -g -O0
#CC = g++

BIN = bin

hpINC = graph.h MinPQ.h dPath.h bfs.h dfs.h HexPlayer.h
#hbINC = ${hpINC} HexBoard.h
hbINC = HexBoard.h
geINC = ${hpINC} HexBoard.h HexExecutor.h HexConsoleExe.h HexCurseExe.h HexGameEngine.h

OBJs = ${BIN}/main.o ${BIN}/dPath.o ${BIN}/HexBoard.o ${BIN}/HexExecutor.o ${BIN}/HexConsoleExe.o ${BIN}/HexCurseExe.o ${BIN}/ComputerPlayer.o ${BIN}/HexGameEngine.o

all: ${BIN}/hex

${BIN}/hex:	${OBJs}
	${CC} ${OBJs} -o ${BIN}/hex -lncurses

${BIN}/main.o: ${geINC} main.cpp
	${CC} -c main.cpp -o ${BIN}/main.o

${BIN}/dPath.o: graph.h MinPQ.h dPath.h dPath.cpp
		${CC} -c dPath.cpp -o ${BIN}/dPath.o

${BIN}/HexBoard.o:	${hbINC} HexBoard.cpp
	${CC} -c HexBoard.cpp -o ${BIN}/HexBoard.o

${BIN}/HexExecutor.o:	${hpINC} ${hbINC} HexExecutor.h HexGameEngine.h HexExecutor.cpp
	${CC} -c HexExecutor.cpp -o ${BIN}/HexExecutor.o

${BIN}/HexConsoleExe.o:	${hpINC} ${hbINC} HexExecutor.h HexConsoleExe.h HexGameEngine.h HexConsoleExe.cpp
	${CC} -c HexConsoleExe.cpp -o ${BIN}/HexConsoleExe.o

${BIN}/HexCurseExe.o:	${hpINC} ${hbINC} HexExecutor.h HexCurseExe.h HexGameEngine.h HexCurseExe.cpp
	${CC} -c HexCurseExe.cpp -o ${BIN}/HexCurseExe.o

${BIN}/ComputerPlayer.o:	${geINC} ComputerPlayer.cpp
	${CC} -c ComputerPlayer.cpp -o ${BIN}/ComputerPlayer.o

${BIN}/HexGameEngine.o:	${geINC} HexGameEngine.cpp
	${CC} -c HexGameEngine.cpp -o ${BIN}/HexGameEngine.o

clean:
	rm ${BIN}/*

