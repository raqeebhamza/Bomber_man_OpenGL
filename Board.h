/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>
#include <iostream>
#include<vector>
#include "util.h"
#include"Bomberman.h"
#include"bomb.h"
#include"ghost.h"
#include"pinky.h"
#include"blinky.h"
#include"inky.h"
#include"Clyde.h"
#include"energizer.h"
#include<fstream>
//#define WITH_TEXTURES
using namespace std;
class Board {
private:

     Bomberman *man;
     deque <bomb> boo;
     vector<ghost*> Enemies;
     energizer *Energy;
	int xcellsize, ycellsize;
	int width, height;
	int score;
	int lives;
	int timer;
	int option;
	int num_bricks;
	int total_bricks;
	int on;
    bool won;
    int high_score;
	ColorNames pcolor, bcolor, gcolor;

public:
	static const int BOARD_X;
	static const int BOARD_Y;
	Board(Bomberman &,bomb &,int xsize = 8, int ysize = 8);

	~Board(void);
	void InitalizeBoard(int, int);
	//draw the board
	void Draw();

	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}
	void GetInitBombermanPosition(int &x, int &y) {
		x = xcellsize + xcellsize / 2;
		y = ycellsize + ycellsize / 2;
	}
	int get_score(){return score;}
	int  values_on_board(int i,int j);
	void set_bomb_on_board(int i,int j);
	void remove_bomb(int i,int j);
	void SetBombermanPosition(int a,int b)
	{
		man->setBombermanposition(a,b);
	}
	void GetBombermanPosition(int &a,int &b)
	{
		man->getBombermanposition(a,b);
	}
	int get_lives()
	{
		return lives;
	}
	void set_lives(int l)
	{
		lives=l;
	}
	int get_timer()
	{
		return timer;
	}
	int get_option()
	{
	   return option;
	}
	void set_option(int o)
	{
		option=o;
	}
	void set_num_bricks(int a){num_bricks=a;total_bricks=(total_bricks>a)?total_bricks:a;}
	void set_score(int a){score=a;}
	void set_timer(int a){timer=a;}
	void Draw_manu();
	void Draw_rule();
	void Draw_GameOver();
	void pause();
	void Draw_wining();
	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void initialize_pinky();
	void initialize_blinky();
	void initialize_inky();
	void initialize_Clyde();
	void initialize_energizer();
	void ghost_motion();
	void re_play();
	void draw_bomb();
	void break_red_bricks(int i,int j);
	void blast_ghost(int ,int);
	void GetInitTextPosition(int &x, int &y);
	void GetInitPinkyPosition(int &x, int &y);
            void again_start();
            void set_high_score();
            void set_Direction_of_bomber(int );
            void eat_energy();
            void calculate_bricks();
            void pinky_move();
            void blinky_move();
            void inky_move();
            void Clyde_move();
            bool percent_30_break();
            bool percent_70_break();
            bool win();
            bool BomberMan_alive();
            int get_Direction_of_bomber();
//	int GetMidx
};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif
