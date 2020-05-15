/*
 * robot.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */
#include "..\Inc\robot.h"


void jedzProsto(Robot* robot) {
	switch(robot->orientacja) {
	case 0:
		robot->posY--;
		break;
	case 1:
		robot->posX++;
		break;
	case 2:
		robot->posY++;
		break;
	case 3:
		robot->posX--;
		break;
	}
}

// strona = 0 - obrot w lewo;
// strona = 1 - obrot w prawo
void obroc(Robot* robot, int strona) {
	switch(strona) {
	case 0:
		robot->orientacja--;
		robot->orientacja %=4;
		break;
	case 1:
		robot->orientacja++;
		robot->orientacja %=4;
		break;
	}
}

void jedzPrawo(Robot* robot) {
	obroc(robot, 1);
	jedzProsto(robot);
}

void jedzLewo(Robot* robot) {
	obroc(robot, 0);
	jedzProsto(robot);
}

void jedzTyl(Robot* robot) {
	obroc(robot, 1);
	obroc(robot, 1);
	jedzProsto(robot);
}

void skanujObszar(Robot* robot) {

}
