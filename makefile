BIN = poker
OBJ = carte.o poker.o jeu.o joueur.o mise.o
CC = gcc
CFLAGS = -g -Iinclude

all: ${BIN}

${BIN}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${BIN}

carte.o: carte.c
	${CC} ${CFLAGS} -c carte.c

poker.o: poker.c
	${CC} ${CFLAGS} -c poker.c

jeu.o: jeu.c
	${CC} ${CFLAGS} -c jeu.c

joueur.o: joueur.c
	${CC} ${CFLAGS} -c joueur.c

mise.o: mise.c
	${CC} ${CFLAGS} -c mise.c

clean:
	- rm *.o

mrproper: clean
	- rm ${BIN}
