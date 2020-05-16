#include <stdio.h>
#include <stdint.h>
#include "..\Inc\robot.h"

// Definicja labiryntu na podstawie: W (gora), A (lewo), S (dol), D (prawo).
#define W 202
#define A 185
#define S 203
#define D 204
#define WS 179
#define SA 191
#define WD 192
#define DA 196
#define WA 217
#define DS 218
#define WSA 180
#define WDA 193
#define DSA 194
#define WDS 195
#define WDSA 197


int main() {
    Robot robot = {0, 0, 1}; 	// Obiekt robota (pozycja x, pozycja y, orientacja)
    char tabLabiryntu[8][8] = { {D, DA, DSA, DA, SA, DS, DSA, A}, 
                                {D, DSA, WA, S, WS, WS, WD, SA}, 
                                {S, WS, DS, WSA, WD, WDA, SA, W},
                                {WDS, WA, WS, WDS, SA, S, WD, SA},
                                {WS, D, WSA, WD, WA, WDS, DA, WA},
                                {WDS, A, WDS, A, DS, WDSA, DA, SA},
                                {WDS, DSA, WSA, D, WA, WS, D, WSA},
                                {W, W, WD, DA, DA, WDA, DA, WA} };

    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            printf("%c", tabLabiryntu[i][j]);
        }
        printf("\n");
    }
    
    /*
    printf("PosX: %d \nPosY: %d \n", robot.posX, robot.posY);
    jedzPrawo(&robot);
    jedzProsto(&robot);
    printf("PosX: %d \nPosY: %d \n", robot.posX, robot.posY);
    */

    return 0;
}