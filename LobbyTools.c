#include "link.h"

//Sous-programmes
void separer_bitmap_personnage(sCharacter* personnage, BITMAP* bitmap)
{
    for (int j = 0; j < 4; j++) {
        personnage->bas[j] = create_sub_bitmap(bitmap, j * bitmap->w/4, 0 * bitmap->h/4, bitmap->w/4, bitmap->h/4);
        personnage->gauche[j] = create_sub_bitmap(bitmap, j * bitmap->w/4, 1 * bitmap->h/4, bitmap->w/4, bitmap->h/4);
        personnage->droite[j] = create_sub_bitmap(bitmap, j * bitmap->w/4, 2 * bitmap->h/4, bitmap->w/4, bitmap->h/4);
        personnage->haut[j] = create_sub_bitmap(bitmap, j * bitmap->w/4, 3 * bitmap->h/4, bitmap->w/4, bitmap->h/4);
    }
}

void dessiner_personnage(sCharacter* personnage, BITMAP* buffer){
    BITMAP* frame;
    switch (personnage->direction) {
        case 0:
            frame = personnage->bas[personnage->frame];
            break;
        case 1:
            frame = personnage->gauche[personnage->frame];
            break;
        case 2:
            frame = personnage->droite[personnage->frame];
            break;
        case 3:
            frame = personnage->haut[personnage->frame];
            break;
    }
    masked_blit(frame, buffer, 0, 0, personnage->x, personnage->y, frame->w, frame->h);
}
void maj_personnage(sCharacter* personnage, BITMAP *Chemin_joueur_possible){
    int vitesse = 1;
    personnage->en_deplacement = 0;
    if (key[KEY_UP] && getpixel(Chemin_joueur_possible, personnage->x+32, personnage->y-1+64) == makecol(0, 0, 0)) {
        personnage->y -= vitesse;
        personnage->direction = 3;
        personnage->en_deplacement = 1;
    }
    if (key[KEY_DOWN] && getpixel(Chemin_joueur_possible, personnage->x+32, personnage->y+1+64) == makecol(0, 0, 0)) {
        personnage->y += vitesse;
        personnage->direction = 0;
        personnage->en_deplacement = 1;
    }
    if (key[KEY_LEFT] && getpixel(Chemin_joueur_possible, personnage->x-1+32, personnage->y+64) == makecol(0, 0, 0)) {
        personnage->x -= vitesse;
        personnage->direction = 1;
        personnage->en_deplacement = 1;
    }
    if (key[KEY_RIGHT] && getpixel(Chemin_joueur_possible, personnage->x+1+32, personnage->y+64) == makecol(0, 0, 0)) {
        personnage->x += vitesse;
        personnage->direction = 2;
        personnage->en_deplacement = 1;
    }
}


void enter_pseudo(char *pseudo) {
    clear_keybuf();
    int i = 0;
    while (1) {
        if (keypressed()) {
            int touche = readkey() & 0xff;
            //Pour le programme s'arrete au bon moment
            if (touche == 13) { // Touche "Entrée"
                break;
                //si jamais on souhaite changer une lettre
            } else if (touche == 8 && i > 0) { // Touche "Retour arrière"
                i--;
                //Chaine de caractere donc un \0
                pseudo[i] = '\0';
                //Blindage pour ne pas avoir de mauvaise lettre
            } else if (touche >= 32 && touche <= 126 && i < MAX_PSEUDO - 1) { // Caractères valides
                pseudo[i] = touche;
                i++;
                pseudo[i] = '\0';
            }
        }
        rest(10);
    }
}
