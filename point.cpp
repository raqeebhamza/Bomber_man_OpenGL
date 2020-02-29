/*
 * point.cpp
 *
 *  Created on: May 6, 2017
 *      Author: ubuntu
 */

#include"point.h"

Point::Point(int a,int b)
{

	x=a;
    y=b;
    direction=0;
}
Point::~Point(){}
void Point:: setx(int a){x=a;}
void Point::sety(int b){y=b;}
int Point::getx(){return x;}
int Point::gety(){return y;}
void Point::set_direction(int a){direction=a;}
int Point::get_direction(){return direction;}
bool Point::operator ==(Point& p)
{
   if(x==p.x&&y==p.y)
	   return true;
	return false;
}
float Point::distance_of_point(Point &p)
{
    return Distance(x,y,p.x,p.y);
}



