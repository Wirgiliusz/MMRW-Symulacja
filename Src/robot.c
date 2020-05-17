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
    unsigned char tabLabiryntuTemp[8][8] = {    {EAST,              WEST|EAST,              WEST|SOUTH|EAST,    WEST|EAST,          WEST|SOUTH,     WEST|EAST,              WEST|SOUTH|EAST,    WEST}, 
                                                {EAST,              WEST|SOUTH|EAST,        NORTH|WEST,         SOUTH,              NORTH|SOUTH,    NORTH|SOUTH,            NORTH|EAST,         WEST|SOUTH}, 
                                                {SOUTH,             NORTH|SOUTH,            SOUTH|EAST,         NORTH|WEST|SOUTH,   NORTH|EAST,     NORTH|WEST|EAST,        WEST|SOUTH,         NORTH},
                                                {NORTH|SOUTH|EAST,  NORTH|WEST,             NORTH|SOUTH,        NORTH|SOUTH|EAST,   WEST|SOUTH,     SOUTH,                  NORTH|EAST,         WEST|SOUTH},
                                                {NORTH|SOUTH,       EAST,                   NORTH|WEST|SOUTH,   NORTH|EAST,         NORTH|WEST,     NORTH|SOUTH|EAST,       WEST|EAST,          NORTH|WEST},
                                                {NORTH|SOUTH|EAST,  WEST,                   NORTH|SOUTH|EAST,   WEST,               SOUTH|EAST,     NORTH|WEST|SOUTH|EAST,  WEST|EAST,          WEST|SOUTH},
                                                {NORTH|SOUTH|EAST,  WEST|SOUTH|EAST,        NORTH|WEST|SOUTH,   EAST,               NORTH|WEST,     NORTH|SOUTH,            EAST,               NORTH|WEST|SOUTH},
                                                {NORTH,             NORTH,                  NORTH|EAST,         WEST|EAST,          WEST|EAST,      NORTH|WEST|EAST,        WEST|EAST,          NORTH|WEST} };

    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            robot.tabLabiryntuBin[i][j] = tabLabiryntuTemp[i][j];
            robot.tabSciezki[i][j] = 0;
        }
    } 

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
    if(robot->tabLabiryntuBin[posY][posX] & NORTH) {
        if(!robot->tabSciezki[posY-1][posX] || robot->tabSciezki[posY-1][posX] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY-1][posX] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX, posY-1);
        }
    }
    if(robot->tabLabiryntuBin[posY][posX] & WEST) {
        if(!robot->tabSciezki[posY][posX-1] || robot->tabSciezki[posY][posX-1] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY][posX-1] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX-1, posY);
        }
    }
    if(robot->tabLabiryntuBin[posY][posX] & SOUTH) {
        if(!robot->tabSciezki[posY+1][posX] || robot->tabSciezki[posY+1][posX] > robot->tabSciezki[posY][posX] ) {
            robot->tabSciezki[posY+1][posX] = robot->tabSciezki[posY][posX] + 1;
            znajdzNajkrotszaSciezkeRekurencja(robot, posX, posY+1);
        }     
    }
    if(robot->tabLabiryntuBin[posY][posX] & EAST) {
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
    printf("PosX: %d\nPosY: %d\n", robot->posX, robot->posY);

    while(!(robot->posX == 3 && robot->posY == 3)) {
        //printf("PosX: %d | PosY: %d\n", robot->posX, robot->posY);
        if((robot->tabLabiryntuBin[robot->posY][robot->posX] & NORTH) && (robot->tabSciezki[robot->posY-1][robot->posX] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Polnoc);
            printf("Znalazlem droge Polnoc\n");
        }
        if((robot->tabLabiryntuBin[robot->posY][robot->posX] & WEST) && (robot->tabSciezki[robot->posY][robot->posX-1] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Zachod);
            printf("Znalazlem droge Zachod\n");

        }
        if((robot->tabLabiryntuBin[robot->posY][robot->posX] & SOUTH) && (robot->tabSciezki[robot->posY+1][robot->posX] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Poludnie);
            printf("Znalazlem droge Poludnie\n");

        }
        if((robot->tabLabiryntuBin[robot->posY][robot->posX] & EAST) && (robot->tabSciezki[robot->posY][robot->posX+1] == robot->tabSciezki[robot->posY][robot->posX] - 1)) {
            jedzKierunek(robot, Wschod);
            printf("Znalazlem droge Wschod\n");

        }
    }

    printf("Przejazd wzdluz sciezki zakonczony\n");
    printf("PosX: %d\nPosY: %d\n", robot->posX, robot->posY);
}