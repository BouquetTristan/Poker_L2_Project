# Presentation
This is a project of a poker game, created for 2nd year project of the university of Le Mans.

# How to run without installation ?
1) download and extract archive
2) *cd* at root folder of the extracted archive
3) *make install-sdl* if SDL libraries are not installed yet
4) *./poker* (*chmod +x* if it does not launch)
 
# How to install ?
This will build and copy the entire game to the desired installation folder
1) right click on *install.sh* > "open in terminal" (OR *./install.sh* from terminal)
2) double click on *poker* (OR *./poker* from terminal)

# How to uninstall ?
This will remove the installation folder
1) right click on *uninstall.sh* > "open in terminal" (OR *./uninstall.sh* from terminal)

# How to build from the sources ?
1) makefile using :
  - *make help*         (details the list of commands below)
  - *make all*          (compile the game)
  - *make clean*        (remove all \*.o)
  - *make clean-logs*        (remove last installation logs from *install_logs.txt*)
  - *make mrproper*		  (remove all \*.o + the executable)
  - *make install-sdl*  (install *SDL*, *SDL_image*, *SDL_ttf*, and *SDL_mixer* libraries v1.2 via *apt* package manager)
2) *./poker*

Development team : BOUQUET Tristan - POUPIN Romain - NJOFFANG William

