#!/bin/sh

installdir=$(head -n 1 install_logs.txt)
if [ -d "$installdir" ]
then 
	zenity --question \
       	--title="Désinstallation de Poker" \
      	--text="Voulez-vous vraiment désinstaller Poker ?"
	case $? in
		0)
			sudo rm -r $installdir
			if [ -d "$installdir"]
			then
				zenity --error --text="La désinstallation de Poker a échouée !"  				
			else
				zenity --info --text="Poker est désormais désinstallé !"
			fi;;
		1);;
		-1) zenity --error --text="Une erreur inatendue est survenue.";;
	esac
else
  zenity --error --text="Poker n'est pas installé ou à déjà été désinstallé ! Tapez d'abord ./install"  
fi
