
//
// Created by Willyson on 14/05/2023.
//
#include "link.h"


void jeudeloie(t_joueur* joueur) {
    int compteurTour=0; int de=0; int tourJoueur=0;
    BITMAP *SpritePersonnage1 = load_bitmap("ressources/images/Oie/ninja1.bmp", NULL);
    BITMAP *SpritePersonnage2= load_bitmap("ressources/images/Oie/elfe1.bmp",NULL);
    BITMAP *Imgfond = load_bitmap("ressources/images/Oie/jeudeloie.bmp", NULL);
    BITMAP *ImgIntro = load_bitmap("ressources/images/Oie/introjeuoie.bmp", NULL);

    sJoueurCoordonnees tabJoueur[5];
    sJoueurCoordonnees previous;
    for (int i=0;i<2;i++){
        tabJoueur[i].posX=0;
        tabJoueur[i].posY=0;
        previous.posX=tabJoueur[i].posX;
        previous.posY=tabJoueur[i].posY;
    }
    tabJoueur[0].image=SpritePersonnage1;
    tabJoueur[1].image=SpritePersonnage2;
    blit(ImgIntro,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    rest(8000);
    blit(Imgfond,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    draw_sprite(screen,SpritePersonnage1,0*110,640);
    draw_sprite(screen,SpritePersonnage1,0*110,640);

    while(tabJoueur[tourJoueur].posX !=6 || tabJoueur[tourJoueur].posY!=5){
        if(key[KEY_SPACE]){
            de=rand()%6+1;
            allegro_message("La sorcière te fait avancer de %d cases",de);
            tourJoueur=(compteurTour%2);
            for(int i=0;i<de;i++){
                verifieDeplacement(&tabJoueur[tourJoueur],1);
                blit(Imgfond,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                draw_sprite(screen,tabJoueur[(compteurTour+1)%2].image,tabJoueur[(compteurTour+1)%2].posX*130,(5-tabJoueur[(compteurTour+1)%2].posY)*127+10*tabJoueur[(compteurTour+1)%2].posY);
                rest(50);
                draw_sprite(screen,tabJoueur[tourJoueur].image,tabJoueur[tourJoueur].posX*130,(5-tabJoueur[tourJoueur].posY)*127+10*tabJoueur[tourJoueur].posY);
                rest(800);
            }
            verifieCase(&tabJoueur[tourJoueur],&tabJoueur[(compteurTour+1)%2]);
            blit(Imgfond,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            draw_sprite(screen,tabJoueur[(compteurTour+1)%2].image,tabJoueur[(compteurTour+1)%2].posX*130,(5-tabJoueur[(compteurTour+1)%2].posY)*127+10*tabJoueur[(compteurTour+1)%2].posY);
            rest(100);
            draw_sprite(screen,tabJoueur[tourJoueur].image,tabJoueur[tourJoueur].posX*130,(5-tabJoueur[tourJoueur].posY)*127+10*tabJoueur[tourJoueur].posY);
            previous.posX=tabJoueur[tourJoueur].posX;
            previous.posY=tabJoueur[tourJoueur].posY;
            compteurTour++;
            allegro_message("Joueur Suivant");
        }
    }
    allegro_message("Bravo le jour %d remporte un ticket et l'autre joueur en perd un",tourJoueur+1);
    if(tourJoueur==0){
        joueur->ticket_j1++;
        joueur->ticket_j2--;
        joueur->Oie_j1++;
        joueur->Oie_j2--;
    }
    if(tourJoueur==1){
        joueur->ticket_j2++;
        joueur->ticket_j1--;
        joueur->Oie_j2++;
        joueur->Oie_j1--;

    }
    destroy_bitmap(SpritePersonnage1);
    destroy_bitmap(SpritePersonnage2);
    destroy_bitmap(Imgfond);
    destroy_bitmap(ImgIntro);
}


void verifieCase(sJoueurCoordonnees* prJoueur1,sJoueurCoordonnees*prJoueur2){
    int de=0;int de2=0;int xTemp=0;int yTemp=0;
    if(prJoueur1->posX==2 && prJoueur1->posY==0){//Mage
        allegro_message("Le mage te donne un coup de pouce");
        prJoueur1->posX+=4;
    }
    if(prJoueur1->posX==4 && prJoueur1->posY==0){//Dragon
        de=rand()%7;
        de2=rand()%6;
        allegro_message("Le dragon te fait voler à un endroit au hasard");
        prJoueur1->posX=de;
        prJoueur1->posY=de2;
    }
    if(prJoueur1->posX==1 && prJoueur1->posY==1){//Portail Bleu
        allegro_message("Tu te téléportes à travers une étrange dimension");
        prJoueur1->posX=4;
        prJoueur1->posY=3;
    }
    if(prJoueur1->posX==4 && prJoueur1->posY==1){//Fantome
        allegro_message("Oh un fantome, tu as peur et tu recules de 3 cases");
        prJoueur1->posX-=3;
    }
    if(prJoueur1->posX==2 && prJoueur1->posY==2){//Troll
        allegro_message("Le troll te balance de deux cases");
        de=rand()%1;
        if(de==0){
            prJoueur1->posX+=2;
        }
        else{
            prJoueur1->posX-=2;
        }
    }
    if(prJoueur1->posX==5 && prJoueur1->posY==2){//Potion
        allegro_message("Tu bois une étrange potion qui te fais rétrécir et tu arrives une case en dessous");
        prJoueur1->posY--;

    }
    if(prJoueur1->posX==1 && prJoueur1->posY==3){//Champignon
        allegro_message("Le champignon te fait rebondir une case au dessus");
        prJoueur1->posY++;
    }
    if(prJoueur1->posX==2 && prJoueur1->posY==3){//Fantome 24
        allegro_message("Oh un fantome, tu as peur et tu recules de 3 cases");
        prJoueur1->posX=6;
        prJoueur1->posY=2;
    }
    if(prJoueur1->posX==5 && prJoueur1->posY==3){//Gobelin 27
        allegro_message("Oh un gobelin, tu as peur et tu fuis de 3 cases");
        allegro_message("");
        prJoueur1->posX=1;
        prJoueur1->posY=4;
    }
    if(prJoueur1->posX==2 && prJoueur1->posY==4){//Mage
        allegro_message("Le mage rouge lance un sort et les 2 joueurs échangent de place");
        xTemp=prJoueur1->posX;
        yTemp=prJoueur1->posY;
        prJoueur1->posX=prJoueur2->posX;
        prJoueur1->posY=prJoueur2->posY;
        prJoueur2->posX=xTemp;
        prJoueur2->posY=yTemp;
    }
    if(prJoueur1->posX==4 && prJoueur1->posY==4){//Fantome 33
        allegro_message("Oh un fantome, tu as peur et tu recules de 3 cases");
        prJoueur1->posX-=3;
    }
    if(prJoueur1->posX==1 && prJoueur1->posY==5){//Gobelin 37
        allegro_message("Oh un gobelin, tu as peur et tu fuis de 3 cases");
        prJoueur1->posX+=3;
    }
    if(prJoueur1->posX==2 && prJoueur1->posY==5){//Mort
        allegro_message("La faucheuse a fait son travail, et tu dois recommencer ton chemin");
        prJoueur1->posX=0;
        prJoueur1->posY=0;
    }
}
void verifieDeplacement(sJoueurCoordonnees* prJoueur,int de){
    prJoueur->posX += de;

    while(prJoueur->posX >= 7){
        prJoueur->posX -= 7;
        prJoueur->posY++;
    }

    // If the player overshoots the last square, move them back.
    if (prJoueur->posY >= 6 && prJoueur->posX > 6) {
        int excess = prJoueur->posX - 6;
        prJoueur->posX = 6 - excess;
    }

    // Ensure posY is within the valid range.
    if(prJoueur->posY >= 6){
        prJoueur->posY = 5;
    }
}








