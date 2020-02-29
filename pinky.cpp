/*
 * pinky.cpp
 *
 *  Created on: May 7, 2017
 *      Author: ubuntu
 */

#include"pinky.h"

pinky::pinky(int a, int b) :
		ghost(a, b) {
}
void pinky::getghostposition(int &a, int &b) {
	a = x;
	b = y;
}
void pinky::setghostposition(int a, int b) {
	x = a;
	y = b;
}
pinky::~pinky() {
}
void pinky::scatter_mode()
{
   cout<<"pinky move only randomly:";
}
void pinky::draw() {
	int a, b;
	getghostposition(a, b);
	a = 12 - a;
	DrawEnemy(b * 60/*starting x*/, a * 60/*starting y*/,DEEP_PINK/*color*/,
			50/*Enemy Width in Units*/, 50/*Enemy Height in Units*/,DEEP_PINK,WHITE);
}
