/*
 * Bomberman.h
 *
 *  Created on: May 4, 2017
 *      Author: ubuntu
 */

#ifndef BOMBERMAN_H_
#define BOMBERMAN_H_

class Bomberman
{
private:
	int x;
	int y;
	int direction_man;
public:
    Bomberman(int a=8,int b=7)
    {
    	x=a;
    	y=b;
    	direction_man=3;
    }
    void getBombermanposition(int &a,int &b)
    {
        a=x;
        b=y;
    }
    void setBombermanposition(int a,int b )
    {
       x=a;
       y=b;
    }
    void set_direction_man(int a){direction_man=a;}
    int get_direction_man(){return direction_man;}
    ~Bomberman()
    {
    }
};



#endif /* BOMBERMAN_H_ */

