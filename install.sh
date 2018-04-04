#!/bin/bash

#############
# VARIABLES #
#############

# Colors
NC="\e[0m"
ORANGE="\e[33m"
GREEN="\e[92m"
RED="\e[91m"
BOLD="\e[1m"

# Packages
pkg_list=(
    "libsdl1.2-dev"
    "libsdl-image1.2-dev"
    "libsdl-ttf2.0-dev"
    "libsdl-mixer1.2-dev"
)
pkg_install=(0 0 0 0)
pkg_nb=${#pkg_list[@]}
check_valid=1

# Paths, Dirs and Execs
user_path=`echo $HOME`
desktop_name=`cat $user_path/.config/user-dirs.dirs | grep "XDG_DESKTOP_DIR="`
desktop_name=${desktop_name#*=\""$"HOME}
desktop_name=`echo "${desktop_name//\"/}"`
launchers_path="/usr/share/applications/"
launcher_game="pokerpc.desktop"
launcher_uninstall="pokerpc_uninstall.desktop"


#############
# FUNCTIONS #
#############

# vérifie si le paquet passé en paramètre est installé
check_pkg() {
  pkg_installed=0
  echo -n "vérification de "$1"... " 
  install_status=$(dpkg -s $1 2> /dev/null | grep "install ok installed")
  if [ "$install_status" = "" ]
  then
    echo -e $RED"[PAS INSTALLE]$NC"
    pkg_installed=0
  else
    echo -e -n $GREEN"[INSTALLE]$NC\n"
    pkg_installed=1
  fi
}

# installe le paquet passé en paramètre
install_pkg() {
  sudo apt-get -y install $1
}

check_game_installation() {
  if [ -f $launchers_path$launcher_game ]
  then
    game_installed=1
  else
    game_installed=0
  fi
}

# extrait et éxécute la commande de désinstallation du jeu
# depuis le launcher (.desktop)
game_uninstall() {
  cd $launchers_path
  uninstall_cmd=`cat $launcher_uninstall | grep "Exec="`
  uninstall_cmd=`echo "${uninstall_cmd//Exec=/}"`
  echo $uninstall_cmd
  $uninstall_cmd
}


#######################
# INSTALLATION SCRIPT #
#######################

# vérifie si le script est éxécuté dans un terminal
# (requis pour certaines opérations)
if [ -t 1 ]
then
  # vérifie si les paquets requis sont installés
  echo -e $ORANGE"recherche des paquets requis...$NC"
  for ((i=0; i < $pkg_nb; i++)); do
    check_pkg ${pkg_list[$i]}
    if [ $pkg_installed = 0 ]; then
      pkg_install[$i]=1 && check_valid=0
    fi
  done
  
  # propose d'installer les paquets manquants si le check_pkg en a détecter
  if [ $check_valid = 0 ]; then
    zenity  --question \
            --title="Installation paquets" \
            --text="Voulez-vous installer les paquets manquants ?\n\n
            - 'Oui' pour les installer (connexion internet requise)
            - 'Non' si vous êtes sûr qu'ils sont bien installés"
    case $? in
      0)
        #echo -e $BOLD$ORANGE"INSTALLATION DES PAQUETS MANSQUANTS$NC"
        echo -e $ORANGE"mise à jour de la liste des paquets disponibles...$NC"
        sudo apt-get update
        for ((i=0; i < $pkg_nb; i++)); do
          if [ ${pkg_install[$i]} = 1 ]; then
            echo -e $ORANGE"installation de "${pkg_list[$i]}"...$NC"
            install_pkg ${pkg_list[$i]}
          fi
        done ;;
      1) 
        echo -e $RED"ATTENTION : poursuite de l'installation malgré des paquets manquants !$NC" ;;
      -1) zenity --error --text="Une erreur inatendue est survenue." ;;
    esac
  fi

  # vérifie que le jeu n'est pas déjà installé
  check_game_installation
  if [ $game_installed = 1 ]
  then 
    zenity --error --text="Poker est déjà installé ! Veuillez d'abord le désinstaller"
    # propose de désinstaller le logiciel
    zenity  --question \
            --title="Désinstallation" \
            --text="Voulez-vous désinstaller le jeu ?"
    case $? in
      0) game_uninstall ;;
      #1) echo -e "$RED""installation anulée !$NC" ;;
      -1) zenity --error --text="Une erreur inatendue est survenue." ;;
    esac
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
            install_dir=$DIR/poker
            echo -e $ORANGE"création du répertoire d'installation...$NC"
            mkdir $install_dir
            if [ -d "$install_dir" ]; then
              echo -e $ORANGE"copie des fichiers du jeu dans le répertoire d'installation...$NC"
              cp -r * $install_dir
              cd $install_dir
              
              echo -e $ORANGE"sauvegarde du chemin du répertoire d'installation...$NC"
              echo $install_dir > install_dir.txt
              
              echo -e $ORANGE"création du launcher...$NC"
              touch launcher.sh
              echo -e "
              #!/bin/bash\n\n
              cd $install_dir\n
              ./poker" > launcher.sh
              chmod +x launcher.sh

              echo -e $ORANGE"compilation du jeu...$NC"
              make all
              chmod +x poker uninstall.sh
              
              echo -e $ORANGE"ajout du raccourci vers le launcher dans le menu d'applications...$NC "
              touch $launcher_game
              echo -e "
              [Desktop Entry]\n
              Type=Application\n
              Name=Poker PC\n
              Categories=Game\n
              Exec=$install_dir/launcher.sh\n
              Icon=$install_dir/img/jeton_backup.png\n
              Terminal=true" > $launcher_game
              sudo cp $launcher_game /usr/share/applications
              sudo chmod +x /usr/share/applications/$launcher_game
              
              zenity  --question \
                      --title="Raccourci" \
                      --text="Voulez-vous ajouter un raccourci ?"
              case $? in
                0)
                  echo -e $ORANGE"création du raccourci sur le bureau...$NC "
                  sudo cp $launcher_game $user_path$desktop_name
                  sudo chmod +x $user_path$desktop_name/$launcher_game
                  if [ -f "$user_path$desktop_name/$launcher_game" ]
                  then
                    echo $user_path$desktop_name/$launcher_game >> install_dir.txt
                    shortcut=$user_path$desktop_name/$launcher_game  
                  else
                    shortcut_dir=`zenity --file-selection --directory --title="Sélectionnez un emplacement pour le raccourci"`
                    case $? in
                      0)
                        echo -e $ORANGE"création du raccourci dans $shortcut_dir...$NC "
                        sudo cp $launcher_game $shortcut_dir
                        sudo chmod +x $shortcut_dir/$launcher_game
                        echo $shortcut_dir/$launcher_game >> install_dir.txt
                        shortcut=$shortcut_dir/$launcher_game ;;
                      1) zenity --error --text="Aucun emplacement sélectionné : raccourci annulé !";;
                      -1) zenity --error --text="Une erreur inattendue est survenue.";;
                    esac
                  fi
                  ;;
                1) ;;
                -1) zenity --error --text="Une erreur inatendue est survenue.";;
              esac

              echo -e $ORANGE"ajout du raccourci vers le script de désinstallation dans le menu d'applications...$NC "
              touch $launcher_uninstall
              echo -e "
              [Desktop Entry]\n
              Type=Application\n
              Name=Poker PC - Désinstaller\n
              Categories=Game\n
              Exec=$install_dir/uninstall.sh $install_dir $shortcut\n
              Icon=$install_dir/img/uninstall.png\n
              Terminal=true" > $launcher_uninstall
              sudo mv $launcher_uninstall /usr/share/applications
              sudo chmod +x /usr/share/applications/$launcher_uninstall

              echo -e $ORANGE"suppression des fichiers de compilation et d'installation...$NC"
              make clean
              rm -r include src makefile install.sh $launcher_game

              zenity --info --text="L'installation de Poker s'est déroulée avec succès !"
            else
              zenity --error --text="Impossible de créer le répertoire d'installation : arrêt de l'installation !\n
              Essayer de recommencer l'installation avec les droits administrateurs 'sudo ./install.sh'"
            fi;;
          1) zenity --error --text="Aucun emplacement sélectionné : arrêt de l'installation !";;
          -1) zenity --error --text="Une erreur inattendue est survenue.";;
        esac
      ;;
      1) zenity --error --text="Licence refusée : arrêt de l'installation !";;
      -1) zenity --error --text="Une erreur inattendue est survenue.";;
    esac 
  fi
else
  zenity --error --text="Vous devez lancer cet outil dans un terminal !"    
fi
