cmake_minimum_required(VERSION 3.26)
project(MiniGames)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MiniGames
        .idea/.gitignore
        .idea/MiniGames.iml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        Ressources/Ball/ballon_aqua.bmp
        Ressources/Ball/ballon_bleu.bmp
        Ressources/Ball/ballon_jaune.bmp
        Ressources/Ball/ballon_orange.bmp
        Ressources/Ball/ballon_rouge.bmp
        Ressources/Ball/ballon_vert.bmp
        Ressources/Ball/ballon_violet.bmp
        Ressources/Ball/fond_ballon.bmp
        Ressources/Casino/fondCasino.bmp
        Ressources/Casino/introCasino.bmp
        Ressources/Casino/MancheCasino.bmp
        Ressources/Casino/symboleCasino.bmp
        Ressources/Casino/youLose.bmp
        Ressources/Casino/youWin.bmp
        Ressources/Lobby/changement_de_joueur.bmp
        Ressources/Lobby/Chemin_possible.bmp
        Ressources/Lobby/ECE_World_map.bmp
        Ressources/Lobby/ECE_World_op.bmp
        Ressources/Lobby/personnage.bmp
        Ressources/Oie/contourde.bmp
        Ressources/Oie/dame1.bmp
        Ressources/Oie/elfe1.bmp
        Ressources/Oie/introjeuoie.bmp
        Ressources/Oie/jeudeloie.bmp
        Ressources/Oie/ninja1.bmp
        Ressources/Oie/sorciere2.bmp
        Ressources/Oie/SpriteMagenta.bmp
        ballon.c
        case_memoire.c
        jackpot.c
        jeudeloie.c
        link.h
        main.c
        Ne_pas_toucher_les_bords_electrique.c
        README.md)
