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
            printf("%d", wartosci[i][j]);
        }
        printf("\n");
    }
}

void znajdzNajkrotszaSciezkeRekurencja(int tabSciezki[8][8], const unsigned int labirynt[][8], int posX, int posY) {
    if(labirynt[posY][posX] == W) {
        tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == A) {
        tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == S) {
        tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == D) {
        tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == WS) {
        tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == AS) {
        tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == WD) {
        tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == AD) {
        tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == WA) {
        tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == SD) {
        tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == WAS) {
        tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == WAD) {
        tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == ASD) {
        tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == WSD) {
        tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
    }
    if(labirynt[posY][posX] == WASD) {
        tabSciezki[posY-1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX-1] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY+1][posX] = tabSciezki[posY][posX] + 1;
        tabSciezki[posY][posX+1] = tabSciezki[posY][posX] + 1;
    }
}

void znajdzNajkrotszaSciezkeStart(const unsigned int labirynt[][8]) {
    int tabSciezki[8][8] = {0};
    int posX = 2;
    int posY = 0;

    znajdzNajkrotszaSciezkeRekurencja(tabSciezki, labirynt, posX, posY);
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

    narysujLabirynt(tabLabiryntu);
    znajdzNajkrotszaSciezkeStart(tabLabiryntu);

    return 0;
}