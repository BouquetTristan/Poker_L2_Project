# Presentation
This is a project of a poker game, created for 2nd year project of the university of Le Mans.

# How to run without installation ?
1) download and extract archive
2) `cd` at root folder of the extracted archive
3) `make install-sdl` if SDL libraries are not installed yet
4) `./poker` (`chmod +x` if it does not launch)
 
# How to install ?
This will build, copy the game to the desired installation folder
and add shortcuts into your linux distro launcher and desktop
1) launch `./install.sh`
2) click on `poker` icon from your application launcher

# How to uninstall ?
This will remove the installation folder and all the game shortcuts
1) click on `uninstall` icon from your application launcher

# How to build from the sources ?
makefile using :
  - `make help`         (details the list of commands below)
  - `make all`          (compile the game)
  - `make clean`        (remove all `.o` files)
  - `make clean-logs`        (remove the last installation logs from `install_dir.txt`)
  - `make mrproper`		  (call `clean` target + remove the executable `poker`)
  - `make install-sdl`  (install `SDL, SDL_image, SDL_ttf,` and `SDL_mixer` libraries V1.2 via `apt` package manager)

# Development team
POUPIN Romain - BOUQUET Tristan - NJOFFANG William

