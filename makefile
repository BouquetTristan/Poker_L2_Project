BIN = poker
OBJ = carte.o poker.o jeu.o
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

clean:
	- rm *.o
	- rm ${BIN}
