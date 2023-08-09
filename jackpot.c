
#include "link.h"

void jackpot(t_joueur* joueur, int tour) {
    //Son et image
    SAMPLE *sonManche = load_sample("ressources/son/Casino/banditmanchot.wav");
    BITMAP *page = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *ImgIntro = load_bitmap("ressources/images/Casino/introCasino.bmp", NULL);
    BITMAP *Imgfond = load_bitmap("ressources/images/Casino/fondCasino.bmp", NULL);
    BITMAP *Imgmanche = load_bitmap("ressources/images/Casino/MancheCasino.bmp", NULL);
    BITMAP *ImgSymbole = load_bitmap("ressources/images/Casino/symboleCasino.bmp", NULL);
    BITMAP *win = load_bitmap("ressources/images/Casino/youWin.bmp", NULL);
    BITMAP *lose = load_bitmap("ressources/images/Casino/youLose.bmp", NULL);
    int image1 = 0, image2 = 0, image3 = 0, symboleRandom, nbLancers = 0, vWin = 0;
    sImgCoordonnees tabimage[3];
    blit(ImgIntro, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_W);
    rest(8000);
    blit(Imgfond, page, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(Imgmanche, page, 0, 0, 794, 250, 105, 175);
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    for (int i = 0; i < 3; i++) {
        symboleRandom = rand() % 16;
        tabimage[i].indexImage = symboleRandom;
        tabimage[i].PosX = symboleRandom * 110;
        tabimage[i].PosY = 0;
    }
    while(!key[KEY_ESC]){
    if (key[KEY_SPACE]) {
        while (nbLancers < 10) {
            play_sample(sonManche, 255, 128, 4364, FALSE);//Joue le sonManche
            blit(Imgfond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            blit(Imgmanche, screen, 0, 176, 794, 362, 105, 175);//Affichage du manche baissé
            rest(100);
            blit(Imgfond, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            blit(Imgmanche, screen, 0, 0, 794, 250, 105, 175);//Affichage du manche relevé
            for (int j = 0; j <= 4; j++) {
                image1 = rand() % 3;
                image2 = rand() % 3;
                image3 = rand() % 3;
                blit(ImgSymbole, page, tabimage[image1].PosX, tabimage[image1].PosY, 320, 350, 110, 110);
                blit(ImgSymbole, page, tabimage[image2].PosX, tabimage[image2].PosY, 475, 350, 110, 110);
                blit(ImgSymbole, page, tabimage[image3].PosX, tabimage[image3].PosY, 630, 350, 110, 110);
                blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest(250);
                if (j == 4) {
                    if (image1 == image2 && image2 == image3) {
                        rest(450);
                        vWin++;
                        nbLancers++;
                        blit(win, screen, 0, 0, 450, 300, 1000, 800);
                        rest(500);
                    } else {
                        rest(500);
                        nbLancers++;
                        blit(lose, screen, 0, 0, 400, 270, 1000, 800);
                        rest(500);
                    }
                }
            }
        }
        nbLancers = 0;
        if (vWin != 0) {
            rest(1000);
            allegro_message("Vous avez gagné 3 tickets");
            if (tour == 0) {
                joueur->ticket_j1 += 3;
                joueur->ticket_j2--;
                joueur->Jackpot_j1++;
                joueur->Jackpot_j2--;
            }
            if (tour == 1) {
                joueur->ticket_j2 += 3;
                joueur->ticket_j1--;
                joueur->Jackpot_j2++;
                joueur->Jackpot_j1--;
            }
        } else {
            rest(1000);
            allegro_message("Vous avez perdu 1 tickets");
            if (tour == 0) {
                joueur->ticket_j1--;
                joueur->Jackpot_j1--;
                joueur->Jackpot_j2++;
            }
            if (tour == 1) {
                joueur->ticket_j2--;
                joueur->Jackpot_j2--;
                joueur->Jackpot_j1++;
            }
        }
        vWin = 0;
    }
}
    destroy_bitmap(ImgIntro);
    destroy_bitmap(page);
    destroy_bitmap(Imgfond);
    destroy_bitmap(Imgmanche);
    destroy_bitmap(ImgSymbole);
    destroy_bitmap(win);
    destroy_bitmap(lose);
    destroy_sample(sonManche);
}
