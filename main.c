#include "link.h"


int main() {
    srand(time(NULL));
    AllegroInitialisation();

    //Creation of bitmaps that we will use to display the lobby
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *source_ECE_World_map = load_bitmap("Ressources/Lobby/ECE_World_map.bmp",NULL);
    BITMAP *source_Chemin_joueur_possible = load_bitmap("Ressources/Lobby/Chemin_possible.bmp",NULL);
    BITMAP *Personnage = load_bitmap("Ressources/Lobby/Character.bmp",NULL);
    BITMAP *PlayerSwap = load_bitmap("Ressources/images/changement_de_joueur.bmp",NULL);
    BITMAP *opening= load_bitmap("Ressources/Lobby/ECE_World_op.bmp",NULL);

    //Variable Declaration
    int FrameCounter = 0;
    int PlayerTurn=0; // 0 or 1 for value

    //Struct Initialisation
        //Character
        sCharacter Character;
        Character.direction = 0;
        Character.frame = 0;
        Character.x = SCREEN_W / 2;
        Character.y = SCREEN_H / 2;

        //Player
        sPlayer PlayerList[2];
        for (int i=0;i<2;i++){
            PlayerList[i].NbOfTickets=5;
            PlayerList[i].Goose=0;PlayerList[i].Lightning=0;PlayerList[i].Memory=0;
            PlayerList[i].Ball=0;PlayerList[i].CasinoRoyal=0;
        }



    //Resizing the path of the map
    BITMAP *Chemin_joueur_possible = create_bitmap(SCREEN_W, SCREEN_H);
    stretch_blit(source_Chemin_joueur_possible, Chemin_joueur_possible, 0, 0, source_Chemin_joueur_possible->w, source_Chemin_joueur_possible->h, 0, 0, SCREEN_W, SCREEN_H);
    destroy_bitmap(source_Chemin_joueur_possible);

    //Resizing the World's Map
    BITMAP *ECE_World_map = create_bitmap(SCREEN_W, SCREEN_H);
    stretch_blit(source_ECE_World_map, ECE_World_map, 0, 0, source_ECE_World_map->w, source_ECE_World_map->h, 0, 0, SCREEN_W, SCREEN_H);
    destroy_bitmap(source_ECE_World_map);

    //Splitting the character bitmap into small bitmap that just contains one frame
    SplitCharacterBitmap(&Character, Personnage);

//------------------------------------------------------------------------Start of the Display------------------------------------------------------------------------

    //Display the Home Images
    blit(opening, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

    //Loop waiting for the user's interaction
    int timer=0;
    while(!key[KEY_ENTER]){
        rest(1000);
        timer++;
        if(timer>=120){//Close the menu after 2mins
            textout_centre_ex(screen, font, "Le jeu va se fermer", SCREEN_W / 2, SCREEN_H / 2 - 10, makecol(255, 255, 255), -1);
            rest(10000);
            exit(0);
        }
    }

    //Username selection interface
    clear(buffer);
    clear(screen);

        //First Player
        textout_centre_ex(screen, font, "Entrez votre pseudo Player 1:", SCREEN_W / 2, SCREEN_H / 2 - 10, makecol(255, 255, 255), -1);
        UsernameInput(PlayerList[PlayerTurn].Username);
            //Print
            textout_centre_ex(screen, font, "Pseudo du Player 1 enregistré:", SCREEN_W / 2, SCREEN_H / 2 + 10, makecol(255, 255, 255), -1);
            textout_centre_ex(screen, font, PlayerList[PlayerTurn].Username, SCREEN_W / 2, SCREEN_H / 2 + 30, makecol(255, 255, 255), -1);
        PlayerTurn^1;
        rest(1000);

        //Player Swap
        stretch_blit(PlayerSwap, screen, 0, 0, PlayerSwap->w, PlayerSwap->h, 0, 0, SCREEN_W, SCREEN_H);
        rest(2500);
        clear(screen);

        //Second Player
        textout_centre_ex(screen, font, "Entrez votre pseudo Player 2:", SCREEN_W / 2, SCREEN_H / 2 - 10, makecol(255, 255, 255), -1);
        UsernameInput(PlayerList[PlayerTurn].Username);
            //Print
            textout_centre_ex(screen, font, "Pseudo du Player 2 enregistré:", SCREEN_W / 2, SCREEN_H / 2 + 10, makecol(255, 255, 255), -1);
            textout_centre_ex(screen, font, PlayerList[PlayerTurn].Username, SCREEN_W / 2, SCREEN_H / 2 + 30, makecol(255, 255, 255), -1);
        PlayerTurn^1;
        rest(1000);
        clear(screen);

    while (Character.y + 64 < 690 && PlayerList[0].NbOfTickets!= 0 && PlayerList[1].NbOfTickets) {

        CharacterUpdate(&Character, Chemin_joueur_possible);

        blit(ECE_World_map, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        DrawCharacter(&Character, buffer);

        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

        FrameCounter++;
        if (FrameCounter >= 10) {
            if (Character.Moving) {
                Character.frame = (Character.frame + 1) % 4;
            } else {
                Character.frame = 0;
            }
            FrameCounter = 0;
        }
        rest(10);
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y + 1 + 64) == makecol(255, 0, 255 ) && key[KEY_ENTER]){
            //jeu_ne_pas_toucher_les_bords_electrique(&Player);
        }
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y + 1 + 64) == makecol(0, 255, 0 ) && key[KEY_ENTER]){
            //jeu_Snake(&Player);
        }
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y + 1 + 64) == makecol(255, 255, 255 ) && key[KEY_ENTER]){
            jackpot(&joueur,0);
            stretch_blit(PlayerSwap, screen, 0, 0, PlayerSwap->w, PlayerSwap->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            jackpot(&joueur,1);
        }
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y + 1 + 64) == makecol(100, 100, 100 ) && key[KEY_ENTER]){
            jeudeloie(&joueur);
        }
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y - 1 + 64) == makecol(255, 0, 0 ) && key[KEY_ENTER]){
           /* clear(screen);
            resultat_roue1 = jeu_RoueFor();
            stretch_blit(PlayerSwap, screen, 0, 0, PlayerSwap->w, PlayerSwap->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            clear(screen);
            resultat_roue2 = jeu_RoueFor();
            if(resultat_roue1<resultat_roue2){
                allegro_message("Le Player 1 a reçu un meilleur score. Il remporte un ticket du Player 2.");
                Player.NbOfTickets+=1;
                Player.ticket_j2-=1;

            }
            if(resultat_roue1>resultat_roue2){
                allegro_message("Le Player 2 a reçu un meilleur score. Il remporte un ticket du Player 1.");
                Player.ticket_j2+=1;
                Player.NbOfTickets-=1;
            }
            if(resultat_roue1==resultat_roue2){
                allegro_message("Les deux joueurs ont reçu le même score. Personne ne gagne de ticket.");
            }
            */
        }
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y - 1 + 64) == makecol(0, 0, 255 ) && key[KEY_ENTER]){

            /* clear(screen);
            resultat_guitar1=jeu_Guitar();
            stretch_blit(PlayerSwap, screen, 0, 0, PlayerSwap->w, PlayerSwap->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            clear(screen);
            resultat_guitar2=jeu_Guitar();
            if(resultat_guitar1<resultat_guitar2){
                allegro_message("Le Player 1 a reçu un meilleur score. Il remporte un ticket du Player 2.");
                Player.NbOfTickets+=1;
                Player.ticket_j2-=1;
            }
            if(resultat_guitar1>resultat_guitar2){
                allegro_message("Le Player 2 a reçu un meilleur score. Il remporte un ticket du Player 1.");
                Player.ticket_j2+=1;
                Player.NbOfTickets-=1;
            }
            if(resultat_guitar1==resultat_guitar2){
                allegro_message("Les deux joueurs ont reçu le même score. Personne ne gagne de ticket.");
            }
            */
        }


        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y - 1 + 64) == makecol(0, 255, 255 ) && key[KEY_ENTER]){
            clear(screen);
            BITMAP *regle_du_jeu= load_bitmap("Ressources/images/Regle_ballon.bmp",NULL);
            blit(regle_du_jeu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(5000);
            clear(screen);
            BallGameResultP1=jeu_ballon();
            stretch_blit(PlayerSwap, screen, 0, 0, PlayerSwap->w, PlayerSwap->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            clear(screen);
            BallGameResultP2=jeu_ballon();
            if(BallGameResultP1 < BallGameResultP2){
                allegro_message("%s a été le plus rapide. Il remporte un ticket du %s.", joueur.Username, joueur.pseudo_j2);
                joueur.NbOfTickets+=1;
                joueur.ballon_j1+=1;
                joueur.ticket_j2-=1;
                joueur.ballon_j2-=1;
            }
            if(BallGameResultP1 > BallGameResultP2){
                allegro_message("%s a été le plus rapide. Il remporte un ticket du %s.",joueur.pseudo_j2,joueur.Username);
                joueur.NbOfTickets-=1;
                joueur.ballon_j1-=1;
                joueur.ticket_j2+=1;
                joueur.ballon_j2+=1;
            }
            if(BallGameResultP1 == BallGameResultP2){
                allegro_message("Les 2 joueurs ont le même temps. Ils gagnent rien et perdent rien");
            }
        }
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y - 1 + 64) == makecol(255, 255, 0 ) && key[KEY_ENTER]){
            clear(screen);
            BITMAP *regle_du_jeu= load_bitmap("Ressources/images/regle_memoire.bmp",NULL);
            blit(regle_du_jeu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest(5000);
            clear(screen);
            resultat_memoire1=jeu_de_memoire();
            stretch_blit(PlayerSwap, screen, 0, 0, PlayerSwap->w, PlayerSwap->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(2500);
            clear(screen);
            resultat_memoire2=jeu_de_memoire();
            if(resultat_memoire1>resultat_memoire2){
                allegro_message("%s a été le plus loin. Il remporte un ticket du %s.", joueur.Username, joueur.pseudo_j2);
                joueur.NbOfTickets+=1;
                joueur.Memoire_j1+=1;
                joueur.ticket_j2-=1;
                joueur.Memoire_j2-=1;
            }
            if(resultat_memoire1<resultat_memoire2){
                allegro_message("%s a été le plus loin. Il remporte un ticket du %s.",joueur.pseudo_j2,joueur.Username);
                joueur.NbOfTickets-=1;
                joueur.Memoire_j1-=1;
                joueur.ticket_j2+=1;
                joueur.Memoire_j2+=1;
            }
            if(resultat_memoire1==resultat_memoire2){
                allegro_message("Les 2 joueurs ont le même score. Ils gagnent rien et perdent rien");
            }
        }
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y - 1 + 64) == makecol(100, 0, 100 ) && key[KEY_ENTER]){
            allegro_message("%s : %d tickets\n %s : %d tickets\n\n Tickets gagné et perdu joueur1:\n Snake: %d   Eclaire: %d   Ballon: %d   Memoire: %d   Oie: %d   Jackpot: %d   \nGuitar: %d   RoueFortune: %d\n\nTickets gagné et perdu joueur2:\n Snake: %d   Eclaire: %d   Ballon: %d   Memoire: %d   Oie: %d   Jackpot: %d   \nGuitar: %d   RoueFortune: %d\n\n", joueur.Username, joueur.NbOfTickets, joueur.pseudo_j2, joueur.ticket_j2, joueur.Snake_j1, joueur.Eclaire_j1, joueur.ballon_j1, joueur.Memoire_j1, joueur.Goose, joueur.Jackpot_j1, joueur.Guitar_j1, joueur.RoueF_j1, joueur.Snake_j2, joueur.Eclaire_j2, joueur.ballon_j2, joueur.Memoire_j2, joueur.Oie_j2, joueur.Jackpot_j2, joueur.Guitar_j2, joueur.RoueF_j2);
        }
    }

    if (joueur.NbOfTickets == 0 && joueur.ticket_j2 != 0){
        allegro_message("%s a gagné.",joueur.pseudo_j2);
    }
    if (joueur.NbOfTickets != 0 && joueur.ticket_j2 == 0){
        allegro_message("%s a gagné.",joueur.Username);
    }
    if (joueur.NbOfTickets == 0 && joueur.ticket_j2 == 0){
        allegro_message("Les 2 joueurs ont perdu.");
    }
    allegro_message("See you next time ! ;)");

    destroy_bitmap(buffer);
    destroy_bitmap(ECE_World_map);
    destroy_bitmap(Chemin_joueur_possible);
    destroy_bitmap(Personnage);
    for (int i = 0; i < 4; i++) {
        destroy_bitmap(Character.Down[i]);
        destroy_bitmap(Character.Left[i]);
        destroy_bitmap(Character.Right[i]);
        destroy_bitmap(Character.UP[i]);
    }
    allegro_exit();
    return 0;

}

END_OF_MAIN();

