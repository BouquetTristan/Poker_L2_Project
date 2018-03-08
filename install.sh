#!/bin/sh

if [ -t 1 ]
then
  installdir=$(head -n 1 install_logs.txt)
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
        DIR=`zenity --file-selection --directory --title="Sélectionnez un dossier d'installation pour Poker"`
        case $? in
          0)
            echo $DIR > install_logs.txt
            
            zenity  --question \
                    --title="SDL installation" \
                    --text="Voulez-vous installer les bibliothèques SDL ?"
            case $? in
              0) make install-sdl >> install_logs.txt;;
              1) echo "refus installation SDL." >> install_logs.txt;;
              -1) zenity --error --text="Une erreur inatendue est survenue.";;
            esac

            make all >> install_logs.txt
            make clean >> install_logs.txt
            sudo cp -r * $DIR
            #pwd=`pwd`
            cd $DIR
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