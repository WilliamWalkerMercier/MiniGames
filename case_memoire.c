
#include "link.h"
#define NB_RECT 9

typedef struct Rectangle {
    int coord_x1; // pixel coin UP Left
    int coord_x2; // pixel coin UP droit
    int coord_y1; // pixel coin Down Left
    int coord_y2; // pixel coin Down droit
} t_rect;

t_rect *creer_rect(int i) {
    t_rect *rectangle = (t_rect*)malloc(sizeof(t_rect));
    if(i==0){
        rectangle->coord_x1=300;
        rectangle->coord_x2=400;
        rectangle->coord_y1=150;
        rectangle->coord_y2=250;
    }
    if(i==1){
        rectangle->coord_x1=450;
        rectangle->coord_x2=550;
        rectangle->coord_y1=150;
        rectangle->coord_y2=250;
    }
    if(i==2){
        rectangle->coord_x1=600;
        rectangle->coord_x2=700;
        rectangle->coord_y1=150;
        rectangle->coord_y2=250;
    }
    if(i==3){
        rectangle->coord_x1=300;
        rectangle->coord_x2=400;
        rectangle->coord_y1=300;
        rectangle->coord_y2=400;
    }
    if(i==4){
        rectangle->coord_x1=450;
        rectangle->coord_x2=550;
        rectangle->coord_y1=300;
        rectangle->coord_y2=400;
    }
    if(i==5){
        rectangle->coord_x1=600;
        rectangle->coord_x2=700;
        rectangle->coord_y1=300;
        rectangle->coord_y2=400;
    }if(i==6){
        rectangle->coord_x1=300;
        rectangle->coord_x2=400;
        rectangle->coord_y1=450;
        rectangle->coord_y2=550;
    }
    if(i==7){
        rectangle->coord_x1=450;
        rectangle->coord_x2=550;
        rectangle->coord_y1=450;
        rectangle->coord_y2=550;
    }
    if(i==8){
        rectangle->coord_x1=600;
        rectangle->coord_x2=700;
        rectangle->coord_y1=450;
        rectangle->coord_y2=550;
    }
    return rectangle;
}

void demo_combi(int *combinaison, t_rect **rectangle, int niveau) {
    int i = 0;
    int j = 0;
    while (j < niveau) {
        i = combinaison[j];
        rectfill(screen, rectangle[i]->coord_x1, rectangle[i]->coord_y1, rectangle[i]->coord_x2, rectangle[i]->coord_y2, makecol(255, 0, 0));
        rest(500);
        rectfill(screen, rectangle[i]->coord_x1, rectangle[i]->coord_y1, rectangle[i]->coord_x2, rectangle[i]->coord_y2, makecol(255, 255, 255));
        rest(500);
        free(rectangle[i]); // Libérer la mémoire allouée pour le rectangle
        j++;
    }
}

void combi_entree(int *combinaison_entree,int niveau,t_rect **rectangle){
    int nb_clique=0;
    while(nb_clique<niveau){
        if(mouse_b & 1){
            for(int i=0;i<NB_RECT;i++){
                if(mouse_x>=rectangle[i]->coord_x1 && mouse_x<=rectangle[i]->coord_x2 && mouse_y>=rectangle[i]->coord_y1 && mouse_y<=rectangle[i]->coord_y2){
                    combinaison_entree[nb_clique]=i;
                    rectfill(screen, rectangle[i]->coord_x1, rectangle[i]->coord_y1, rectangle[i]->coord_x2, rectangle[i]->coord_y2, makecol(255, 0, 0));
                    rest(500);
                    rectfill(screen, rectangle[i]->coord_x1, rectangle[i]->coord_y1, rectangle[i]->coord_x2, rectangle[i]->coord_y2, makecol(255, 255, 255));
                    rest(500);
                }
            }
            nb_clique++;
        }
    }
}

int verif_combi(int *combinaison,int *combinaison_entree,int niveau){
    int verifie=1;
    for(int i=0;i<niveau;i++){
        if(combinaison[i]!=combinaison_entree[i])verifie=0;
    }
    return verifie;
}

int jeu_de_memoire() {
    t_rect *rectangle[NB_RECT];
    int fin_de_jeu=1;
    int combinaison[40], combinaison_entree[40];
    int niveau = 0;
    for (int i = 0; i < NB_RECT; i++) {
        rectangle[i] = creer_rect(i);
    }

    while (!key[KEY_ESC] && fin_de_jeu) {
        combinaison[niveau] = rand() % 9;
        if (niveau == 0) {
            for (int i = 0; i < NB_RECT; i++) {
                rectfill(screen, rectangle[i]->coord_x1, rectangle[i]->coord_y1, rectangle[i]->coord_x2, rectangle[i]->coord_y2, makecol(255, 255, 255));
            }
        }
        if(verif_combi(combinaison,combinaison_entree,niveau)){
            niveau++;

            demo_combi(combinaison,rectangle,niveau);
            rest(100);
            combi_entree(combinaison_entree,niveau,rectangle);
        }
        else{
            fin_de_jeu=0;
        }
    }

    for (int i = 0; i < NB_RECT; i++) {
        free(rectangle[i]);
    }
    allegro_message("Vous avez atteint le niveau : %d",niveau);
    return niveau;
}

