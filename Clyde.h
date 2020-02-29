/*
 * Clyde.h
 *
 *  Created on: May 19, 2017
 *      Author: ubuntu
 */

#ifndef CLYDE_H_
#define CLYDE_H_
#include"ghost.h"
class Clyde:public virtual ghost
{

public:
	Clyde(int =1,int =3);
	void getghostposition(int& ,int&);
	void setghostposition(int ,int);
	void scatter_mode();
	int search_corners();
	void draw();
    virtual ~Clyde();
};


#endif /* CLYDE_H_ */
