/*
 * bomb.h
 *
 *  Created on: May 4, 2017
 *      Author: ubuntu
 */

#ifndef BOMB_H_
#define BOMB_H_
#include<iostream>
#include"util.h"
using namespace std;
class bomb
{
private:
    int bom_x;
    int bom_y;
    int blast_Counter;
public:
    bomb(int a=0,int b=0);
   ~bomb();
   void setbombposition(int,int);
   void  draw();
   int get_blast_Counter();
   void set_blast_Counter(int );
   void getbombposition(int &,int &);

};



#endif /* BOMB_H_ */
