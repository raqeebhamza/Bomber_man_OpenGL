/*
 * energizer.h
 *
 *  Created on: May 20, 2017
 *      Author: ubuntu
 */

#ifndef ENERGIZER_H_
#define ENERGIZER_H_


class energizer
{
  int x;
  int y;
  bool eaten=false;
public:
  energizer(int a=0,int b=0)
  {
	x=a;
	y=b;

  }
  void set_energizer(int a, int b)
  {
	  x=a;
	  y=b;
  }
  void get_energizer(int &a,int &b)
  {
	  a=x;
	  b=y;
  }
  void set_eaten(bool a){eaten=a;}
  bool get_eaten(){return eaten;}
  ~energizer(){};

};


#endif /* ENERGIZER_H_ */
