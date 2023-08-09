
#include "link.h"
#define NB_BALLON 10


typedef struct Ballons{
    int coord_x1; // pixel coin haut gauche
    int coord_x2; // pixel coin haut droit
    int coord_y1; // pixel coin bas gauche
    int coord_y2; // pixel coin bas droit
    int dep_x; // Pour controler le changement de coordonnees
    int dep_y;
    int couleur; //Nous allons faire 7 couleurs différentes
    int direction; // Permet de modifier la direction du ballon
}t_ballons;

void *creer_ballon(){
    t_ballons *ballons=(t_ballons*)malloc(sizeof(t_ballons));
    ballons->couleur=rand()%7;
    ballons->direction=rand()%4;
    ballons->dep_x=1;
    ballons->dep_y=1;
    ballons->coord_x1=rand()%638+132;
    ballons->coord_x2=ballons->coord_x1+72; //Taille pixel de l'image choisi
    ballons->coord_y1=rand()%286+134;
    ballons->coord_y2=ballons->coord_y1+97;
}

void mouvement(t_ballons *ballon){
    if(ballon->direction==0){
        ballon->coord_x1-=2*ballon->dep_x;
        ballon->coord_x2-=2*ballon->dep_x;
        ballon->coord_y1-=2*ballon->dep_y;
        ballon->coord_y2-=2*ballon->dep_y;
    }
    if(ballon->direction==1){
        ballon->coord_x1+=ballon->dep_x;
        ballon->coord_x2+=ballon->dep_x;
        ballon->coord_y1-=2*ballon->dep_y;
        ballon->coord_y2-=2*ballon->dep_y;
    }
    if(ballon->direction==2){
        ballon->coord_x1+=ballon->dep_x;
        ballon->coord_x2+=ballon->dep_x;
        ballon->coord_y1+=ballon->dep_y;
        ballon->coord_y2+=ballon->dep_y;
    }
    if(ballon->direction==3){
        ballon->coord_x1-=2*ballon->dep_x;
        ballon->coord_x2-=2*ballon->dep_x;
        ballon->coord_y1+=ballon->dep_y;
        ballon->coord_y2+=ballon->dep_y;
    }
    if(ballon->coord_x1<132)ballon->dep_x-=2*ballon->dep_x;
    if(ballon->coord_x2>806)ballon->dep_x-=2*ballon->dep_x;
    if(ballon->coord_y1<134)ballon->dep_y-=2*ballon->dep_y;
    if(ballon->coord_y2>519)ballon->dep_y-=2*ballon->dep_y;
}

int jeu_ballon(){
    BITMAP *page;
    page= create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP *source=load_bitmap("ressources/images/fond_ballon.bmp",NULL);
    BITMAP *imagefond = create_bitmap(SCREEN_W, SCREEN_H);
    int vie[NB_BALLON]; // Si le ballon est eclate sa case sera 0 sinon 1
    int terminer=1; // Tant que ce n'est pas termine, 1 sinon 0
    t_ballons *ballons[NB_BALLON];
    BITMAP *imageballon[NB_BALLON];
    time_t temps_debut=time(NULL),temps_fin=temps_debut;
    int valeur_temps;
    for(int i=0;i<NB_BALLON;i++){
        ballons[i]=creer_ballon(); // initiation des ballons
        if(ballons[i]->couleur==0) imageballon[i]=load_bitmap("ressources/images/ballon_rouge.bmp",NULL);
        if(ballons[i]->couleur==1) imageballon[i]=load_bitmap("ressources/images/ballon_orange.bmp",NULL);
        if(ballons[i]->couleur==2) imageballon[i]=load_bitmap("ressources/images/ballon_jaune.bmp",NULL);
        if(ballons[i]->couleur==3) imageballon[i]=load_bitmap("ressources/images/ballon_vert.bmp",NULL);
        if(ballons[i]->couleur==4) imageballon[i]=load_bitmap("ressources/images/ballon_aqua.bmp",NULL);
        if(ballons[i]->couleur==5) imageballon[i]=load_bitmap("ressources/images/ballon_bleu.bmp",NULL);
        if(ballons[i]->couleur==6) imageballon[i]=load_bitmap("ressources/images/ballon_violet.bmp",NULL);
        vie[i]=1;
    }

    stretch_blit(source, imagefond, 0, 0, source->w, source->h, 0, 0, imagefond->w, imagefond->h); // redimension du fond
    while(!key[KEY_ESC] && terminer==1) {
            valeur_temps=temps_fin-temps_debut;
            clear_bitmap(page);
            blit(imagefond, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            textprintf_ex(page, font, SCREEN_W/2, 100, makecol(255, 0, 255), -1, "Temps: %d", valeur_temps);
            // actualisation des ballons
            for(int i=0;i<NB_BALLON;i++){
                mouvement(ballons[i]);
                if(vie[i]){//sinon le ballon est eclate
                    draw_sprite(page, imageballon[i],ballons[i]->coord_x1+36, ballons[i]->coord_y1+49);
                }
            }
            blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            temps_fin=time(NULL);
            if(mouse_b & 1){
                for(int i=0;i<NB_BALLON;i++){
                    if(mouse_x>=ballons[i]->coord_x1 && mouse_x<=ballons[i]->coord_x2 && mouse_y>=ballons[i]->coord_y1 && mouse_y<=ballons[i]->coord_y2){
                        vie[i]=0;
                    }
                }
            }
            if(vie[0]==0 && vie[1]==0 && vie[2]==0 && vie[3]==0 && vie[4]==0 && vie[5]==0 && vie[6]==0 && vie[7]==0 && vie[8]==0 && vie[9]==0){
                terminer=0;
            }
        if(terminer==0){
            allegro_message("Vous avez mis %d secondes",valeur_temps);
        }

    }
    for(int i=0;i<NB_BALLON;i++){
        free(ballons[i]);
        destroy_bitmap(imageballon[i]);
    }
    destroy_bitmap(imagefond);
    destroy_bitmap(page);
    return valeur_temps;
}
