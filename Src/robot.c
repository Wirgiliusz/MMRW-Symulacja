/*
 * robot.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */
#include "..\Inc\robot.h"
#include <stdio.h>

Robot konstruktorRobota(int poczatkoweX, int poczatkoweY, enum Orientacje poczatkowaOrientacja) {
    Robot robot;
    robot.posX = poczatkoweX;
    robot.posY = poczatkoweY;
    robot.orientacja = poczatkowaOrientacja;
    unsigned char tabLabiryntuTemp[8][8] = {    {EAST,              WEST|EAST,              WEST|SOUTH|EAST,    WEST|EAST,          WEST|SOUTH,     SOUTH|EAST,             WEST|SOUTH|EAST,    WEST}, 
                                                {EAST,              WEST|SOUTH|EAST,        NORTH|WEST,         SOUTH,              NORTH|SOUTH,    NORTH|SOUTH,            NORTH|EAST,         WEST|SOUTH}, 
                                                {SOUTH,             NORTH|SOUTH,            SOUTH|EAST,         NORTH|WEST|SOUTH,   NORTH|EAST,     NORTH|WEST|EAST,        WEST|SOUTH,         NORTH},
                                                {NORTH|SOUTH|EAST,  NORTH|WEST,             NORTH|SOUTH,        NORTH|SOUTH|EAST,   WEST|SOUTH,     SOUTH,                  NORTH|EAST,         WEST|SOUTH},
                                                {NORTH|SOUTH,       EAST,                   NORTH|WEST|SOUTH,   NORTH|EAST,         NORTH|WEST,     NORTH|SOUTH|EAST,       WEST|EAST,          NORTH|WEST},
                                                {NORTH|SOUTH|EAST,  WEST,                   NORTH|SOUTH|EAST,   WEST,               SOUTH|EAST,     NORTH|WEST|SOUTH|EAST,  WEST|EAST,          WEST|SOUTH},
                                                {NORTH|SOUTH|EAST,  WEST|SOUTH|EAST,        NORTH|WEST|SOUTH,   EAST,               NORTH|WEST,     NORTH|SOUTH,            EAST,               NORTH|WEST|SOUTH},
                                                {NORTH,             NORTH,                  NORTH|EAST,         WEST|EAST,          WEST|EAST,      NORTH|WEST|EAST,        WEST|EAST,          NORTH|WEST} };
    /*unsigned char tabLabiryntuTemp[4][4] = {    {EAST,              WEST|EAST,              WEST|SOUTH|EAST,    SOUTH}, 
                                                {EAST,              WEST|SOUTH|EAST,        NORTH|WEST|EAST,    NORTH|WEST}, 
                                                {SOUTH,             NORTH|SOUTH,            EAST,               NORTH|WEST|SOUTH},
                                                {NORTH|EAST,        WEST|NORTH|EAST,        WEST|EAST,          NORTH|WEST} };*/
    unsigned char labiryntPoznawany[8][8];
    //unsigned char labiryntPoznawany[4][4];

    
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            robot.tabLabiryntuBin[i][j] = tabLabiryntuTemp[i][j];
            robot.tabSciezki[i][j] = 0;
            robot.obecnosc[i][j] = 0;
            robot.labiryntPoznawany[i][j] = 0;
        }
    }
    /*
   for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            robot.tabLabiryntuBin[i][j] = tabLabiryntuTemp[i][j];
            robot.tabSciezki[i][j] = 0;
            robot.obecnosc[i][j] = 0;
            robot.labiryntPoznawany[i][j] = 0;
        }
    } 
    */

    return robot;
}


void jedzProsto(Robot* robot) {
	switch(robot->orientacja) {
	case Polnoc:
		robot->posY--;
		break;
	case Zachod:
		robot->posX--;
		break;
	case Poludnie:
		robot->posY++;
		break;
	case Wschod:
		robot->posX++;
		break;
	}
}

void obroc(Robot* robot, enum Strony strona) {
	switch(strona) {
        case Lewo:
            robot->orientacja++;
            robot->orientacja %=4;
        break;
        case Prawo:
            robot->orientacja--;
            robot->orientacja %=4;
        break;
	}
}

void jedzPrawo(Robot* robot) {
	obroc(robot, Prawo);
	jedzProsto(robot);
}

void jedzLewo(Robot* robot) {
	obroc(robot, Lewo);
	jedzProsto(robot);
}

void jedzTyl(Robot* robot) {
	obroc(robot, Prawo);
	obroc(robot, Prawo);
	jedzProsto(robot);
}

void jedzKierunek(Robot* robot, enum Orientacje kierunek) {
    switch(kierunek) {
        case Polnoc:
            if(robot->orientacja == Polnoc) {
                jedzProsto(robot);
            } 
            else if(robot->orientacja == Zachod) {
                jedzPrawo(robot);
            }
            else if(robot->orientacja == Poludnie) {
                jedzTyl(robot);
            }
            else if(robot->orientacja == Wschod) {
                jedzLewo(robot);
            }
        break;

        case Zachod:
            if(robot->orientacja == Polnoc) {
                jedzLewo(robot);
            } 
            else if(robot->orientacja == Zachod) {
                jedzProsto(robot);
            }
            else if(robot->orientacja == Poludnie) {
                jedzPrawo(robot);
            }
            else if(robot->orientacja == Wschod) {
                jedzTyl(robot);
            }
        break;

        case Poludnie:
            if(robot->orientacja == Polnoc) {
                jedzTyl(robot);
            } 
            else if(robot->orientacja == Zachod) {
                jedzLewo(robot);
            }
            else if(robot->orientacja == Poludnie) {
                jedzProsto(robot);
            }
            else if(robot->orientacja == Wschod) {
                jedzPrawo(robot);
            }
        break;

        case Wschod:
            if(robot->orientacja == Polnoc) {
                jedzPrawo(robot);
            } 
            else if(robot->orientacja == Zachod) {
                jedzTyl(robot);
            }
            else if(robot->orientacja == Poludnie) {
                jedzLewo(robot);
            }
            else if(robot->orientacja == Wschod) {
                jedzProsto(robot);
            }
        break;
    }
}

void znajdzNajkrotszaSciezkeRekurencja(Robot* robot, int posX, int posY) {
   // Czy osiagniety zostal start
   if(posX == 0 && posY == 0) {
       return;
   }

    // Przejscie do kolejnego pola w zaleznosci od mozliwych polaczen
    if(robot->labiryntPoznawany[posY][posX] & NORTH) {
        if(!robot->tabSciezki[posY-1][posX] || robot->tabSciezki[posY-1][posX] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY-1][posX] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX, posY-1);
        }
    }
    if(robot->labiryntPoznawany[posY][posX] & WEST) {
        if(!robot->tabSciezki[posY][posX-1] || robot->tabSciezki[posY][posX-1] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY][posX-1] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX-1, posY);
        }
    }
    if(robot->labiryntPoznawany[posY][posX] & SOUTH) {
        if(!robot->tabSciezki[posY+1][posX] || robot->tabSciezki[posY+1][posX] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY+1][posX] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX, posY+1);
        }     
    }
    if(robot->labiryntPoznawany[posY][posX] & EAST) {
        if(!robot->tabSciezki[posY][posX+1] || robot->tabSciezki[posY][posX+1] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY][posX+1] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX+1, posY);
        }  
    }
}

void znajdzNajkrotszaSciezkeStart(Robot* robot) {
    int posX = 3;
    int posY = 3;

    znajdzNajkrotszaSciezkeRekurencja(robot, posX, posY);
    robot->tabSciezki[posX][posY] = 0;
}

void przejedzLabirynt(Robot* robot) {
    printf("Zaczynam przejazd wzdluz sciezki\n");
    printf("PosX: %d PosY: %d\n", robot->posX, robot->posY);

    while(!(robot->posX == 3 && robot->posY == 3)) {
        if((robot->labiryntPoznawany[robot->posY][robot->posX] & NORTH) && (robot->tabSciezki[robot->posY-1][robot->posX] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Polnoc);
            printf("Znalazlem droge Polnoc \t\t");
        }
        else if((robot->labiryntPoznawany[robot->posY][robot->posX] & WEST) && (robot->tabSciezki[robot->posY][robot->posX-1] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Zachod);
            printf("Znalazlem droge Zachod \t\t");

        }
        else if((robot->labiryntPoznawany[robot->posY][robot->posX] & SOUTH) && (robot->tabSciezki[robot->posY+1][robot->posX] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Poludnie);
            printf("Znalazlem droge Poludnie \t");

        }
        else if((robot->labiryntPoznawany[robot->posY][robot->posX] & EAST) && (robot->tabSciezki[robot->posY][robot->posX+1] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Wschod);
            printf("Znalazlem droge Wschod \t\t");

        }
        printf("PosX: %d PosY: %d\n", robot->posX, robot->posY);

    }

    printf("Przejazd wzdluz sciezki zakonczony\n");
    printf("PosX: %d PosY: %d\n", robot->posX, robot->posY);
}

void skanujPole(Robot* robot){
    if(robot->tabLabiryntuBin[robot->posY][robot->posX] & NORTH) {
        robot->labiryntPoznawany[robot->posY][robot->posX] |= NORTH;
    }
    if(robot->tabLabiryntuBin[robot->posY][robot->posX] & WEST) {
        robot->labiryntPoznawany[robot->posY][robot->posX] |= WEST;
    }
    if(robot->tabLabiryntuBin[robot->posY][robot->posX] & SOUTH) {
        robot->labiryntPoznawany[robot->posY][robot->posX] |= SOUTH;
    }
    if(robot->tabLabiryntuBin[robot->posY][robot->posX] & EAST) {
        robot->labiryntPoznawany[robot->posY][robot->posX] |= EAST;
    }
}

void przeszukajLabirynt(Robot* robot) {
    int poznane = 0;
    int kierunek = 1;
    int strona = 1;
    int obecnyNumer = 0;
    int najmniejszy = 100;
    robot->posY = 0;
    robot->posX = 0;
    while(1){
        //if(poznane >= 16){
        if(poznane >= 64){
            break;
        }
        printf("X: %d Y: %d numer: %d obecnosc: %d poznane: %d\n", robot->posX, robot->posY, obecnyNumer, robot->obecnosc[robot->posY][robot->posX], poznane);
        if(kierunek == 1) {
            skanujPole(robot);
            robot->obecnosc[robot->posY][robot->posX] = obecnyNumer;
            
            //printf(": %d\n", robot->labiryntPoznawany[robot->posY][robot->posX]);
            //printf("Zmienna obecnyNumer: %d\n", obecnyNumer);
            //printf("X: %d Y: %d\n", robot->posX, robot->posY);
            //printf("X: %d Y: %d\n", robot->posX, robot->posY);

            if((robot->labiryntPoznawany[robot->posY][robot->posX] & NORTH) && (robot->obecnosc[robot->posY-1][robot->posX] == 0)) {
                jedzKierunek(robot, Polnoc);
                ++poznane;
                ++obecnyNumer;
            } else if((robot->labiryntPoznawany[robot->posY][robot->posX] & EAST) && (robot->obecnosc[robot->posY][robot->posX+1] == 0)) {
                jedzKierunek(robot, Wschod);
                ++poznane;
                ++obecnyNumer;
            } else if((robot->labiryntPoznawany[robot->posY][robot->posX] & SOUTH) && (robot->obecnosc[robot->posY+1][robot->posX] == 0)) {
                jedzKierunek(robot, Poludnie);
                ++poznane;
                ++obecnyNumer;
            } else if((robot->labiryntPoznawany[robot->posY][robot->posX] & WEST) && (robot->obecnosc[robot->posY][robot->posX-1] == 0)) {
                jedzKierunek(robot, Zachod);
                ++poznane;
                ++obecnyNumer;
            } else {
                kierunek = 0;
            }
        } else {
            skanujPole(robot);

            if(robot->labiryntPoznawany[robot->posY][robot->posX] & NORTH && obecnyNumer-1 == robot->obecnosc[robot->posY-1][robot->posX]) {
                jedzKierunek(robot, Polnoc);
                obecnyNumer--;
            } else if(robot->labiryntPoznawany[robot->posY][robot->posX] & SOUTH && obecnyNumer-1 == robot->obecnosc[robot->posY+1][robot->posX]) {
                jedzKierunek(robot, Poludnie);
                obecnyNumer--;
            } else if(robot->labiryntPoznawany[robot->posY][robot->posX] & WEST && obecnyNumer-1 == robot->obecnosc[robot->posY][robot->posX-1]) {
                jedzKierunek(robot, Zachod);
                obecnyNumer--;
                //printf("cos");
            } else if(robot->labiryntPoznawany[robot->posY][robot->posX] & EAST && obecnyNumer-1 == robot->obecnosc[robot->posY][robot->posX+1]) {
                jedzKierunek(robot, Wschod);
                obecnyNumer--;
            }
            //printf(": %d %d %d\n", obecnyNumer, robot->posX, robot->posY);
            //printf(": %d\n", robot->obecnosc[robot->posY][robot->posX]);
            skanujPole(robot);
            if((robot->labiryntPoznawany[robot->posY][robot->posX] & NORTH && robot->obecnosc[robot->posY-1][robot->posX] == 0) || 
                (robot->labiryntPoznawany[robot->posY][robot->posX] & SOUTH && robot->obecnosc[robot->posY+1][robot->posX] == 0) || 
                (robot->labiryntPoznawany[robot->posY][robot->posX] & WEST && robot->obecnosc[robot->posY][robot->posX-1] == 0) || 
                (robot->labiryntPoznawany[robot->posY][robot->posX] & EAST && robot->obecnosc[robot->posY][robot->posX+1] == 0)) {
                kierunek = 1;
            }
        }
    }
}