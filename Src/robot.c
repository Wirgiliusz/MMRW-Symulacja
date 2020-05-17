/*
 * robot.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */
#include "..\Inc\robot.h"


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