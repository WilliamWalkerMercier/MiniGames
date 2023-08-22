
#include "link.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700


void RandomDot(int tableau_de_point[21]){
    for (int i = 0; i < 21; ++i) {
        tableau_de_point[i] = 50 + rand()%581;
        for (int j = 0; j < i ; ++j) {
            if (tableau_de_point[j] == tableau_de_point[i] ){
                i--;
            }
        }
    }
}

void Sort(int tableau_de_point[21]){
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

void PathPrint(BITMAP *buffer, int tableau_de_point[21], BITMAP *background){
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

void ElectricityGame(sPlayer prTab[2], BITMAP *PlayerSwap){

    //Variable Declaration
    int tabDot[21];
    time_t StartTime, EndTime, Player1Time, Player2Time,ActualTime;

   //Bitmap Declaration
    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP *source_background = load_bitmap("ressources/ElectricityGame/LightningBackground.bmp",NULL);

    //Resize lightning image
    BITMAP *background = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    stretch_blit(source_background, background, 0, 0, source_background->w, source_background->h, 0, 0, background->w, background->h);

    //Show the cursor on the screen
    show_mouse(screen);

    //Generates randomly the dot tab
    RandomDot(tabDot);

    //Sort the dottab
    Sort(tabDot);

    //Game Loop
    for (int i = 0; i < 2; ++i) {

        //Draw the start platform
        rectfill(buffer, 0, 0, 50, 50, Green);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


        while (getpixel(buffer, mouse_x, mouse_y) != (Green)) {
        }
        rest(500);
        clear(screen);
        clear(buffer);

        //Show the Path
        PathPrint(buffer, tabDot, background);
        PathPrint(buffer, tabDot, background);
        PathPrint(buffer, tabDot, background);

        //Initialisation of the time
        StartTime = time(NULL);
        ActualTime=time(NULL);


        //Loop that verify if the mouse cursor in on the white path
        while (getpixel(buffer, mouse_x, mouse_y) == White && ActualTime-StartTime<=60000) {
            PathPrint(buffer, tabDot, background);
            ActualTime=time(NULL);
        }
        EndTime = time(NULL);

        //Check if the player has arrived at the end of the game
        if (getpixel(buffer, mouse_x, mouse_y) == Purple) {
            if (i == 0){
                Player1Time = EndTime - StartTime;
                //allegro_message("Player 1 time is %ld",Player1Time);
            }
            if (i == 1){
                Player2Time = EndTime - StartTime;
                //allegro_message("Player 2 time is %ld",Player2Time);
            }
        } else{
            //Condition when the player doesn't get to the end
            if (i==0){
                Player1Time = EndTime;
                //allegro_message("Player 1 time is %ld",Player1Time);

            }
            if (i == 1){
                Player2Time =EndTime;
                //allegro_message("Player 2 time is %ld",Player2Time);
            }
        }
        clear(buffer);
        clear(screen);
        if (i == 0){
            stretch_blit(PlayerSwap, screen, 0, 0, PlayerSwap->w, PlayerSwap->h, 0, 0, SCREEN_W, SCREEN_H);
            rest(5000);
        }
    }
    //Attributes the ticket for each player
    if (Player1Time < Player2Time){
        prTab[0].NbOfTickets++;
        prTab[1].NbOfTickets--;
        prTab[0].Lightning++;
        prTab[1].Lightning--;
        allegro_message("Player 1 went the furthest and was the fastest. He wins a ticket");
    }
    if (Player1Time > Player2Time){
        prTab[1].NbOfTickets++;
        prTab[0].NbOfTickets--;
        prTab[1].Lightning++;
        prTab[0].Lightning--;
        allegro_message("Player 2 went the furthest and was the fastest. He wins a ticket ");
    }
    if (Player1Time == Player2Time){
        allegro_message("The players have done the same time, they don't lose or win any tickets.");
    }

    //Destroying the variables to free some memory space
    destroy_bitmap(buffer);
    destroy_bitmap(background);
    destroy_bitmap(source_background);
}