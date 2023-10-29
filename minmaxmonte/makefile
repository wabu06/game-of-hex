CC = clang++ -std=gnu++17
#CC = clang++ -std=gnu++17 -g -O0
#CC = g++

BIN = bin

hpINC = graph.h MinPQ.h dPath.h bfs.h dfs.h HexPlayer.h
#hbINC = ${hpINC} HexBoard.h
hbINC = HexBoard.h
geINC = ${hpINC} HexBoard.h HexConsoleUI.h HexCurseUI.h HexGameEngine.h

OBJs = ${BIN}/main.o ${BIN}/dPath.o ${BIN}/HexBoard.o ${BIN}/HexConsoleUI.o ${BIN}/HexCurseUI.o ${BIN}/HexGameApp.o ${BIN}/ComputerPlayer.o ${BIN}/HexGameEngine.o

all: ${BIN}/hex

${BIN}/hex:	${OBJs}
	${CC} ${OBJs} -o ${BIN}/hex -lncurses

${BIN}/main.o: ${geINC} main.cpp
	${CC} -c main.cpp -o ${BIN}/main.o

${BIN}/dPath.o: graph.h MinPQ.h dPath.h dPath.cpp
		${CC} -c dPath.cpp -o ${BIN}/dPath.o

${BIN}/HexBoard.o:	${hbINC} HexBoard.cpp
	${CC} -c HexBoard.cpp -o ${BIN}/HexBoard.o

${BIN}/HexGameApp.o:	${hpINC} ${hbINC} HexGameApp.h HexGameEngine.h HexGameApp.cpp
	${CC} -c HexGameApp.cpp -o ${BIN}/HexGameApp.o

${BIN}/HexConsoleUI.o:	${hpINC} ${hbINC} HexUI.h HexConsoleUI.h HexGameEngine.h HexConsoleUI.cpp
	${CC} -c HexConsoleUI.cpp -o ${BIN}/HexConsoleUI.o

${BIN}/HexCurseUI.o:	${hpINC} ${hbINC} HexUI.h HexCurseUI.h HexGameEngine.h HexCurseUI.cpp
	${CC} -c HexCurseUI.cpp -o ${BIN}/HexCurseUI.o

${BIN}/ComputerPlayer.o:	${geINC} ComputerPlayer.cpp
	${CC} -c ComputerPlayer.cpp -o ${BIN}/ComputerPlayer.o

${BIN}/HexGameEngine.o:	${geINC} HexGameEngine.cpp
	${CC} -c HexGameEngine.cpp -o ${BIN}/HexGameEngine.o

clean:
	rm ${BIN}/*

