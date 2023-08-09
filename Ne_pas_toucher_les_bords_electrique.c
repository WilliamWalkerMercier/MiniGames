
#include "link.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700


void point_alleatoire(int tableau_de_point[21]){
    for (int i = 0; i < 21; ++i) {
        tableau_de_point[i] = 50 + rand()%581;
        for (int j = 0; j < i ; ++j) {
            if (tableau_de_point[j] == tableau_de_point[i] ){
                i--;
            }
        }
    }
}

void tri(int tableau_de_point[21]){
    int temp;

    for (int i = 1; i < 21; i += 2) {
        for (int j = 0; j < 21 - i; j += 2) {
            if (tableau_de_point[j] > tableau_de_point[j + 2]) {
                temp = tableau_de_point[j];
                tableau_de_point[j] = tableau_de_point[j + 2];
                tableau_de_point[j + 2] = temp;
            }
        }
    }
}

void affichage(BITMAP *buffer, int tableau_de_point[21], BITMAP *background){
    blit(background, buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    for (int i = 0; i < 21; ++i) {
        if ( i == 0){
            rectfill(buffer, 0, 50, tableau_de_point[i], 0, makecol(255, 255, 255));
            rectfill(buffer, tableau_de_point[i], 0, tableau_de_point[i] + 15, tableau_de_point[i + 1], makecol(255, 255, 255));
        }
        if ( i == 20){
            rectfill(buffer, tableau_de_point[i-2], tableau_de_point[i-1],SCREEN_WIDTH, tableau_de_point[i-1] + 15,  makecol(255, 255, 255));
            rectfill(buffer, SCREEN_WIDTH -50, tableau_de_point[i-1],SCREEN_WIDTH, SCREEN_HEIGHT,  makecol(255, 255, 255));
            rectfill(buffer, SCREEN_WIDTH -50, SCREEN_HEIGHT - 50,SCREEN_WIDTH, SCREEN_HEIGHT,  makecol(0, 200, 0));
        }
        if ( i % 2 == 0 && i != 20 && i != 0){rectfill(buffer, tableau_de_point[i-2] , tableau_de_point[i-1], tableau_de_point[i] +15, tableau_de_point[i-1]+15,  makecol(255, 255, 255));}
        if ( i % 2 != 0 && i != 1){rectfill(buffer, tableau_de_point[i-1], tableau_de_point[i-2] +15, tableau_de_point[i-1]+15, tableau_de_point[i],  makecol(255, 255, 255));}
    }
    blit(buffer, screen, 0, 0, 0 ,0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
/*
void jeu_ne_pas_toucher_les_bords_electrique(t_joueur* joueur){

    int tableau_de_point[21];
    time_t temps_debut, temps_fin, temps_j1, temps_j2;

    /// Déclaration de bitmap buffer / bitmap dimage
    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    int blanc = makecol(255, 255, 255);

    BITMAP *source_background = load_bitmap("ressources/images/eclairerel2.bmp",NULL);
    BITMAP *PlayerSwap = load_bitmap("ressources/images/changement_de_joueur.bmp", NULL);
    //on redimensionne l'image (eclaire)
    BITMAP *background = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    stretch_blit(source_background, background, 0, 0, source_background->w, source_background->h, 0, 0, background->w, background->h);


    show_mouse(screen);

    point_alleatoire(tableau_de_point);

    tri(tableau_de_point);

    for (int i = 0; i < 2; ++i) {

        rectfill(buffer, 0, 0, 50, 50, makecol(0, 200, 0));
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


        while (getpixel(buffer, mouse_x, mouse_y) != makecol(0, 200, 0)) {}
        rest(500);
        clear(screen);
        clear(buffer);

        affichage(buffer, tableau_de_point, background);
        affichage(buffer, tableau_de_point, background);
        affichage(buffer, tableau_de_point, background);

        temps_debut = time(NULL);
        temps_fin = time(NULL);

        while (getpixel(buffer, mouse_x, mouse_y) == blanc) { affichage(buffer, tableau_de_point, background); }
        temps_fin = time(NULL);

        if (getpixel(buffer, mouse_x, mouse_y) == makecol(0, 200, 0)) {
            if (i == 0){
                temps_j1 = temps_fin - temps_debut;
            }
            if (i == 1){
                temps_j2 = temps_fin - temps_debut;
            }
        } else{
            if (i == 0){
                temps_j1 = 9999999999;
            }
            if (i == 1){
                temps_j2 = 9999999999;
            }
        }
        clear(buffer);
        clear(screen);
        if (i == 0){
            stretch_blit(PlayerSwap, screen, 0, 0, PlayerSwap->w, PlayerSwap->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(5000);
        }
    }

    if (temps_j1 < temps_j2){
        joueur->ticket_j1++;
        joueur->ticket_j2--;
        joueur->Eclaire_j1++;
        joueur->Eclaire_j2--;
        allegro_message("Le joueur 1 a été le plus rapide. Il remporte un ticket du joueur 2.");
    }
    if (temps_j1 > temps_j2){
        joueur->ticket_j1--;
        joueur->ticket_j2++;
        joueur->Eclaire_j1--;
        joueur->Eclaire_j2++;
        allegro_message("Le joueur 2 a été le plus rapide. Il remporte un ticket du joueur 1.");
    }
    if (temps_j1 == temps_j2 && temps_j1 != 9999999999){
        joueur->ticket_j1++;
        joueur->ticket_j2++;
        joueur->Eclaire_j1++;
        joueur->Eclaire_j2++;
        allegro_message("Les 2 joueurs ont le même temps. Ils gagnent tout les 2 un ticket");
    }
    if (temps_j1 == temps_j2 && temps_j1 == 9999999999){
        joueur->ticket_j1--;
        joueur->ticket_j2--;
        joueur->Eclaire_j1--;
        joueur->Eclaire_j2--;
        allegro_message("Les 2 joueurs sont sorti du terrain. Ils perdent tout les 2 un ticket");
    }

    destroy_bitmap(buffer);
    destroy_bitmap(background);
    destroy_bitmap(source_background);
    destroy_bitmap(PlayerSwap);
}
*/