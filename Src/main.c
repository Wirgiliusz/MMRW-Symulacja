#include <stdio.h>
#include "..\Inc\robot.h"

// Definicja labiryntu na podstawie: W (gora), A (lewo), S (dol), D (prawo).
#define A 182
#define D 199
#define W 207
#define S 209
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
    //printf("%c", 197);
    printf("PosX: %d \nPosY: %d \n", robot.posX, robot.posY);
    jedzPrawo(&robot);
    jedzProsto(&robot);
    printf("PosX: %d \nPosY: %d \n", robot.posX, robot.posY);


    return 0;
}