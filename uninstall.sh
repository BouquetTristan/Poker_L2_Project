#!/bin/sh

# Colors
NC="\033[0m"
ORANGE="\033[33m"

if [ -t 1 ]
then
	install_dir=$(cat install_dir.txt | sed -n 1p)
	shortcut=$(cat install_dir.txt | sed -n 2p)
	# si le script est appellé depuis le menu d'applications
	if [ "$install_dir" = "" ]
	then
		install_dir=$1
		shortcut=$2
	fi
	if [ "$1" = "" ] && ["$install_dir" = ""]
	then
		zenity --error --text="Le fichier 'install_dir.txt' est absent ou vide !"  	
	else
		if [ -d "$install_dir" ]
		then 
			zenity --question \
		       	--title="Désinstallation de Poker" \
		      	--text="Voulez-vous vraiment désinstaller Poker ?"
			case $? in
				0)
					echo "$ORANGE* SUPPRESSION DU DOSSIER D'INSTALLATION DU JEU *$NC"
					sudo rm -r $install_dir
					echo "$ORANGE* SUPPRESSION DES RACCOURCIS DU JEU *$NC"
					sudo rm $shortcut /usr/share/applications/pokerpc.desktop /usr/share/applications/pokerpc_uninstall.desktop
					zenity --info --text="Poker est désormais désinstallé !"
					;;
				1);;
				-1) zenity --error --text="Une erreur inatendue est survenue.";;
			esac
		else
			zenity --error --text="Poker n'est pas installé ou à déjà été désinstallé ! Tapez d'abord ./install"  
			make clean-logs
		fi
	fi
else
	zenity --error --text="Vous devez lancer cet outil dans un terminal !"  	
fi
