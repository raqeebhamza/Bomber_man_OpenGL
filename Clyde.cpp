/*
 * Clyde.cpp
 *
 *  Created on: May 19, 2017
 *      Author: ubuntu
 */

#include"Clyde.h"

Clyde::Clyde(int a, int b) :
		ghost(a, b) {
}
void Clyde::getghostposition(int &a, int &b) {
	a = x;
	b = y;
}
void Clyde::setghostposition(int a, int b) {
	x = a;
	y = b;
}
void Clyde::draw() {
	int a, b;
	getghostposition(a, b);
	a = 12 - a;
	ColorNames lcolor,ecolor,body=ORANGE_RED;
		if(mode<21){

		lcolor=WHITE;
		ecolor=RED;
		}
		else if(mode>=21&&mode<=27)
		{
			body=BLUE;
		  	lcolor=body;
		  	ecolor=WHITE;
		}
		else
		{
			 lcolor=ORANGE_RED;
			 ecolor=WHITE;
		}
	DrawEnemy(b * 60/*starting x*/, a * 60/*starting y*/, body/*color*/,
			50/*Enemy Width in Units*/, 50/*Enemy Height in Units*/,lcolor,ecolor);
}
void Clyde::scatter_mode()
{
	int a,b;
cout<<"BLINKY MOVE"<<endl;
getghostposition(a,b);
switch (search_corners())
{
case UP: {
	        if(B_arr[a-1][b]==UP)
	        {
	        	int temp=array[a][b];
	        	array[a][b]=array[a-1][b];
	        	array[a-1][b]=temp;
	        	setghostposition(a-1,b);
	        }
          break;
         }
case RIGHT:{
	            if(B_arr[a][b+1]==RIGHT)
	            {
	            	int temp=array[a][b];
	                array[a][b]=array[a][b+1];
	            	array[a][b+1]=temp;
	            	setghostposition(a,b+1);
	            }
	            break;
           }
case DOWN:{
	           if(B_arr[a+1][b]==DOWN)
	           {
	        	   int temp=array[a][b];
	        	   array[a][b]=array[a+1][b];
	        	   array[a+1][b]=temp;
	        	   setghostposition(a+1,b);
	           }
	           break;
          }
case LEFT:{
               if(B_arr[a][b-1]==LEFT )
			   {

			      int temp=array[a][b];
			      array[a][b]=array[a][b-1];
			      array[a][b-1]=temp;
			      setghostposition(a,b-1);

			   }
			   break;
          }
default:
{
	break;
}

 	}
}

int Clyde::search_corners()
{
	deque<Point> dq_points;
		cout << "BFS" << endl;
		set_B_arr();
		int a, b;

		getghostposition(a, b);
		Point present_point(a, b), corner_point(11,1);

		float Distance = present_point.distance_of_point(corner_point);
		Point next_point;
		if (B_arr[a - 1][b] == -1) {

			B_arr[a - 1][b] = Direction(UP);
			next_point.setx(a - 1);
			next_point.sety(b);
			dq_points.push_back(next_point);

		}
		if (B_arr[a + 1][b] == -1 ) {

			B_arr[a + 1][b] = Direction(DOWN);
			next_point.setx(a + 1);
			next_point.sety(b);
			dq_points.push_back(next_point);
		}
		if (B_arr[a][b - 1] == -1 ) {
			B_arr[a][b - 1] = Direction(LEFT);
			next_point.setx(a);
			next_point.sety(b - 1);
			dq_points.push_back(next_point);

		}
		if (B_arr[a][b + 1] == -1 ) {
			B_arr[a][b + 1] = Direction(RIGHT);
			next_point.setx(a);
			next_point.sety(b + 1);
			dq_points.push_back(next_point);

		}
		int d;
		while (Distance > 0) {

			int x = dq_points[0].getx(), y = dq_points[0].gety();
			d = B_arr[x][y];

			Distance = dq_points[0].distance_of_point(corner_point);
			Point neighbor_up, neighbor_down, neighbor_left, neighbor_right;
			if (B_arr[x - 1][y] == -1 ) {             //up

				B_arr[x - 1][y] = d;
				neighbor_up.setx(x - 1);
				neighbor_up.sety(y);
				dq_points.push_back(neighbor_up);

			}
			if (B_arr[x + 1][y] == -1 ) {            //down
				B_arr[x + 1][y] = d;
				neighbor_down.setx(x + 1);
				neighbor_down.sety(y);
				dq_points.push_back(neighbor_down);

			}
			if (B_arr[x][y - 1] == -1 ) {

			                                          //left
				B_arr[x][y - 1] = d;
				neighbor_left.setx(x);
				neighbor_left.sety(y - 1);

				dq_points.push_back(neighbor_left);

			}
			if (B_arr[x][y + 1] == -1 ) {             //right
				B_arr[x][y + 1] = d;
				neighbor_right.setx(x);
				neighbor_right.sety(y + 1);
				dq_points.push_back(neighbor_right);

			}
			dq_points.pop_front();
		}
		return d;
}
Clyde::~Clyde() {
}


