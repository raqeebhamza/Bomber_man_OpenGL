/*
 * pinky.h
 *
 *  Created on: May 7, 2017
 *      Author: ubuntu
 */

#ifndef PINKY_H_
#define PINKY_H_

#include"ghost.h"


class pinky:public virtual ghost
{

public:
	pinky(int =1,int =3);
	void getghostposition(int& ,int&);
	void setghostposition(int ,int);
	void draw();
	void scatter_mode();
    virtual ~pinky();
};

#endif /* PINKY_H_ */
