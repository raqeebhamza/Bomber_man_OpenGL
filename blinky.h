/*
 * blinky.h
 *
 *  Created on: May 7, 2017
 *      Author: ubuntu
 */

#ifndef BLINKY_H_
#define BLINKY_H_

#include"ghost.h"

class blinky: public virtual ghost {

public:
	blinky(int = 1, int = 1);
	void getghostposition(int&, int &);
	void setghostposition(int, int);
	void scatter_mode();
	int search_corners();
	void draw();

	~blinky();
};

#endif /* BLINKY_H_ */
