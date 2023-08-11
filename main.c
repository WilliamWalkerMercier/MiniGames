#include "link.h"


int main() {
    srand(time(NULL));
    AllegroInitialisation();

    //Creation of bitmaps that we will use to display the lobby
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *source_ECE_World_map = load_bitmap("Ressources/Lobby/ECE_World_map.bmp", NULL);
    BITMAP *source_Chemin_joueur_possible = load_bitmap("Ressources/Lobby/Chemin_possible.bmp", NULL);
    BITMAP *Personnage = load_bitmap("Ressources/Lobby/Character.bmp", NULL);
    BITMAP *PlayerSwap = load_bitmap("Ressources/Lobby/changement_de_joueur.bmp", NULL);
    BITMAP *opening = load_bitmap("Ressources/Lobby/ECE_World_op.bmp", NULL);

    //Variable Declaration
    int FrameCounter = 0;
    int PlayerTurn = 0; // 0 or 1 for value

    //Struct Initialisation
    //Character
    sCharacter Character;
    Character.direction = 0;
    Character.frame = 0;
    Character.x = SCREEN_W / 2;
    Character.y = SCREEN_H / 2;

    //Player
    sPlayer PlayerList[2];
    for (int i = 0; i < 2; i++) {
        PlayerList[i].NbOfTickets = 5;
        PlayerList[i].Goose = 0;
        PlayerList[i].Lightning = 0;
        PlayerList[i].Memory = 0;
        PlayerList[i].Ball = 0;
        PlayerList[i].CasinoRoyal = 0;
    }



    //Resizing the path of the map
    BITMAP *Chemin_joueur_possible = create_bitmap(SCREEN_W, SCREEN_H);
    stretch_blit(source_Chemin_joueur_possible, Chemin_joueur_possible, 0, 0, source_Chemin_joueur_possible->w,
                 source_Chemin_joueur_possible->h, 0, 0, SCREEN_W, SCREEN_H);
    destroy_bitmap(source_Chemin_joueur_possible);

    //Resizing the World's Map
    BITMAP *ECE_World_map = create_bitmap(SCREEN_W, SCREEN_H);
    stretch_blit(source_ECE_World_map, ECE_World_map, 0, 0, source_ECE_World_map->w, source_ECE_World_map->h, 0, 0,
                 SCREEN_W, SCREEN_H);
    destroy_bitmap(source_ECE_World_map);

    //Splitting the character bitmap into small bitmap that just contains one frame
    SplitCharacterBitmap(&Character, Personnage);

//------------------------------------------------------------------------Start of the Display------------------------------------------------------------------------

    //Display the Home Images
    blit(opening, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

    //Loop waiting for the user's interaction
    int timer = 0;
    while (!key[KEY_ENTER]) {
        rest(995);
        timer++;
        if (timer >= 120) {//Close the menu after 2mins
            textout_centre_ex(screen, font, "Le jeu va se fermer", SCREEN_W / 2, SCREEN_H / 2 - 10,
                              makecol(255, 255, 255), -1);
            rest(10000);
            exit(0);
        }
    }

    //Username selection interface
    clear(buffer);
    clear(screen);

    //First Player
    textout_centre_ex(screen, font, "Entrez votre pseudo Player 1:", SCREEN_W / 2, SCREEN_H / 2 - 10,
                      makecol(255, 255, 255), -1);
    UsernameInput(PlayerList[PlayerTurn].Username);
    //Print
    textout_centre_ex(screen, font, "Pseudo du Player 1 enregistré:", SCREEN_W / 2, SCREEN_H / 2 + 10,
                      makecol(255, 255, 255), -1);
    textout_centre_ex(screen, font, PlayerList[PlayerTurn].Username, SCREEN_W / 2, SCREEN_H / 2 + 30,
                      makecol(255, 255, 255), -1);
    PlayerTurn ^ 1;
    rest(1000);

    //Player Swap
    stretch_blit(PlayerSwap, screen, 0, 0, PlayerSwap->w, PlayerSwap->h, 0, 0, SCREEN_W, SCREEN_H);
    rest(2500);
    clear(screen);

    //Second Player
    textout_centre_ex(screen, font, "Entrez votre pseudo Player 2:", SCREEN_W / 2, SCREEN_H / 2 - 10,
                      makecol(255, 255, 255), -1);
    UsernameInput(PlayerList[PlayerTurn].Username);
    //Print
    textout_centre_ex(screen, font, "Pseudo du Player 2 enregistré:", SCREEN_W / 2, SCREEN_H / 2 + 10,
                      makecol(255, 255, 255), -1);
    textout_centre_ex(screen, font, PlayerList[PlayerTurn].Username, SCREEN_W / 2, SCREEN_H / 2 + 30,
                      makecol(255, 255, 255), -1);
    PlayerTurn ^ 1;
    rest(1000);
    clear(screen);

//Lobby loop --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    while (Character.y + 64 < 690 && PlayerList[0].NbOfTickets != 0 && PlayerList[1].NbOfTickets) {
        //[*] Manage the character animation
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
        //[*]
        rest(10);
        /*Game Interaction where the player go where the game image is and interact with it
            Same parameters for every game:
                -We only send the tab with the player infos
                -The number of tickets, the player swap animation and who wins is determined in the mini game program */

        //Electrical Game
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y + 1 + 64) == makecol(255, 0, 255) &&
            key[KEY_ENTER]) {
            //jeu_ne_pas_toucher_les_bords_electrique(&Player);
        }
        //In the previous version, it was a Snake Game but we will change it later
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y + 1 + 64) == makecol(0, 255, 0) &&
            key[KEY_ENTER]) {
            exit(0);
        }
        //Casino Royal Party but we only have for now the jackpot Game
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y + 1 + 64) == makecol(255, 255, 255) &&
            key[KEY_ENTER]) {
            jackpot(PlayerList, 0);
        }
        //Goose Game
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y + 1 + 64) == makecol(100, 100, 100) &&
            key[KEY_ENTER]) {
            jeudeloie(PlayerList);
        }
        //In the previous version, it was a turn the wheel game but we will change it
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y - 1 + 64) == makecol(255, 0, 0) &&
            key[KEY_ENTER]) {
            exit(0);
        }
        //In the previous version, it was a guitar hero  game but we will change it
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y - 1 + 64) == makecol(0, 0, 255) &&
            key[KEY_ENTER]) {
        }
        //Ball Game
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y - 1 + 64) == makecol(0, 255, 255) &&
            key[KEY_ENTER]) {
        }
        if (getpixel(Chemin_joueur_possible, Character.x + 32, Character.y - 1 + 64) == makecol(255, 255, 0) && key[KEY_ENTER]) {
            exit(0);
        }

    }
    allegro_exit();
    return 0;
}

END_OF_MAIN();

