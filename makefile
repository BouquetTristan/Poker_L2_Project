# FLAGS
BIN = poker
OBJ = carte.o poker.o jeu.o joueur.o
CC = gcc
CFLAGS = -g -Iinclude
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

# COMMANDES
clean:
	- rm *.o

mrproper: clean
	- rm ${BIN}

install-sdl:
	@echo ""
	@echo "Assurez-vous que :"
	@echo " - le gestionnaire de paquets aptitude soit installé"
	@echo " - d'être connecté à internet"
	@echo ""
	@echo "Pressez [ENTRER] pour continuer, [CRTL+C] pour annuler"
	@echo "" 
	@read key
	sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev libsdl-mixer1.2-dev

help :
	@echo ""
	@echo "make all		- compile le jeu"
	@echo "make clean		- supprime les fichiers *.o"
	@echo "make mrproper		- supprime les fichiers *.o et l'éxécutable"
	@echo "make install-sdl	- installe SDL, SDL_image, SDL_ttf, et SDL_mixer version 1.2 (via apt)"
	@echo "make help		- affiche cette info"
	@echo ""
