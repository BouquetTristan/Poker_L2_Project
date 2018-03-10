#!/bin/sh

NC="\033[0m" # no color
ORANGE="\033[0;33m" # orange color

if [ -t 1 ]
then
	installdir=$(head -n 1 install_dir.txt)
	if [ -d "$installdir" ]
	then 
		zenity --question \
	       	--title="Désinstallation de Poker" \
	      	--text="Voulez-vous vraiment désinstaller Poker ?"
		case $? in
			0)
				echo "$ORANGE* suppression du dossier d'installation du jeu *$NC"
				sudo rm -r $installdir
				if [ -d "$installdir"]
				then
					zenity --error --text="La désinstallation de Poker a échouée !"  				
				else
					make clean-logs
					zenity --info --text="Poker est désormais désinstallé !"
				fi;;
			1);;
			-1) zenity --error --text="Une erreur inatendue est survenue.";;
		esac
	else
	  zenity --error --text="Poker n'est pas installé ou à déjà été désinstallé ! Tapez d'abord ./install"  
	fi
else
	zenity --error --text="Vous devez lancer cet outil dans un terminal !"  	
fi