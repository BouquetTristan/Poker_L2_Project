# FLAGS
BIN = poker
OBJ = carte.o poker.o jeu.o joueur.o gui.o
CC = gcc
CFLAGS = -g -Iinclude -W
SDLFLAGS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer


# MODULES
all: ${BIN}

${BIN}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${BIN} ${SDLFLAGS}

carte.o: carte.c
	${CC} ${CFLAGS} -c carte.c

poker.o: poker.c
	${CC} ${CFLAGS} -c poker.c

jeu.o: jeu.c
	${CC} ${CFLAGS} -c jeu.c

joueur.o: joueur.c
	${CC} ${CFLAGS} -c joueur.c

gui.o: gui.c
	${CC} ${CFLAGS} -c gui.c


# COMMANDS
clean-logs:
	@echo "" > install_dir.txt

clean:
	- rm *.o

mrproper: clean
	- rm ${BIN}

install-sdl:
	sudo apt-get -y update
	sudo apt-get -y install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl-mixer1.2-dev

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
