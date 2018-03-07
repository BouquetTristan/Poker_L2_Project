# FLAGS
BIN = poker
OBJ = carte.o poker.o jeu.o joueur.o
CC = gcc
CFLAGS = -g -Iinclude
SDLFLAGS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
OK_COLOR = "\e[1m"

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

# COMMANDS
install:
	@if !(test -d "/usr/games"); then\
		echo "Creation du repertoire "'"games"'" dans "'"/usr"'""; \
		sudo mkdir /usr/games; \
	fi
	@if !(test -d "/usr/games/poker"); then \
		echo "\033[0;33m* Installation de SDL V1.2 et des librairies SDL_image, mixer et ttf *\033[0m"; \
		make install-sdl; \
		echo "\033[0;33m* Compilation du jeu *\033[0m"; \
		make all; \
		echo "\033[0;33m* Suppression des fichiers temporaires de compilation *\033[0m"; \
		make clean; \
		echo "\033[0;33m* Deplacement du jeu vers "'"/usr/games/poker"'" *\033[0m"; \
		sudo mkdir /usr/games/poker; \
		sudo cp -r * /usr/games/poker; \
		sudo chmod 777 /usr/games/poker/poker; \
		echo "\n\033[1;32m* INSTALLATION TERMINEE ! *\033[0m\n"; \
	else \
		echo "\n\033[1;31m* Poker est deja installe, tapez "'"make uninstall"'" d'abord. *\033[0m\n"; \
	fi

uninstall:
	@if !(test -d "/usr/games/poker"); then \
		echo "\n\033[1;31m* Impossible de desinstaller Poker car le dossier du jeu est absent ! *\033[0m\n"; \
	else \
		sudo rm -r /usr/games/poker; \
		echo "\n\033[1;32m* DESINSTALLATION TERMINEE ! *\033[0m\n"; \
	fi

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
	@echo "make install-sdl	- installe SDL V1.2, SDL_image, SDL_ttf, et SDL_mixer (via apt)"
	@echo "make install		- installe le jeu"
	@echo "make uninstall		- desinstalle le jeu"
	@echo "make help		- affiche cette info"
	@echo ""
