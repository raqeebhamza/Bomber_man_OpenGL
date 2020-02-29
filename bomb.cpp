/*
 * bomb.cpp
 *
 *  Created on: May 4, 2017
 *      Author: ubuntu
 */


#include"bomb.h"
bomb::bomb(int a,int b)
{
    bom_x=a;
    bom_y=b;
    blast_Counter=0;
}
void bomb::getbombposition(int &a,int &b)
{
    a=bom_x;
    b=bom_y;
}
void bomb::setbombposition(int a,int b)
{
    bom_x=a;
    bom_y=b;
}
void bomb::set_blast_Counter(int a){ blast_Counter=a; }
int bomb::get_blast_Counter(){ return blast_Counter;}
void bomb:: draw()
{
	int x,y;
	getbombposition(x,y);
    x=12-x;
    DrawCircle(y*60+30, x*60+30, 15, colors[RED]);
}

bomb::~bomb()
{}

