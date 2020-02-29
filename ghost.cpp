/*
 * ghost.cpp
 *
 *  Created on: May 6, 2017
 *      Author: ubuntu
 */

#include"ghost.h"
ghost::ghost(int a, int b) {
	array = new int*[14];
	B_arr = new int*[14];
	for (int i = 0; i < 14; ++i) {
		array[i] = new int[17];
		B_arr[i] = new int[17];
	}
	x = a, y = b;
	ghost_alive = true;
	bpos_x = 0;
	bpos_y = 0;
	mode=0;
	ch_color=true;
}
int** ghost::get_board_from_ghost() {
	return array;
}
void ghost::copy_board_for_ghost(int ptr[][17]) {
	for (int i = 0; i < 14; ++i) {
		for (int j = 0; j < 17; ++j) {
			array[i][j] = ptr[i][j];

		}

	}
}
void ghost::getBMan_position_for_ghost(int a, int b) {
	bpos_x = a;
	bpos_y = b;
}
void ghost::set_ghost_alive(bool t) {
	ghost_alive = t;
}
bool ghost::get_ghost_alive() {
	return ghost_alive;
}
int ghost::BFS() {
	deque<Point> dq_points;
	cout << "BFS" << endl;
	set_B_arr();
	int a, b;

	getghostposition(a, b);
	Point present_point(a, b), BOMBER_point(bpos_x, bpos_y);

	float Distance = present_point.distance_of_point(BOMBER_point);
	Point next_point;
	if (B_arr[a - 1][b] == -1 || B_arr[a - 1][b] == 4) {

		B_arr[a - 1][b] = Direction(UP);
		next_point.setx(a - 1);
		next_point.sety(b);
		dq_points.push_back(next_point);

	}
	if (B_arr[a + 1][b] == -1 || B_arr[a + 1][b] == 4) {

		B_arr[a + 1][b] = Direction(DOWN);
		next_point.setx(a + 1);
		next_point.sety(b);
		dq_points.push_back(next_point);
	}
	if (B_arr[a][b - 1] == -1 || B_arr[a][b - 1] == 4) {
		B_arr[a][b - 1] = Direction(LEFT);
		next_point.setx(a);
		next_point.sety(b - 1);
		dq_points.push_back(next_point);

	}
	if (B_arr[a][b + 1] == -1 || B_arr[a][b + 1] == 4) {
		B_arr[a][b + 1] = Direction(RIGHT);
		next_point.setx(a);
		next_point.sety(b + 1);
		dq_points.push_back(next_point);

	}
	int d;
	while (Distance > 0) {

		int x = dq_points[0].getx(), y = dq_points[0].gety();
		d = B_arr[x][y];

		Distance = dq_points[0].distance_of_point(BOMBER_point);
		Point neighbor_up, neighbor_down, neighbor_left, neighbor_right;
		if (B_arr[x - 1][y] == -1 || B_arr[x - 1][y] == 4) {                //up

			B_arr[x - 1][y] = d;
			neighbor_up.setx(x - 1);
			neighbor_up.sety(y);
			dq_points.push_back(neighbor_up);

		}
		if (B_arr[x + 1][y] == -1 || (B_arr[x + 1][y] == 4)) {            //down
			B_arr[x + 1][y] = d;
			neighbor_down.setx(x + 1);
			neighbor_down.sety(y);
			dq_points.push_back(neighbor_down);

		}
		if (B_arr[x][y - 1] == -1 || B_arr[x][y - 1] == 4) {

		                                                             	//left
			B_arr[x][y - 1] = d;
			neighbor_left.setx(x);
			neighbor_left.sety(y - 1);

			dq_points.push_back(neighbor_left);

		}
		if (B_arr[x][y + 1] == -1 || B_arr[x][y + 1] == 4) {             //right
			B_arr[x][y + 1] = d;
			neighbor_right.setx(x);
			neighbor_right.sety(y + 1);
			dq_points.push_back(neighbor_right);

		}
		dq_points.pop_front();
	}
	return d;
}
void ghost::chasing_mode()
{	int a,b;
cout<<"BLINKY MOVE"<<endl;
getghostposition(a,b);
cout<<"BFS:x="<<a<<"  y="<<b<<endl;
switch (BFS())
{
case UP: {
	        if(B_arr[a-1][b]==UP)
	        {
	        	 if(array[a-1][b]==4)
	        		            	   {
	        		            		   array[a-1][b]=0;
	        		            		   array[a][b]=0;
	        		            	   }
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
	            	 if(array[a][b+1]==4)
	            		            	   {
	            		            		   array[a][b+1]=0;
	            		            		   array[a][b]=0;
	            		            	   }
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
	        	   if(array[a+1][b]==4)
	        	  	            	   {
	        	  	            		   array[a+1][b]=0;
	        	  	            		 array[a][b]=0;
	        	  	            	   }
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
            	   if(array[a][b-1]==4)
            	   {
            		                     array[a][b-1]=0;
            		                     array[a][b]=0;
            	   }

			      int temp=array[a][b];
			      array[a][b]=array[a][b-1];
			      array[a][b-1]=temp;
			      setghostposition(a,b-1);

			   }
			   break;
          }
default:{


        }
 	}
}
void ghost::random_mode()
{
int a, b;
getghostposition(a, b);
Point p;
deque_points.push_back(p);
deque_points[deque_points.size()-1].setx(a);
deque_points[deque_points.size()-1].sety(b);
for (int i = 0; i < 3; ++i)
	if (deque_points.size() > 3)
		deque_points.pop_front();
int index;
if (deque_points.size() == 2)
	index = 0;
else
	index = 1;
bool counter = true;
int num = 0;
do {
	int choose = GetRandInRange(1, 5);
	cout << "choose=" << choose << endl;
	switch (choose) {
	case 1: {
		if ((array[a - 1][b] == 0 || array[a-1][b]==4)
				&& !(a - 1 == deque_points[index].getx()
						&& b == deque_points[index].gety()))    //up
				{
			if (array[a - 1][b] == 4) {
				array[a - 1][b] = 0;
				array[a][b] = 0;
				setghostposition(a - 1, b);
			} else {
				cout << "up" << endl;
				int temp = array[a - 1][b];
				array[a - 1][b] = array[a][b];
				array[a][b] = temp;
				setghostposition(a - 1, b);
				counter = false;
			}
		}
		break;
	}
	case 2: {
		if ((array[a + 1][b] == 0 || array[a + 1][b] ==4)
				&& !(a + 1 == deque_points[index].getx()
						&& b == deque_points[index].gety())) {      // down

			if (array[a + 1][b] == 4) {
				array[a + 1][b] = 0;
				array[a][b] = 0;
				setghostposition(a + 1, b);

			} else {

				cout << "down" << endl;
				int temp = array[a + 1][b];
				array[a + 1][b] = array[a][b];
				array[a][b] = temp;
				setghostposition(a + 1, b);
				counter = false;
			}
		}
		break;
	}
	case 3: {
		if ((array[a][b + 1] == 0 || array[a][b + 1]==4)
				&& !(a == deque_points[index].getx()
						&& b + 1 == deque_points[index].gety()))    ///right

				{
			if (array[a][b + 1] == 4) {
				array[a][b + 1] = 0;
				array[a][b] = 0;
				setghostposition(a, b + 1);
			} else {

				cout << "right" << endl;
				int temp = array[a][b + 1];
				array[a][b + 1] = array[a][b];
				array[a][b] = temp;
				setghostposition(a, b + 1);
				counter = false;
			}
		}
		break;
	}
	case 4: {

		if ((array[a][b - 1] == 0 || array[a][b - 1]==4)
				&& !(a == deque_points[index].getx()
						&& b - 1 == deque_points[index].gety())) {  //left
			if (array[a][b - 1] == 4) {
				array[a][b - 1] = 0;
				array[a][b] = 0;
				setghostposition(a, b - 1);
			}

			else {
				cout << "left" << endl;
				int temp = array[a][b - 1];
				array[a][b - 1] = array[a][b];
				array[a][b] = temp;
				setghostposition(a, b - 1);
				counter = false;
			}
		}
		break;
	}
	}
	if (counter) {
		if (num == 5) {
			num = 0;
			move_back();
			cout << "move back" << endl;
			counter = false;
		} else {
			num++;
			choose = GetRandInRange(1, 5);
		}
	}
} while (counter);
}
void ghost::move_back()
{	int a, b;
getghostposition(a, b);

if ((array[a - 1][b] == 0 || array[a - 1][b]==4)
		&& !(a - 1 == deque_points[1].getx() && b == deque_points[1].gety())) // up
		{
	if (array[a - 1][b] == 4) {
		array[a - 1][b] = 0;
		array[a][b] = 0;
		setghostposition(a - 1, b);
	} else {

		cout << "back up" << endl;
		int temp = array[a - 1][b];
		array[a - 1][b] = array[a][b];
		array[a][b] = temp;
		setghostposition(a - 1, b);
	}
}

else if ((array[a][b + 1] == 0 ||array[a][b + 1]== 4)
		&& !(a == deque_points[1].getx() && b + 1 == deque_points[1].gety())) //right
		{
	if (array[a][b + 1] == 4) {
		array[a][b + 1] = 0;
		array[a][b] = 0;
		setghostposition(a, b + 1);
	} else {

		cout << "back right" << endl;
		int temp = array[a][b + 1];
		array[a][b + 1] = array[a][b];
		array[a][b] = temp;
		setghostposition(a, b + 1);
	}
} else if ((array[a + 1][b] == 0 || array[a + 1][b]==4)
		&& !(a + 1 == deque_points[1].getx() && b == deque_points[1].gety())) //down
		{
	if (array[a + 1][b] == 4) {
		array[a + 1][b] = 0;
		array[a][b] = 0;
		setghostposition(a + 1, b);

	} else {

		cout << "back down" << endl;
		int temp = array[a + 1][b];
		array[a + 1][b] = array[a][b];
		array[a][b] = temp;
		setghostposition(a + 1, b);

	}
} else if (array[a][b - 1] == 0||array[a][b - 1]==4)     // left
		{

	if (array[a][b - 1] == 4) {
		array[a][b - 1] = 0;
		array[a][b] = 0;
		setghostposition(a, b - 1);
	} else {
		cout << "back left" << endl;
		int temp = array[a][b - 1];
		array[a][b - 1] = array[a][b];
		array[a][b] = temp;
		setghostposition(a, b - 1);

	}
}
}
void ghost::set_B_arr() {

	for (int i = 0; i < 14; ++i) {
		for (int j = 0; j < 17; ++j) {
			B_arr[i][j] = array[i][j];
			if (B_arr[i][j] == 0)
				B_arr[i][j] = -1;
			else if (B_arr[i][j] == 4)
				B_arr[i][j] = 4;
			else
				B_arr[i][j] = 0;

		}
	}
}
void ghost::set_mode(int a){mode=a;}
int ghost::get_mode(){return mode;}
void ghost::set_ch_color(bool a){ch_color=a;}
bool ghost::get_ch_color(){return ch_color;}
ghost::~ghost() {
}

