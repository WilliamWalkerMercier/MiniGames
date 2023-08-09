
//
// Created by Moi on 27/04/2023.
//

#ifndef PROJET_LINK_H
#define PROJET_LINK_H

#endif //PROJET_LINK_H
#define MAX_PSEUDO 40
//Librairie-----------------------------------------------------------
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Structure-------------------------------------------------------
typedef struct ImageCoordonnees{
    int indexImage;
    int PosX;
    int PosY;
}sImgCoordonnees;

typedef struct joueur{
    int ticket_j1;
    int ticket_j2;
    char pseudo_j1[MAX_PSEUDO];
    char pseudo_j2[MAX_PSEUDO];
    int Oie_j1, Oie_j2;
    int Eclaire_j1, Eclaire_j2;
    int Snake_j1, Snake_j2;
    int Memoire_j1, Memoire_j2;
    int ballon_j1, ballon_j2;
    int Jackpot_j1, Jackpot_j2;
    int RoueF_j1, RoueF_j2;
    int Guitar_j1, Guitar_j2;
}t_joueur;

typedef struct JoueurCoordonnees{
    int posX;
    int posY;
    BITMAP *image;
}sJoueurCoordonnees;

typedef struct personnage{
    BITMAP* bas[4];
    BITMAP* gauche[4];
    BITMAP* droite[4];
    BITMAP* haut[4];
    int x, y;
    int direction;
    int frame;
    int en_deplacement;
}t_personnage;


//Prototype-----------------------------------------------------------
void initialisation_allegro();
void separer_bitmap_personnage(t_personnage* personnage, BITMAP* bitmap);
void dessiner_personnage(t_personnage* personnage, BITMAP* buffer);


    //Jackpot
    void jackpot(t_joueur* joueur,int tour);

    //Jeu de l'oie
    void jeudeloie(t_joueur* joueur);
    void verifieCase(sJoueurCoordonnees* prJoueur1,sJoueurCoordonnees*prJoueur2);
    void verifieDeplacement(sJoueurCoordonnees* prJoueur,int de);

    //Ballon
    int jeu_ballon();

    //Snake
    void jeu_Snake(t_joueur* joueur);


    //Ne pas toucher les bords
    void jeu_ne_pas_toucher_les_bords_electrique(t_joueur* joueur);

    //Memory
    int jeu_de_memoire();

    //Guitar Hero
    int jeu_Guitar();

    //Jeu de la fortune
    int jeu_RoueFor();



