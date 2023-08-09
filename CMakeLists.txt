cmake_minimum_required(VERSION 3.26)
project(MiniGames C)

set(CMAKE_CXX_STANDARD 99)


add_executable(MiniGames main.c jackpot.c ballon.c case_memoire.c jeudeloie.c Ne_pas_toucher_les_bords_electrique.c
        InitialisationAllegro.c
        LobbyTools.c)

target_link_libraries(MiniGames -lmingw32 -lalleg44)