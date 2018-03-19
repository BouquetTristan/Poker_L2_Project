# Presentation
This is a project of a poker game, created for 2nd year project of the university of Le Mans.

# How to run without installation ?
1) download and extract archive
2) *cd* at root folder of the extracted archive
3) *make install-sdl* if SDL libraries are not installed
4) *./poker* (*chmod +x* if it does not launch)
 
# How to install ?
This will rebuild the executable and copy the entire game to an installation folder
1) right click on *install.sh* > "open in terminal" (OR enter : *./install.sh* from a terminal)
2) double click on *poker* (OR enter *./poker* from a terminal)

# How to uninstall ?
This will remove the installation folder
1) right click on *uninstall.sh* > "open in terminal" (OR enter : *./uninstall.sh* from a terminal)

# How to build from the sources ?
1) makefile using :
  - *make help*         (details the list of commands below)
  - *make all*          (compile the game)
  - *make clean*        (remove all \*.o)
  - *make clean-logs*        (remove installation logs in *install_logs.txt*)
  - *make mrproper*		  (remove all \*.o + the executable)
  - *make install-sdl*  (install *SDL*, *SDL_image*, *SDL_ttf*, and *SDL_mixer* libraries v1.2 via *apt* package manager)
4) *./poker*

Developement team : BOUQUET Tristan - POUPIN Romain - NJOFFANG William

