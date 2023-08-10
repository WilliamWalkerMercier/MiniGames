#ifndef PROJET_LINK_H
#define PROJET_LINK_H

#endif //PROJET_LINK_H



//Define
#define MAX_PSEUDO 40


//Libraries-----------------------------------------------------------
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Structure------------------------------------------------------------

typedef struct ImageCoordinates{
    int PosX;
    int PosY;
}sImgCoordinates;

typedef struct Player{
    int NbOfTickets;
    char Username[MAX_PSEUDO];
    int Goose;
    int Lightning;
    int Memory;
    int Ball;
    int CasinoRoyal;
}sPlayer;

typedef struct PlayerCoordinates{
    int posX;
    int posY;
    BITMAP *image;
}sPlayerCoordinates;

typedef struct Character{
    BITMAP* Down[4];
    BITMAP* Left[4];
    BITMAP* Right[4];
    BITMAP* UP[4];
    int x, y;
    int direction;
    int frame;
    int Moving;
}sCharacter;




//Prototype-----------------------------------------------------------
void AllegroInitialisation();
void SplitCharacterBitmap(sCharacter* personnage, BITMAP* bitmap);
void DrawCharacter(sCharacter* personnage, BITMAP* buffer);
void CharacterUpdate(sCharacter* personnage, BITMAP *Chemin_joueur_possible);
void UsernameInput(char *pseudo);


    //Jackpot
    void jackpot(sPlayer* joueur, int tour);

    //Jeu de l'oie
    void jeudeloie(sPlayer* joueur);
    void verifieCase(sPlayerCoordinates* prJoueur1, sPlayerCoordinates*prJoueur2);
    void verifieDeplacement(sPlayerCoordinates* prJoueur, int de);

    //Ballon
    int jeu_ballon();

    //Snake
    void jeu_Snake(sPlayer* joueur);


    //Ne pas toucher les bords
    void jeu_ne_pas_toucher_les_bords_electrique(sPlayer* joueur);

    //Memory
    int jeu_de_memoire();

    //Guitar Hero
    int jeu_Guitar();

    //Jeu de la fortune
    int jeu_RoueFor();


/*
 Jeu gardé:
    -Casino
    -Ballon
    -Oie
    -Electricite
    -Memory
 */
