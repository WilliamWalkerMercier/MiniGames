//
// Created by Willyson on 09/08/2023.
//
#include "link.h"

void AllegroInitialisation(){
    allegro_init();
    install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
    install_keyboard();

    install_mouse();

    if(install_keyboard()==-1){
        allegro_message("prb clavier\n %s",allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    if(install_mouse()==-1){
        allegro_message("prb souris\n %s",allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    set_color_depth(32);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1000,700,0,0)!=0){
        allegro_message("prb GFX mode \n %s",allegro_error);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse((screen));
}