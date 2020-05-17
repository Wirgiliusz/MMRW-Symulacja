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
