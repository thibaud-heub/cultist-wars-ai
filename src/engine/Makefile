CC = gcc
CCFLAGS = -Wall -g

all: game_engine game.o 

game.o: game.c game.h game_types.h
	${CC} ${CCFLAGS} -c game.c

game_engine: game_engine.c game.c game.h game_types.h
	${CC} ${CCFLAGS} -o game_engine game_engine.c game.c

#autoconf
#automake