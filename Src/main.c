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

void znajdzNajkrotszaSciezkeRekurencja(int tabSciezki[8][8], const unsigned int labirynt[][8], int posX, int posY) {
    // Okropienstwo, prosze nie patrzec
    switch(labirynt[posY][posX]) {
        case W:
            if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY-1);
            }
            
        break;
        case A:
            if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX-1, posY);
            }
        break;
        case S:
            if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY+1);
            }         
        break;
        case D:
            if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX+1, posY);
            }  
        break;
        case WS:
            if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY-1);
            }
            if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY+1);
            }  
        break;
        case AS:
            if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX-1, posY);
            }
            if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY+1);
            }
        break;
        case WD:
            if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY-1);
            }
            if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX+1, posY);
            }
        break;
        case AD:
            if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX-1, posY);
            }
            if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX+1, posY);
            }
        break;
        case WA:
            if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY-1);
            }
            if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX-1, posY);
            }
        break;
        case SD:
            if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY+1);
            }
            if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX+1, posY);
            }
        break;
        case WAS:
            if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY-1);
            }
            if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX-1, posY);
            }
            if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY+1);
            }
        break;
        case WAD:
            if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY-1);
            }
            if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX-1, posY);
            }
            if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX+1, posY);
            }
        break;
        case ASD:
            if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX-1, posY);
            }
            if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY+1);
            }
            if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX+1, posY);
            }
        break;
        case WSD:
            if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY-1);
            }
            if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY+1);
            }
            if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX+1, posY);
            }
        break;
        case WASD:
            if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY-1);
            }
            if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX-1, posY);
            }
            if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
                tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY+1);
            }
            if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
                tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
                znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX+1, posY);
            }
        break;
    }
}

void znajdzNajkrotszaSciezkeStart(const unsigned int labirynt[][8]) {
    int tabSciezki[8][8] = {0};
    int posX = 0;
    int posY = 0;

    znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY);
    tabSciezki[0][0] = 0;
    narysujWartosci(tabSciezki);
}

void znajdzNajkrotszaSciezkeRekurencjaBIN(int tabSciezki[8][8], const unsigned char labirynt[][8], int posX, int posY) {
    if(labirynt[posY][posX] & NORTH) {
        if(!tabSciezki[posY-1][posX] || tabSciezki[posY-1][posX] > tabSciezki[posY][posX] ) {
            tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencjaBIN(tabSciezki, labirynt, posX, posY-1);
        }
    }

    if(labirynt[posY][posX] & WEST) {
        if(!tabSciezki[posY][posX-1] || tabSciezki[posY][posX-1] > tabSciezki[posY][posX] ) {
            tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencjaBIN(tabSciezki, labirynt, posX-1, posY);
        }
    }

    if(labirynt[posY][posX] & SOUTH) {
        if(!tabSciezki[posY+1][posX] || tabSciezki[posY+1][posX] > tabSciezki[posY][posX] ) {
            tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencjaBIN(tabSciezki, labirynt, posX, posY+1);
        }     
    }

    if(labirynt[posY][posX] & EAST) {
        if(!tabSciezki[posY][posX+1] || tabSciezki[posY][posX+1] > tabSciezki[posY][posX] ) {
            tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencjaBIN(tabSciezki, labirynt, posX+1, posY);
        }  
    }
}

void znajdzNajkrotszaSciezkeStartBIN(const unsigned char labirynt[][8]) {
    int tabSciezki[8][8] = {0};
    int posX = 0;
    int posY = 0;

    znajdzNajkrotszaSciezkeRekurencjaBIN(tabSciezki, labirynt, posX, posY);
    tabSciezki[0][0] = 0;
    narysujWartosci(tabSciezki);
}




int main() {
    Robot robot = {0, 0, 1}; 	// Obiekt robota (pozycja x, pozycja y, orientacja)
    const unsigned int tabLabiryntu[8][8] = { {D, AD, ASD, AD, AS, SD, ASD, A}, 
                                {D, ASD, WA, S, WS, WS, WD, AS}, 
                                {S, WS, SD, WAS, WD, WAD, AS, W},
                                {WSD, WA, WS, WSD, AS, S, WD, AS},
                                {WS, D, WAS, WD, WA, WSD, AD, WA},
                                {WSD, A, WSD, A, SD, WASD, AD, AS},
                                {WSD, ASD, WAS, D, WA, WS, D, WAS},
                                {W, W, WD, AD, AD, WAD, AD, WA} };

    const unsigned char tabLabiryntuBin[8][8] = { {EAST, WEST|EAST, WEST|SOUTH|EAST, WEST|EAST, WEST|SOUTH, WEST|EAST, WEST|SOUTH|EAST, WEST}, 
                                {EAST, WEST|SOUTH|EAST, NORTH|WEST, SOUTH, NORTH|SOUTH, NORTH|SOUTH, NORTH|EAST, WEST|SOUTH}, 
                                {SOUTH, NORTH|SOUTH, WEST|EAST, NORTH|WEST|SOUTH, NORTH|EAST, NORTH|WEST|EAST, WEST|SOUTH, NORTH},
                                {NORTH|SOUTH|EAST, NORTH|WEST, NORTH|SOUTH, NORTH|SOUTH|EAST, WEST|SOUTH, SOUTH, NORTH|EAST, WEST|SOUTH},
                                {NORTH|SOUTH, EAST, NORTH|WEST|SOUTH, NORTH|EAST, NORTH|WEST, NORTH|SOUTH|EAST, WEST|EAST, NORTH|WEST},
                                {NORTH|SOUTH|EAST, WEST, NORTH|SOUTH|EAST, WEST, WEST|EAST, WASD, WEST|EAST, WEST|SOUTH},
                                {NORTH|SOUTH|EAST, WEST|SOUTH|EAST, NORTH|WEST|SOUTH, EAST, NORTH|WEST, NORTH|SOUTH, EAST, NORTH|WEST|SOUTH},
                                {NORTH, NORTH, NORTH|EAST, WEST|EAST, WEST|EAST, NORTH|WEST|EAST, WEST|EAST, NORTH|WEST} };

    narysujLabirynt(tabLabiryntu);
    //znajdzNajkrotszaSciezkeStart(tabLabiryntu);
    znajdzNajkrotszaSciezkeStartBIN(tabLabiryntuBin);


    return 0;
}