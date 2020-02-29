/*
 * inky.h
 *
 *  Created on: May 18, 2017
 *      Author: ubuntu
 */

#ifndef INKY_H_
#define INKY_H_


#include"ghost.h"
class inky:public virtual ghost
{
public:
	inky(int =1,int =1);
	void getghostposition(int& ,int&);
	void setghostposition(int ,int);
	void draw();
	void scatter_mode();
	int search_corners();
	~inky();


};


#endif /* INKY_H_ */
