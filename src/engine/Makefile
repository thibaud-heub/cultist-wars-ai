CC = gcc
CCFLAGS = -Wall -g

all: Game_Engine game.o 

game.o: game.c game.h game_types.h
	${CC} ${CCFLAGS} -c game.c

Game_Engine: Game_Engine.c game.c game.h game_types.h
	${CC} ${CCFLAGS} -o Game_Engine Game_Engine.c game.c

#autoconf
#automake