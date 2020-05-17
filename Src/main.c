#include <stdio.h>
#include <stdint.h>
#include "..\Inc\robot.h"

// Definicja labiryntu na podstawie { W (gora), A (lewo), S (dol), D (prawo).
#define W 202
#define A 185
#define S 203
#define D 204
#define WS 179
#define AS 191
#define WD 192
#define AD 196
#define WA 217
#define SD 218
#define WAS 180
#define WAD 193
#define ASD 194
#define WSD 195
#define WASD 197

#define NORTH   1 //00001000
#define WEST    2 //00000100
#define SOUTH   4 //00000010
#define EAST    8 //00000001

void narysujLabirynt(const unsigned int labirynt[][8]) {
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            printf("%c", labirynt[i][j]);
        }
        printf("\n");
    }
}

void narysujWartosci(int wartosci[][8]) {
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            printf("%d\t", wartosci[i][j]);
        }
        printf("\n");
    }
}

void znajdzNajkrotszaSciezkeRekurencja(int tabSciezki[8][8], const unsigned char labirynt[][8], int posX, int posY) {
    // Czy osiagnieta zostala meta
    /*
    if(posX == 3 || posX == 4) {
        if(posY == 3 || posY == 4) {
            return;
        }
    }
    */
   // Czy osiagniety zostal start
   if(posX == 0 && posY == 0) {
       return;
   }

    // Przejscie do kolejnego pola w zaleznosci od mozliwych polaczen
    if(labirynt[posY][posX] & NORTH) {
        if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
            tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY-1);
        }
    }
    if(labirynt[posY][posX] & WEST) {
        if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
            tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX-1, posY);
        }
    }
    if(labirynt[posY][posX] & SOUTH) {
        if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
            tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY+1);
        }     
    }
    if(labirynt[posY][posX] & EAST) {
        if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
            tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX+1, posY);
        }  
    }
}

void znajdzNajkrotszaSciezkeStart(const unsigned char labirynt[][8]) {
    int tabSciezki[8][8] = {0};
    int posX = 3;
    int posY = 3;

    znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY);
    tabSciezki[posX][posY] = 0;
    narysujWartosci(tabSciezki);
}

void przejedzLabirynt(int tabSciezki[][8], const unsigned char labirynt[][8]) {
    int posX = 0;
    int posY = 0;

    while(posX != 3 && posY != 3) {
        if(labirynt[posY][posX] & NORTH) {
            if(!tabSciezki[posY-1][posX] == tabSciezki[posY-1][posX] - 1) {
                // jedz
            }
        }
        if(labirynt[posY][posX] & WEST) {
            if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
                // jedz
            }
        }
        if(labirynt[posY][posX] & SOUTH) {
            if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
                // jedz
            }     
        }
        if(labirynt[posY][posX] & EAST) {
            if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
                // jedz
            }  
        }
    }
}


int main() {
    Robot robot = {0, 0, 1}; 	// Obiekt robota (pozycja x, pozycja y, orientacja)
    const unsigned int tabLabiryntu[8][8] = {   {D, AD, ASD, AD, AS, SD, ASD, A}, 
                                                {D, ASD, WA, S, WS, WS, WD, AS}, 
                                                {S, WS, SD, WAS, WD, WAD, AS, W},
                                                {WSD, WA, WS, WSD, AS, S, WD, AS},
                                                {WS, D, WAS, WD, WA, WSD, AD, WA},
                                                {WSD, A, WSD, A, SD, WASD, AD, AS},
                                                {WSD, ASD, WAS, D, WA, WS, D, WAS},
                                                {W, W, WD, AD, AD, WAD, AD, WA} };

    const unsigned char tabLabiryntuBin[8][8] = {   {EAST,              WEST|EAST,              WEST|SOUTH|EAST,    WEST|EAST,          WEST|SOUTH,     WEST|EAST,              WEST|SOUTH|EAST,    WEST}, 
                                                    {EAST,              WEST|SOUTH|EAST,        NORTH|WEST,         SOUTH,              NORTH|SOUTH,    NORTH|SOUTH,            NORTH|EAST,         WEST|SOUTH}, 
                                                    {SOUTH,             NORTH|SOUTH,            SOUTH|EAST,          NORTH|WEST|SOUTH,   NORTH|EAST,     NORTH|WEST|EAST,        WEST|SOUTH,         NORTH},
                                                    {NORTH|SOUTH|EAST,  NORTH|WEST,             NORTH|SOUTH,        NORTH|SOUTH|EAST,   WEST|SOUTH,     SOUTH,                  NORTH|EAST,         WEST|SOUTH},
                                                    {NORTH|SOUTH,       EAST,                   NORTH|WEST|SOUTH,   NORTH|EAST,         NORTH|WEST,     NORTH|SOUTH|EAST,       WEST|EAST,          NORTH|WEST},
                                                    {NORTH|SOUTH|EAST,  WEST,                   NORTH|SOUTH|EAST,   WEST,               SOUTH|EAST,     NORTH|WEST|SOUTH|EAST,  WEST|EAST,          WEST|SOUTH},
                                                    {NORTH|SOUTH|EAST,  WEST|SOUTH|EAST,        NORTH|WEST|SOUTH,   EAST,               NORTH|WEST,     NORTH|SOUTH,            EAST,               NORTH|WEST|SOUTH},
                                                    {NORTH,             NORTH,                  NORTH|EAST,         WEST|EAST,          WEST|EAST,      NORTH|WEST|EAST,        WEST|EAST,          NORTH|WEST} };

    narysujLabirynt(tabLabiryntu);
    znajdzNajkrotszaSciezkeStart(tabLabiryntuBin);

    return 0;
}