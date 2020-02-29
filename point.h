/*
 * point.h
 *
 *  Created on: May 6, 2017
 *      Author: ubuntu
 */

#ifndef POINT_H_
#define POINT_H_
#include<iostream>
#include"util.h"
using namespace std;
class Point
{
int x;int y;int direction;
public:
    Point(int =0,int =0);
   int  getx();
   int gety();
   void setx(int);
   void sety(int);
   bool operator==(Point&);
   void set_direction(int);
   int get_direction();
   float distance_of_point(Point &p);
    ~Point();
};
#endif /* POINT_H_ */
