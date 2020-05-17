/*
 * robot.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Maialen
 */

#ifndef INC_ROBOT_H_
#define INC_ROBOT_H_

#define NORTH   1 //00001000
#define WEST    2 //00000100
#define SOUTH   4 //00000010
#define EAST    8 //00000001

typedef struct Robot {
	int posX;
	int posY;
	enum Orientacje{Polnoc, Zachod, Poludnie, Wschod} orientacja;
	enum Strony{Lewo, Prawo} strona;
	int odczytCzujnikow[4];
    unsigned char tabLabiryntuBin[8][8];
    int tabSciezki[8][8];

} Robot;

Robot konstruktorRobota(int poczatkoweX, int poczatkoweY, enum Orientacje poczatkowaOrientacja);

void jedzProsto(Robot* robot);
void obroc(Robot* robot, enum Strony strona);
void jedzPrawo(Robot* robot);
void jedzLewo(Robot* robot);
void jedzTyl(Robot* robot);
void jedzKierunek(Robot* robot, enum Orientacje kierunek);

void znajdzNajkrotszaSciezkeRekurencja(Robot* robot, int posX, int posY);
void znajdzNajkrotszaSciezkeStart(Robot* robot);
void przejedzLabirynt(Robot* robot);




#endif /* INC_ROBOT_H_ */
