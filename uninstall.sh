#!/bin/sh

NC="\033[0m" # no color
ORANGE="\033[0;33m" # orange color

if [ -t 1 ]
then
	installdir=$(cat install_dir.txt | sed -n 1p)
	pok=$(cat install_dir.txt | sed -n 2p)
	
	# si le script est appellé depuis le menu d'applications
	if [ "$installdir" = "" ]
	then
		installdir=$1
		pok=$2
	fi

	if [ -d "$installdir" ]
	then 
		zenity --question \
	       	--title="Désinstallation de Poker" \
	      	--text="Voulez-vous vraiment désinstaller Poker ?"
		case $? in
			0)
				echo "$ORANGE* SUPPRESSION DU DOSSIER D'INSTALLATION DU JEU *$NC"
				rm -r $installdir
				if [ -d "$installdir"]
				then
					zenity --error --text="La désinstallation de Poker a échouée !"  				
				else
					echo "$ORANGE* SUPPRESSION DES RACCOURCIS SUR LE BUREAU ET DU MENU D'APPLICATIONS *$NC"
					rm $pok ~/.local/share/applications/pokerpc.desktop ~/.local/share/applications/pokerpc_uninstall.desktop
					zenity --info --text="Poker est désormais désinstallé !"
				fi;;
			1);;
			-1) zenity --error --text="Une erreur inatendue est survenue.";;
		esac
	else
		zenity --error --text="Poker n'est pas installé ou à déjà été désinstallé ! Tapez d'abord ./install"  
		make clean-logs
	fi
else
	zenity --error --text="Vous devez lancer cet outil dans un terminal !"  	
fi