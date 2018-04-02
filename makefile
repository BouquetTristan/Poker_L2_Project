# FLAGS
BIN = poker
OBJ = carte.o poker.o jeu.o joueur.o mise.o partie.o gui.o
SRC_DIR = src/
INC_DIR = include/
CC = gcc
CFLAGS = -g -W -I${INC_DIR}
SDLFLAGS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer


# MODULES
all: ${BIN}

${BIN}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${BIN} ${SDLFLAGS}

carte.o: ${SRC_DIR}carte.c
	${CC} ${CFLAGS} -c ${SRC_DIR}carte.c

poker.o: ${SRC_DIR}poker.c
	${CC} ${CFLAGS} -c ${SRC_DIR}poker.c

jeu.o: ${SRC_DIR}jeu.c
	${CC} ${CFLAGS} -c ${SRC_DIR}jeu.c

joueur.o: ${SRC_DIR}joueur.c
	${CC} ${CFLAGS} -c ${SRC_DIR}joueur.c

gui.o: ${SRC_DIR}gui.c
	${CC} ${CFLAGS} -c ${SRC_DIR}gui.c

mise.o: ${SRC_DIR}mise.c
	${CC} ${CFLAGS} -c ${SRC_DIR}mise.c

partie.o: ${SRC_DIR}partie.c
	${CC} ${CFLAGS} -c ${SRC_DIR}partie.c


# TARGETS
clean-logs:
	@echo "" > install_dir.txt

clean:
	- rm *.o

mrproper: clean
	- rm ${BIN}

install-sdl:
	sudo apt-get -y update && sudo apt-get -y install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl-mixer1.2-dev

uninstall-sdl:
	sudo apt-get -y remove libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl-mixer1.2-dev

help:
	@echo ""
	@echo "make all		- compile le jeu"
	@echo "make clean		- supprime les fichiers *.o"
	@echo "make clean-logs		- efface les logs du fichier 'install_dir.txt'"
	@echo "make mrproper		- supprime les fichiers *.o et l'éxécutable"
	@echo "make install-sdl	- installe SDL V1.2, SDL_image, SDL_ttf, et SDL_mixer (via apt)"
	@echo "make uninstall-sdl	- désinstalle les librairies SDL ci-dessus"
	@echo "make help		- affiche cette info"
	@echo ""
