#include <stdio.h>
#include <stdint.h>
#include "..\Inc\robot.h"

// Definicja labiryntu na podstawie: W (gora), A (lewo), S (dol), D (prawo).
#define A 185
#define D 204
#define W 202
#define S 203
#define WS 179
#define WAS 180
#define AS 191
#define WD 192
#define AWD 193
#define ASD 194
#define WDS 195
#define AD 196
#define WASD 197
#define AW 217
#define DS 218

int main() {
    Robot robot = {0, 0, 1}; 	// Obiekt robota (pozycja x, pozycja y, orientacja)
    char tabLabiryntu[8][8] = { {D, AD, ASD, AD, AS, DS, ASD, A}, 
                                {D, ASD, AW, S, WS, WS, WD, AS}, 
                                {S, WS, DS, WAS, WD, AWD, AS, W},
                                {WDS, AW, WS, WDS, AS, S, WD, AS},
                                {WS, D, WAS, WD, AW, WDS, AD, AW},
                                {WDS, A, WDS, A, DS, WASD, AD, AS},
                                {WDS, ASD, WAS, D, AW, WS, D, WAS},
                                {W, W, WD, AD, AD, AWD, AD, AW} };

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