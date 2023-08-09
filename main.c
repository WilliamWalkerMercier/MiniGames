#include "link.h"


//Sous-programmes
void separer_bitmap_personnage(t_personnage* personnage, BITMAP* bitmap)
{
    for (int j = 0; j < 4; j++) {
        personnage->bas[j] = create_sub_bitmap(bitmap, j * bitmap->w/4, 0 * bitmap->h/4, bitmap->w/4, bitmap->h/4);
        personnage->gauche[j] = create_sub_bitmap(bitmap, j * bitmap->w/4, 1 * bitmap->h/4, bitmap->w/4, bitmap->h/4);
        personnage->droite[j] = create_sub_bitmap(bitmap, j * bitmap->w/4, 2 * bitmap->h/4, bitmap->w/4, bitmap->h/4);
        personnage->haut[j] = create_sub_bitmap(bitmap, j * bitmap->w/4, 3 * bitmap->h/4, bitmap->w/4, bitmap->h/4);
    }
}

void dessiner_personnage(t_personnage* personnage, BITMAP* buffer){
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

void maj_personnage(t_personnage* personnage, BITMAP *Chemin_joueur_possible){
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
int main() {
    srand(time(NULL));
    initialisation_allegro();
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);;
    BITMAP *source_ECE_World_map = load_image("ressources/images/ECE_World_map.bmp");
    BITMAP *source_Chemin_joueur_possible = load_image("ressources/images/Chemin_possible.bmp");
    BITMAP *Personnage = load_image("ressources/images/personnage.bmp");
    int resultat_roue1=0,resultat_roue2=0;
    int resultat_guitar1=0,resultat_guitar2=0;
    int resultat_ballon1=0,resultat_ballon2=0;
    int resultat_memoire1=0,resultat_memoire2=0;
    //on redimensionne l'image (Chemin_possible)
    BITMAP *Changemant = load_image("ressources/images/changement_de_joueur.bmp");
    BITMAP *Chemin_joueur_possible = create_bitmap(SCREEN_W, SCREEN_H);
    stretch_blit(source_Chemin_joueur_possible, Chemin_joueur_possible, 0, 0, source_Chemin_joueur_possible->w, source_Chemin_joueur_possible->h, 0, 0, SCREEN_W, SCREEN_H);
    destroy_bitmap(source_Chemin_joueur_possible);

    //on redimensionne l'image (Chemin_possible)
    BITMAP *ECE_World_map = create_bitmap(SCREEN_W, SCREEN_H);
    stretch_blit(source_ECE_World_map, ECE_World_map, 0, 0, source_ECE_World_map->w, source_ECE_World_map->h, 0, 0, SCREEN_W, SCREEN_H);
    destroy_bitmap(source_ECE_World_map);

    t_personnage personnage;
    personnage.direction = 0;
    personnage.frame = 0;
    personnage.x = SCREEN_W/2;
    personnage.y = SCREEN_H/2;

    t_joueur joueur;
    joueur.ticket_j1 = 5;
    joueur.ticket_j2 = 5;
    joueur.Oie_j1 = joueur.Oie_j2 = joueur.Eclaire_j1 = joueur.Eclaire_j2 = joueur.Snake_j1 = joueur.Snake_j2 = joueur.Memoire_j1 = joueur.Memoire_j2 = joueur.ballon_j1 = joueur.ballon_j2 = joueur.Jackpot_j1 = joueur.Jackpot_j2 = joueur.RoueF_j1 = joueur.RoueF_j2 = joueur.Guitar_j1 = joueur.Guitar_j2 = 0;

    separer_bitmap_personnage(&personnage, Personnage);
    int frame_counter = 0;

    BITMAP *opening= load_bitmap("ressources/images/ECE_World_op.bmp",NULL);
    while(!key[KEY_ENTER]){
        blit(opening, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    }
    clear(buffer);
    clear(screen);
    textout_centre_ex(screen, font, "Entrez votre pseudo joueur 1:", SCREEN_W / 2, SCREEN_H / 2 - 10, makecol(255, 255, 255), -1);
    enter_pseudo(joueur.pseudo_j1);

    textout_centre_ex(screen, font, "Pseudo du joueur 1 enregistré:", SCREEN_W / 2, SCREEN_H / 2 + 10, makecol(255, 255, 255), -1);
    textout_centre_ex(screen, font, joueur.pseudo_j1, SCREEN_W / 2, SCREEN_H / 2 + 30, makecol(255, 255, 255), -1);
    rest(1000);
    stretch_blit(Changemant, screen, 0, 0, Changemant->w, Changemant->h, 0, 0, SCREEN_W, SCREEN_H);
    rest(2500);
    clear(screen);
    textout_centre_ex(screen, font, "Entrez votre pseudo joueur 2:", SCREEN_W / 2, SCREEN_H / 2 - 10, makecol(255, 255, 255), -1);
    enter_pseudo(joueur.pseudo_j2);

    textout_centre_ex(screen, font, "Pseudo du joueur 2 enregistré:", SCREEN_W / 2, SCREEN_H / 2 + 10, makecol(255, 255, 255), -1);
    textout_centre_ex(screen, font, joueur.pseudo_j2, SCREEN_W / 2, SCREEN_H / 2 + 30, makecol(255, 255, 255), -1);
    rest(1000);
    clear(screen);

    while (personnage.y + 64 < 690 && joueur.ticket_j1 != 0 &&  joueur.ticket_j2 != 0) {

        maj_personnage(&personnage, Chemin_joueur_possible);

        blit(ECE_World_map, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        dessiner_personnage(&personnage, buffer);

        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

        frame_counter++;
        if (frame_counter >= 10) {
            if (personnage.en_deplacement) {
                personnage.frame = (personnage.frame + 1) % 4;
            } else {
                personnage.frame = 0;
            }
            frame_counter = 0;
        }
        rest(10);
        if (getpixel(Chemin_joueur_possible, personnage.x+32, personnage.y+1+64) == makecol(255, 0, 255 ) && key[KEY_ENTER]){
            jeu_ne_pas_toucher_les_bords_electrique(&joueur);
        }
        if (getpixel(Chemin_joueur_possible, personnage.x+32, personnage.y+1+64) == makecol(0, 255, 0 ) && key[KEY_ENTER]){
            jeu_Snake(&joueur);
        }
        if (getpixel(Chemin_joueur_possible, personnage.x+32, personnage.y+1+64) == makecol(255, 255, 255 ) && key[KEY_ENTER]){
            jackpot(&joueur,0);
            stretch_blit(Changemant, screen, 0, 0, Changemant->w, Changemant->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            jackpot(&joueur,1);
        }
        if (getpixel(Chemin_joueur_possible, personnage.x+32, personnage.y+1+64) == makecol(100, 100, 100 ) && key[KEY_ENTER]){
            jeudeloie(&joueur);
        }
        if (getpixel(Chemin_joueur_possible, personnage.x+32, personnage.y-1+64) == makecol(255, 0, 0 ) && key[KEY_ENTER]){
            clear(screen);
            resultat_roue1 = jeu_RoueFor();
            stretch_blit(Changemant, screen, 0, 0, Changemant->w, Changemant->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            clear(screen);
            resultat_roue2 = jeu_RoueFor();
            if(resultat_roue1<resultat_roue2){
                allegro_message("Le joueur 1 a reçu un meilleur score. Il remporte un ticket du joueur 2.");
                joueur.ticket_j1+=1;
                joueur.ticket_j2-=1;
            }
            if(resultat_roue1>resultat_roue2){
                allegro_message("Le joueur 2 a reçu un meilleur score. Il remporte un ticket du joueur 1.");
                joueur.ticket_j2+=1;
                joueur.ticket_j1-=1;
            }
            if(resultat_roue1==resultat_roue2){
                allegro_message("Les deux joueurs ont reçu le même score. Personne ne gagne de ticket.");
            }

        }
        if (getpixel(Chemin_joueur_possible, personnage.x+32, personnage.y-1+64) == makecol(0, 0, 255 ) && key[KEY_ENTER]){
            clear(screen);
            resultat_guitar1=jeu_Guitar();
            stretch_blit(Changemant, screen, 0, 0, Changemant->w, Changemant->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            clear(screen);
            resultat_guitar2=jeu_Guitar();
            if(resultat_guitar1<resultat_guitar2){
                allegro_message("Le joueur 1 a reçu un meilleur score. Il remporte un ticket du joueur 2.");
                joueur.ticket_j1+=1;
                joueur.ticket_j2-=1;
            }
            if(resultat_guitar1>resultat_guitar2){
                allegro_message("Le joueur 2 a reçu un meilleur score. Il remporte un ticket du joueur 1.");
                joueur.ticket_j2+=1;
                joueur.ticket_j1-=1;
            }
            if(resultat_guitar1==resultat_guitar2){
                allegro_message("Les deux joueurs ont reçu le même score. Personne ne gagne de ticket.");
            }
        }


        if (getpixel(Chemin_joueur_possible, personnage.x+32, personnage.y-1+64) == makecol(0, 255, 255 ) && key[KEY_ENTER]){
            clear(screen);
            BITMAP *regle_du_jeu= load_bitmap("ressources/images/Regle_ballon.bmp",NULL);
            blit(regle_du_jeu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(5000);
            clear(screen);
            resultat_ballon1=jeu_ballon();
            stretch_blit(Changemant, screen, 0, 0, Changemant->w, Changemant->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            clear(screen);
            resultat_ballon2=jeu_ballon();
            if(resultat_ballon1<resultat_ballon2){
                allegro_message("%s a été le plus rapide. Il remporte un ticket du %s.",joueur.pseudo_j1,joueur.pseudo_j2);
                joueur.ticket_j1+=1;
                joueur.ballon_j1+=1;
                joueur.ticket_j2-=1;
                joueur.ballon_j2-=1;
            }
            if(resultat_ballon1>resultat_ballon2){
                allegro_message("%s a été le plus rapide. Il remporte un ticket du %s.",joueur.pseudo_j2,joueur.pseudo_j1);
                joueur.ticket_j1-=1;
                joueur.ballon_j1-=1;
                joueur.ticket_j2+=1;
                joueur.ballon_j2+=1;
            }
            if(resultat_ballon1==resultat_ballon2){
                allegro_message("Les 2 joueurs ont le même temps. Ils gagnent rien et perdent rien");
            }
        }
        if (getpixel(Chemin_joueur_possible, personnage.x+32, personnage.y-1+64) == makecol(255, 255, 0 ) && key[KEY_ENTER]){
            clear(screen);
            BITMAP *regle_du_jeu= load_bitmap("ressources/images/regle_memoire.bmp",NULL);
            blit(regle_du_jeu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(5000);
            clear(screen);
            resultat_memoire1=jeu_de_memoire();
            stretch_blit(Changemant, screen, 0, 0, Changemant->w, Changemant->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            clear(screen);
            resultat_memoire2=jeu_de_memoire();
            if(resultat_memoire1>resultat_memoire2){
                allegro_message("%s a été le plus loin. Il remporte un ticket du %s.",joueur.pseudo_j1,joueur.pseudo_j2);
                joueur.ticket_j1+=1;
                joueur.Memoire_j1+=1;
                joueur.ticket_j2-=1;
                joueur.Memoire_j2-=1;
            }
            if(resultat_memoire1<resultat_memoire2){
                allegro_message("%s a été le plus loin. Il remporte un ticket du %s.",joueur.pseudo_j2,joueur.pseudo_j1);
                joueur.ticket_j1-=1;
                joueur.Memoire_j1-=1;
                joueur.ticket_j2+=1;
                joueur.Memoire_j2+=1;
            }
            if(resultat_memoire1==resultat_memoire2){
                allegro_message("Les 2 joueurs ont le même score. Ils gagnent rien et perdent rien");
            }
        }
        if (getpixel(Chemin_joueur_possible, personnage.x+32, personnage.y-1+64) == makecol(100, 0, 100 ) && key[KEY_ENTER]){
            allegro_message("%s : %d tickets\n %s : %d tickets\n\n Tickets gagné et perdu joueur1:\n Snake: %d   Eclaire: %d   Ballon: %d   Memoire: %d   Oie: %d   Jackpot: %d   \nGuitar: %d   RoueFortune: %d\n\nTickets gagné et perdu joueur2:\n Snake: %d   Eclaire: %d   Ballon: %d   Memoire: %d   Oie: %d   Jackpot: %d   \nGuitar: %d   RoueFortune: %d\n\n",joueur.pseudo_j1, joueur.ticket_j1, joueur.pseudo_j2,joueur.ticket_j2, joueur.Snake_j1, joueur.Eclaire_j1, joueur.ballon_j1, joueur.Memoire_j1, joueur.Oie_j1, joueur.Jackpot_j1, joueur.Guitar_j1, joueur.RoueF_j1, joueur.Snake_j2, joueur.Eclaire_j2, joueur.ballon_j2, joueur.Memoire_j2, joueur.Oie_j2, joueur.Jackpot_j2, joueur.Guitar_j2, joueur.RoueF_j2);
        }
    }

    if (joueur.ticket_j1 == 0 &&  joueur.ticket_j2 != 0){
        allegro_message("%s a gagné.",joueur.pseudo_j2);
    }
    if (joueur.ticket_j1 != 0 &&  joueur.ticket_j2 == 0){
        allegro_message("%s a gagné.",joueur.pseudo_j1);
    }
    if (joueur.ticket_j1 == 0 &&  joueur.ticket_j2 == 0){
        allegro_message("Les 2 joueurs ont perdu.");
    }
    allegro_message("See you next time ! ;)");

    destroy_bitmap(buffer);
    destroy_bitmap(ECE_World_map);
    destroy_bitmap(Chemin_joueur_possible);
    destroy_bitmap(Personnage);
    for (int i = 0; i < 4; i++) {
        destroy_bitmap(personnage.bas[i]);
        destroy_bitmap(personnage.gauche[i]);
        destroy_bitmap(personnage.droite[i]);
        destroy_bitmap(personnage.haut[i]);
    }
    allegro_exit();
    return 0;

}

END_OF_MAIN();
