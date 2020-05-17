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


int main() {
    Robot robot = konstruktorRobota(0, 0, Wschod); 	// Obiekt robota (pozycja x, pozycja y, orientacja)
    const unsigned int tabLabiryntu[8][8] = {   {D, AD, ASD, AD, AS, SD, ASD, A}, 
                                                {D, ASD, WA, S, WS, WS, WD, AS}, 
                                                {S, WS, SD, WAS, WD, WAD, AS, W},
                                                {WSD, WA, WS, WSD, AS, S, WD, AS},
                                                {WS, D, WAS, WD, WA, WSD, AD, WA},
                                                {WSD, A, WSD, A, SD, WASD, AD, AS},
                                                {WSD, ASD, WAS, D, WA, WS, D, WAS},
                                                {W, W, WD, AD, AD, WAD, AD, WA} };


    narysujLabirynt(tabLabiryntu);
    znajdzNajkrotszaSciezkeStart(&robot);
    narysujWartosci(robot.tabSciezki);
    przejedzLabirynt(&robot);

    return 0;
}