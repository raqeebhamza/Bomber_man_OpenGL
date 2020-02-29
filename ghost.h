/*
 * ghost.h
 *
 *  Created on: May 6, 2017
 *      Author: ubuntu
 */

#ifndef GHOST_H_
#define GHOST_H_
#include<iostream>
#include <deque>
#include"point.h"
#include"util.h"
using namespace std;
void DrawEnemy(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/, float gw = 6/*Enemy Width in Units*/,
		float gh = 7/*Enemy Height in Units*/,ColorNames legs_color=BLACK,ColorNames eyes_color=WHITE);
enum Direction {
	UP=11, DOWN, LEFT, RIGHT,
	};
class ghost
{
protected:
	int **array;
	int **B_arr;
	deque<Point> deque_points;
	int x;
	int y;
	bool ghost_alive;
               // for  bomber man points
	int bpos_x;
	int bpos_y;
	int mode;
	bool ch_color;
public:
	ghost(int =0,int =0);
	 virtual void getghostposition(int& ,int&)=0;
	 virtual void  draw()=0;
	 virtual void scatter_mode()=0;
	 void copy_board_for_ghost(int ptr[][17]);
	 int** get_board_from_ghost();
	 void getBMan_position_for_ghost(int,int);
	 virtual void setghostposition(int ,int )=0;
	 void set_ghost_alive(bool);
	 bool get_ghost_alive();
	 void set_B_arr();
	 int  BFS();
	 void set_ch_color(bool);
	 bool get_ch_color();
	 void chasing_mode();
	 void random_mode();
	 void move_back();
	 void set_mode(int );
	 int get_mode();
     virtual ~ghost();




};




#endif /* GHOST_H_ */
