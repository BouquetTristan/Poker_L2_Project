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
                    --text="Voulez-vous installer les bibliothèques SDL ?"
            case $? in
              0) sdl_flag="1";;
              1) sdl_fglag="0";;
              -1) zenity --error --text="Une erreur inatendue est survenue.";;
            esac

            if [ "$sdl_flag" -eq "1" ]
            then
              echo "$ORANGE* Installation des librairies SDL *$NC"
              make install-sdl
            fi
            echo "$ORANGE* Compilation *$NC"
            make all
            echo "$ORANGE* Netoyage des fichiers temporaires de compilation *$NC"
            make clean
            echo "$ORANGE* Création du répertoire de destination *$NC"
            sudo mkdir $DIR/poker
            echo "$ORANGE* Sauvegarde du chemin du répertoire de destination *$NC"
            echo $DIR"/poker" > install_dir.txt
            echo "$ORANGE* Copie des fichiers du jeu dans le répertoire de destination *$NC"
            sudo cp -r * $DIR/poker
            #pwd=`pwd`
            cd $DIR/poker
            echo "$ORANGE* Droit d'accès total aux fichiers du jeu *$NC"
            sudo chmod 777 *
            #sudo rm -r $pwd
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