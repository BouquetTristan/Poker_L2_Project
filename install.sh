#!/bin/sh

NC="\033[0m" # no color
ORANGE="\033[0;33m" # orange color

if [ -t 1 ]
then
  installdir=$(head -n 1 install_dir.txt)
  if [ -d "$installdir" ]
  then 
    zenity --error --text="Poker est déjà installé ! Tapez d'abord ./uninstall"
  else
    FILE=LICENSE
    zenity --text-info \
           --title="Licence" \
           --filename=$FILE \
           --checkbox="J'ai lu et j'accepte les termes." \
           --height=500 \
           --width=450

    case $? in
      0)
        DIR=`zenity --file-selection --directory --title="Sélectionnez un emplacement où le dossier d'installation va être créé"`
        case $? in
          0)
            zenity  --question \
                    --title="SDL installation" \
                    --text="Voulez-vous installer les bibliothèques SDL ?\n\nPrérequis :\n- gestionnaire de paquet aptitude\n- connexion internet"
            case $? in
              0) sdl_flag="1";;
              1) sdl_flag="0";;
              -1) zenity --error --text="Une erreur inatendue est survenue.";;
            esac

            if [ "$sdl_flag" = "1" ]
            then
              echo "$ORANGE* INSTALLATION DES LIBRAIRIES SDL *$NC"
              make install-sdl
            fi
            
            echo "$ORANGE* CREATION DU REPERTOIRE DE DESTINATION *$NC"
            mkdir $DIR/poker

            echo "$ORANGE* COPIE DES FICHIERS DU JEU DANS LE REPERTOIRE DE DESTINATION *$NC"
            cp -r * $DIR/poker
            cd $DIR/poker
            
            echo "$ORANGE* ENREGISTREMENT DU CHEMIN DE DESINATION *$NC"
            install_dir=`pwd`
            echo $install_dir > install_dir.txt
            
            echo "$ORANGE* CONFIGURATION DES CHEMINS ABSOLUS DANS LE FICHIER \"commun.h\" *$NC"
            file="include/commun.h"
            rm $file
            touch $file
            echo "#ifndef _COMMUN_H_" > $file
            echo "#define _COMMUN_H_" >> $file
            echo "#include <stdio.h>" >> $file
            echo "#include <stdlib.h>" >> $file
            echo "#include <string.h>" >> $file
            echo "" >> $file
            echo "// tailles des objets" >> $file
            echo "#define N 52 // jeu de cartes" >> $file
            echo "#define LARGEUR_FENETRE 1280" >> $file
            echo "#define HAUTEUR_FENETRE 720" >> $file
            echo "#define LARGEUR_CARTE 112" >> $file
            echo "#define HAUTEUR_CARTE 156" >> $file
            echo "" >> $file
            echo "// textures" >> $file
            echo "#define JETON \""$install_dir"/img/jeton_70.png\"" >> $file
            echo "#define HOME_WALL \""$install_dir"/img/red_wall.jpg\"" >> $file
            echo "#define TABLE \""$install_dir"/img/table_top.png\"" >> $file
            echo "#define JEU_52_CARTES \""$install_dir"/img/52_cards_deck.png\"" >> $file
            echo "#define VERSO_CARTE \""$install_dir"/img/back_card_red2.png\"" >> $file
            echo "" >> $file
            echo "// sons" >> $file
            echo "#define HOME_MUSIC \""$install_dir"/sound/Song_Remains_The_Same.wav\"" >> $file
            echo "#define IN_GAME_MUSIC \""$install_dir"/sound/No_Quarter.wav\"" >> $file
            echo "#define MOVE_CURSOR \""$install_dir"/sound/chipsStack1.wav\"" >> $file
            echo "#define BACK \""$install_dir"/sound/cardTakeOutPackage1.wav\"" >> $file
            echo "" >> $file
            echo "// polices" >> $file
            echo "#define MENU_FONT \""$install_dir"/font/PokerKings-Regular.ttf\"" >> $file
            echo "" >> $file
            echo "#endif" >> $file

            echo "$ORANGE* COMPILATION DU JEU *$NC"
            make all
            chmod +x poker uninstall.sh

            zenity  --question \
                    --title="Raccourci" \
                    --text="Voulez-vous ajouter un raccourci ?"
            case $? in
              0) shortcut_flag="1";;
              1) shortcut_flag="0";;
              -1) zenity --error --text="Une erreur inatendue est survenue.";;
            esac

            if [ "$shortcut_flag" -eq "1" ]
            then
              desktop_dir=`zenity --file-selection --directory --title="Sélectionnez un emplacement pour le raccourci"`
              case $? in
                0)
                  echo "$ORANGE* CREATION DU RACCOURCI SUR LE BUREAU *$NC"
                  ln -s $install_dir"/poker" $desktop_dir"/Poker"
                  echo $desktop_dir"/Poker" >> install_dir.txt
                  shortcut=$desktop_dir"/Poker" ;;
                1) zenity --error --text="Aucun fichier sélectionné.";;
                -1) zenity --error --text="Une erreur inattendue est survenue.";;
              esac
            fi
            
            echo "$ORANGE* INTEGRATION DU JEU DANS LE MENU D'APPLICATIONS *$NC "
            entry=~/.local/share/applications/pokerpc.desktop
            touch $entry
            echo "#!/usr/bin/env xdg-open" > $entry
            echo "[Desktop Entry]" >> $entry
            echo "Type=Application" >> $entry
            echo "Name=Poker PC" >> $entry
            echo "Categories=Game" >> $entry
            echo "Exec="$install_dir"/poker" >> $entry
            echo "Icon="$install_dir"/img/jeton_backup.png" >> $entry
            echo "Terminal=true" >> $entry
            chmod +x $entry

            entry=~/.local/share/applications/pokerpc_uninstall.desktop
            touch $entry
            echo "#!/usr/bin/env xdg-open" > $entry
            echo "[Desktop Entry]" >> $entry
            echo "Type=Application" >> $entry
            echo "Name=Poker PC - Désinstaller" >> $entry
            echo "Categories=Game" >> $entry
            echo "Exec="$install_dir"/uninstall.sh "$install_dir" "$shortcut >> $entry
            echo "Icon="$install_dir"/img/uninstall.png" >> $entry
            echo "Terminal=true" >> $entry
            chmod +x $entry

            echo "$ORANGE* NETTOYAGE DES FICHIERS DE COMPILATION ET D'INSTALLATION *$NC"
            make clean
            rm -r include src makefile install.sh

            zenity --info --text="L'installation de Poker s'est déroulée avec succès !"
            ;;
          1) zenity --error --text="Aucun fichier sélectionné.";;
          -1) zenity --error --text="Une erreur inattendue est survenue.";;
        esac
      ;;
      1) zenity --error --text="Arrêt de l'installation !";;
      -1) zenity --error --text="Une erreur inattendue est survenue.";;
    esac 
  fi
else
  zenity --error --text="Vous devez lancer cet outil dans un terminal !"    
fi