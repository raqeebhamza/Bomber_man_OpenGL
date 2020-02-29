/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#include "Board.h"
#include <cstdio>

const int Board::BOARD_X = 17;   
const int Board::BOARD_Y = 14;
//here's Bomberman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
enum BoardParts {
	NILL, S_BRICK, G_BRICK, R_BRICK, BOMBERMAN,GHOST,GIFT
};

// defining some utility functions...

static int board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };

void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/,
		const ColorNames &colorname/*Bomberman Colour*/,int  direct=1);
void DrawEnemy(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/, float gw/* = 6 Enemy Width in Units*/,
		float gh/* = 7Enemy Height in Units*/,ColorNames legs_color,ColorNames eyes_color);

#ifdef WITH_TEXTURES
const int nbricks = 3;

GLuint texture[nbricks];
GLuint tid[nbricks];
string tnames[] = {"solid.png", "brick.png", "brick-green.png"};
GLuint mtid[nbricks];
int cwidth = 60, cheight = 60; // 60x60 pixels bricks...

void RegisterTextures()
/*Function is used to load the textures from the
 * files and display*/
{
	// allocate a texture name
	glGenTextures(nbricks, tid);

	vector<unsigned char> data;
	//ofstream ofile("image-data.bin", ios::binary | ios::out);
	// now load each bricks data...

	for (int i = 0; i < nbricks; ++i) {

		// Read current brick

		ReadImage(tnames[i], data);
		if (i == 0) {
			int length = data.size();
			//ofile.write((char*) &length, sizeof(int));
		}
		//ofile.write((char*) &data[0], sizeof(char) * data.size());

		cout << " Texture Id=" << tid[i] << endl;
		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
				GL_UNSIGNED_BYTE, &data[0]);
	}
	//ofile.close();

}
void Drawbrick(const BoardParts &cname, float fx, float fy, float fwidth,
		float fheight)
/*Draws a specfic brick at given position coordinate
 * sx = position of x-axis from left-bottom
 * sy = position of y-axis from left-bottom
 * cwidth= width of displayed brick in pixels
 * cheight= height of displayed bricki pixels.
 * */
{

	glPushMatrix();
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname - 1]);
//	glTranslatef(0, 0, 0);
//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin (GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
#endif
// Destructor
Board::~Board(void) {
}
void Board::InitalizeBoard(int w, int h) {
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
				board_array[i][j] =
						(GetRandInRange(0, 10)) < 8 ? NILL :
						(GetRandInRange(0, 10)) < 8 ? G_BRICK : R_BRICK;
		}
	}
	int x,y;
	man->getBombermanposition(x,y);
	board_array[x][y]=BOMBERMAN;

	//  ghost initialization
	Enemies.push_back(new pinky());
	Enemies.push_back(new blinky());
	Enemies.push_back(new inky());
	Enemies.push_back(new Clyde());
    initialize_energizer();
    initialize_pinky();
    initialize_blinky();
}
//Constructor
Board::Board(Bomberman &m,bomb &boo,int xsize, int ysize) {
	xcellsize = xsize;
	ycellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;
	man=&m;
	score=0;
	lives=3;
	timer=-1;
	option=0;
	num_bricks=0;
	on=0;
    high_score=0;
    total_bricks=0;
//set up board
}
void Board::Draw_manu()
{
	 int inx,iny;
	    GetInitTextPosition(inx, iny);
	if(timer==-1)
	{
		DrawString(inx+275,iny-350, "PRESS '1' TO PLAY", colors[WHITE]);
		DrawString(inx+275,iny-375, "PRESS '2' TO RULES", colors[WHITE]);
		DrawString(inx+275,iny-400, "PRESS 'ESC' EXIT", colors[WHITE]);
	}
}
void Board:: Draw_rule()
{
	 int inx,iny;
		    GetInitTextPosition(inx, iny);
		if(timer==-1)
		{
			DrawString(inx+275,iny-350, "PRESS '1' TO PLAY", colors[WHITE]);
			DrawString(inx+275,iny-375, "RULES:", colors[WHITE]);
			DrawCircle(inx+280,iny-395,5,colors[WHITE]);
			DrawString(inx+300,iny-400, "TO CONTROL BOMBERMAN :", colors[WHITE]);
			DrawCircle(inx+280,iny-420,5,colors[WHITE]);
			DrawString(inx+350,iny-425, "USE  'UP'  'DOWN'  'RIGHT'   'LEFT'", colors[WHITE]);
			DrawCircle(inx+280,iny-445,5,colors[WHITE]);
			DrawString(inx+300,iny-450, "BREAK ALL BRICKS TO WIN ", colors[WHITE]);
			DrawCircle(inx+280,iny-470,5,colors[WHITE]);
			DrawString(inx+300,iny-475, "BE AWARE OF GHOST ENEMIES ", colors[WHITE]);
			DrawCircle(inx+280,iny-495,5,colors[WHITE]);
			DrawString(inx+300,iny-500, "PRESS 'B' FOR ANNIHILATION ", colors[WHITE]);
			DrawString(inx+275,iny-525, "PRESS 'ESC' EXIT", colors[WHITE]);
		}
}
void Board::Draw_GameOver()
{

  int inx,iny;
 	    GetInitTextPosition(inx, iny);
  DrawString(inx+325,iny-350, "GAMEOVER", colors[RED]);
  DrawString(inx+300,iny-400, "PRESS 'Y' TO PLAY AGAIN", colors[RED]);
  DrawString(inx+300,iny-450, "PRESS 'ESC' EXIT", colors[RED]);

}
void Board::pause()
{
	 int inx,iny;
	 	    GetInitTextPosition(inx, iny);
	  DrawString(inx+325,iny-400, "GAME IS PAUSED ", colors[WHITE]);
	  DrawString(inx+325,iny-450, "PRESS 'D' TO UN_PAUSE THE GAME ", colors[WHITE]);
}
void Board::Draw_wining()
{
	int inx,iny;
    GetInitTextPosition(inx, iny);
    DrawCircle(inx+450,iny-400,350,colors[WHITE]);
    DrawString(inx+325,iny-350, "YOU WON ", colors[RED]);
    DrawString(inx+325,iny-400, "SCORE:", colors[RED]);
    DrawString(inx+425,iny-400, Num2Str(score), colors[RED]);
    DrawString(inx+325,iny-450, "HIGH_SCORE:", colors[RED]);
    DrawString(inx+425+60,iny-450, Num2Str(high_score), colors[RED]);
    DrawString(inx+325,iny-500, "TIME:", colors[RED]);
    DrawString(inx+425,iny-500, Num2Str(timer), colors[RED]);
    DrawString(inx+325,iny-550, "PRESS 'Y' TO PLAY AGAIN ", colors[RED]);

}
void Board::Draw() {
	glColor3f(0, 0, 1);
	glPushMatrix();
	draw_bomb();
    int inx,iny;
    GetInitTextPosition(inx, iny);
	DrawString(inx,iny-10, "SCORE:", colors[WHITE]);
	DrawString(inx+100,iny-10, Num2Str(score), colors[WHITE]);
	DrawString(inx+10*60,iny-10, "LIVES:", colors[WHITE]);
	DrawString(inx+3*60,iny-10,"'P' TO  PAUSE",colors[RED]);
	DrawString(inx+7*60,iny-10, "TIME:", colors[WHITE]);
	DrawString(inx+7*60+70,iny-10, Num2Str(timer), colors[WHITE]);
	inx+=12*60;
	for(int i=0;i<lives;++i)
		DrawEnemy(inx+i*40/*starting x*/, iny-15/*starting y*/,GHOST_WHITE /*color*/,
					30/*Enemy Width in Units*/, 30/*Enemy Height in Units*/,GHOST_WHITE,WHITE);
	calculate_bricks();
	 for(int i=0;i<14;++i)
	 { for(int j=0;j<17;++j)
		   			 		 cout<<board_array[i][j]<<" ";

	 cout<<endl;
	 }
#ifdef WITH_TEXTURES
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
				case NILL:
				// Empty space
				break;
				case S_BRICK:
				case G_BRICK:
				case R_BRICK:
				float fwidth = (float) (xcellsize) / width * 2, fheight =
				(float) ycellsize / height * 2;
				float fx = (float) (x - 10) / width * 2 - 1, fy = (float) y
				/ height * 2 - 1;

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				 fheight);*/
				Drawbrick((BoardParts) board_array[i][j], (float)x/width-1, (float)y/height-1, fwidth,
						fheight);
				break;
			}
		}
	}
#else
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout <<      " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
			case NILL:
				// Empty space
				break;
			case S_BRICK:
				DrawRectangle(x , y, ycellsize, xcellsize,colors[SLATE_GRAY]);
		     	            DrawLine(x, y+20,x+60, y+20, 4, colors[BLACK]);
		              	DrawLine(x, y+40,x+60, y+40, 4, colors[BLACK]);
		            	DrawLine(x+20, y,x+20, y+20, 4, colors[BLACK]);
		            	DrawLine(x+40, y+20,x+40, y+40, 4, colors[BLACK]);
		            	DrawLine(x+20, y+40,x+20, y+60, 4, colors[BLACK]);
				break;
			case G_BRICK:
				DrawRectangle(x , y, ycellsize, xcellsize,colors[LIGHT_GREEN]);
				DrawLine(x, y+20,x+60, y+20, 4, colors[BLACK]);
		      	            DrawLine(x, y+40,x+60, y+40, 4, colors[BLACK]);
		              	DrawLine(x+20, y,x+20, y+20, 4, colors[BLACK]);
    	                        	DrawLine(x+40, y+20,x+40, y+40, 4, colors[BLACK]);
				DrawLine(x+20, y+40,x+20, y+60, 4, colors[BLACK]);
				break;
			case R_BRICK:
				DrawRectangle(x , y, ycellsize, xcellsize, colors[RED]);
				DrawLine(x, y+20,x+60, y+20, 4, colors[BLACK]);
			            DrawLine(x, y+40,x+60, y+40, 4, colors[BLACK]);
				DrawLine(x+20, y,x+20, y+20, 4, colors[BLACK]);
			            DrawLine(x+40, y+20,x+40, y+40, 4, colors[BLACK]);
		     	            DrawLine(x+20, y+40,x+20, y+60, 4, colors[BLACK]);
				break;
			case BOMBERMAN:
				DrawBomberman(x+30, y+30, GetCellSize() / 2 - 2, WHITE,man->get_direction_man());
						break;
			case GHOST:
				if(Enemies[0]->get_ghost_alive())
					Enemies[0]->draw();
				if(Enemies[1]->get_ghost_alive())
				    Enemies[1]->draw();
				if(percent_30_break()&&Enemies[2]->get_ghost_alive())
				{
					if(on==0)
					{
					    on++;
					    initialize_inky();
					}
					Enemies[2]->draw();

				}
				if(percent_70_break()&&Enemies[3]->get_ghost_alive())
				{	if(on==1)
					{
						on++;
						initialize_Clyde();
					}
					Enemies[3]->draw();
				}
					break;

			case GIFT:


				   int a,b;
				   Energy->get_energizer(a,b);
				   a=12-a;
	               DrawCircle(b*60+30,a*60+30,15,colors[WHITE]);
				
	            break;
		    }
		}
	}
#endif
	glPopMatrix();
}

void Board::GetInitPinkyPosition(int &x, int &y) {
	x = xcellsize * 3;
	y = (BOARD_Y - 3) * ycellsize;
}
void Board::GetInitTextPosition(int &x, int &y) {
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}
int Board:: values_on_board(int i,int j)
{
	return board_array[i][j];

}
void Board::set_bomb_on_board(int i,int j)
{
	bomb bo;
    boo.push_back(bo);
    boo[boo.size()-1].setbombposition(i,j);
    boo[boo.size()-1].set_blast_Counter(1);

}
void Board:: move_left()
    {
    	int i,j;
    	man->getBombermanposition(i,j);
    	if(board_array[i][j-1]==6)
    	    			eat_energy();
    	if(values_on_board(i,j-1)==0)
    	{

    		int temp=board_array[i][j];
    		board_array[i][j]=board_array[i][j-1];
    		board_array[i][j-1]=temp;
    		man->setBombermanposition(i,j-1);
    	}

    }
void Board:: move_right()
    {
    	int i,j;
    	man->getBombermanposition(i,j);
    	if(board_array[i][j+1]==6)
    	    			eat_energy();
    	if(values_on_board(i,j+1)==0)
    	{

    		int temp=board_array[i][j];
    		board_array[i][j]=board_array[i][j+1];
    		board_array[i][j+1]=temp;
    		man->setBombermanposition(i,j+1);
    	}

    }
void Board:: move_up()
    {
    	int i,j;
    	man->getBombermanposition(i,j);
    	cout<<i<<j<<endl;
    	if(board_array[i-1][j]==6)
    	    			eat_energy();
    	if(values_on_board(i-1,j)==0)
    	{

    		int temp=board_array[i][j];
    		board_array[i][j]=board_array[i-1][j];
    		board_array[i-1][j]=temp;
    		man->setBombermanposition(i-1,j);

    	}

    }
void Board:: move_down()
    {
    	int i,j;
    	man->getBombermanposition(i,j);
    	if(board_array[i+1][j]==6)
    	    			eat_energy();
    	if(values_on_board(i+1,j)==0)
    	{

    		int temp=board_array[i][j];
    		board_array[i][j]=board_array[i+1][j];
    		board_array[i+1][j]=temp;
    		man->setBombermanposition(i+1,j);
    	}

    }
void Board:: ghost_motion()
{
	if(BomberMan_alive() )
	{
		pinky_move();
		blinky_move();
		inky_move();
		Clyde_move();

	}
	else
	{
         re_play();
	}

}

void Board::initialize_pinky()
{
	int x,y;
	man->getBombermanposition(x,y);
	if(x<=9)x+=3;
	else x-=3;
	int i=0;
	for(;i<17;i++)
		if(values_on_board(x,i)==0)
		{
           y=i;
		   break;
		}
    board_array[x][y]=GHOST;
	Enemies[0]->setghostposition(x,y);
}
void Board::initialize_blinky()
{
	int x,y;
		man->getBombermanposition(x,y);
		if(x<=10)x+=1;
		else x-=1;
		int i=3;
		for(;i<17;i++)
			if(values_on_board(x,i)==0)
			{
	           y=i;
			   break;
			}
	    board_array[x][y]=GHOST;
		Enemies[1]->setghostposition(x,y);
}
void Board::initialize_inky()
{
	int x=9,y;

		int i=16;
		for(;i>0;i--)
			if(values_on_board(x,i)==0)
			{
	           y=i;
			   break;
			}

	    board_array[x][y]=GHOST;
		Enemies[2]->setghostposition(x,y);
}
void Board::initialize_Clyde()
{
	int x=7,y;
    		int i=12;
			for(;i>0;i--)
				if(values_on_board(x,i)==0)
				{
		           y=i;
				   break;
				}

		    board_array[x][y]=GHOST;
			Enemies[3]->setghostposition(x,y);

}
void Board::initialize_energizer()
{

	int x=8,y;
	int i=12;
	for(;i>0;i--)
		if(values_on_board(x,i)==0)
		{
			y=i;
			break;
		}
    board_array[x][y]=GIFT;
    Energy=new energizer(x,y);
}
void Board::re_play()
{
	int x,y;
            lives-=1;
	int a,b;

		cout<<"Enemies.size()="<<Enemies.size()<<endl;
		for(int i=0;i<Enemies.size();++i)
	            if(Enemies[i]->get_ghost_alive())
			{
				Enemies[i]->getghostposition(a,b);
		                        board_array[a][b]=0;
			}
        man->setBombermanposition(8,7);
        man->getBombermanposition(x,y);
        boo.clear();
		board_array[x][y]=BOMBERMAN;
		if(Enemies[0]->get_ghost_alive())
		initialize_pinky();
		if(Enemies[1]->get_ghost_alive())
	    initialize_blinky();
		if(percent_30_break()&&Enemies[2]->get_ghost_alive())
		initialize_inky();
		if(percent_70_break()&&Enemies[3]->get_ghost_alive())
	    initialize_Clyde();
}
void  Board:: draw_bomb()
{
  	deque<bomb>::iterator it;
  	int i=0;
  	for(it=boo.begin();i<boo.size();++it,i++)
  	{	if(it->get_blast_Counter()!=0 &&it->get_blast_Counter()<=6)
  	   {
  	          it->draw();

  	   }
  	    else
  	    {
            bool u=false,d=false,r=false,l=false,p=false;
  	    	boo.pop_front();
  	        int x,y;
  	        it->getbombposition(x,y);
  	        int i=12-x;
  	        if(board_array[x][y]==4)    // bomber man  blast
  	        	p=true;
  	        if(board_array[x][y]==5)      //ghost blast
  	        	blast_ghost(x,y);
  	        board_array[x][y]=NILL;
  	        DrawRectangle(y*60,i*60 ,60, 60,colors[ORANGE]);
  	        if(p){re_play();p=false;}
            if(board_array[x-1][y]!=1)
            {
            	if(board_array[x-1][y]==4)    // Bomber man blast
            	               u=true;
            	if(board_array[x-1][y]==3)   // red brick blast
            		break_red_bricks(x-1,y);
            	if(board_array[x-1][y]==5)    // ghost  blast
            		blast_ghost(x-1,y);
            	if(board_array[x-1][y]==2)
            		score+=50;
            	board_array[x-1][y]=NILL;
               if(u){re_play();u=false;}
               DrawRectangle(y*60,(i-1)*60 ,60, 60,colors[ORANGE]);

            }
            if(board_array[x+1][y]!=1)
            { 	if(board_array[x+1][y]==4)   // Bomber man blast
            	     d=true;
               if(board_array[x+1][y]==3)    // red brick blast
            	   break_red_bricks(x+1,y);
               if(board_array[x+1][y]==5)    // ghost blast
            	   blast_ghost(x+1,y);
               if(board_array[x+1][y]==2)
            	   score+=50;
            	board_array[x+1][y]=NILL;
            	DrawRectangle( y*60,(i+1)*60, 60,60,colors[ORANGE]);
                if(d){re_play();d=false;}
            }
            if(board_array[x][y-1]!=1)
            {	if(board_array[x][y-1]==4)         // Bomber man blast
            	      l=true;
                if(board_array[x][y-1]==3)      // red brick blast
                	break_red_bricks(x,y-1);
                if(board_array[x][y-1]==5)      // ghost blast
                	blast_ghost(x,y-1);
            	if(board_array[x][y-1]==2)
            		score+=50;
                board_array[x][y-1]=NILL;
            	DrawRectangle((y-1)*60,i*60, 60, 60,colors[ORANGE]);
            	if(board_array[x][y-1]==5)

              if(l){re_play();l=false;}
            }
          	if(board_array[x][y+1]!=1)
          	{
          		if(board_array[x][y+1]==4)     // Bomber man blast
          			   r=true;
          		if(board_array[x][y+1]==3)    // red brick blast
          			break_red_bricks(x,y+1);
          		if(board_array[x][y+1]==5)     // ghost blast
          			blast_ghost(x,y+1);
          		if(board_array[x][y+1]==2)
          			score+=50;
          		board_array[x][y+1]=NILL;
          		DrawRectangle((y+1)*60,i*60,60, 60, colors[ORANGE]);
  	          if(r){re_play();r=false;}
          	}
            it++;
  	        it->draw();

  	    }
  	    	it->set_blast_Counter(it->get_blast_Counter()+1);
  	}

}
void Board::break_red_bricks(int i,int j)
{
	score+=50;
	if(board_array[i][j]==2)
	{  board_array[i][j]=0;
	   score+=50;
	}
	if(board_array[i-1][j]==2)
	{
		board_array[i-1][j]=0;
		score+=50;
	}
	if(board_array[i+1][j]==2)
	{
		board_array[i+1][j]=0;
		score+=50;
	}
	if(board_array[i][j+1]==2)
	{
		board_array[i][j+1]=0;
		score+=50;
	}
	if(board_array[i][j-1]==2)
	{
		board_array[i][j-1]=0;
		score+=50;
	}

}
void Board::blast_ghost(int a,int b)
{

	int x,y;
	int i=0;
    for(;i<Enemies.size();++i)
    {
    	Enemies[i]->getghostposition(x,y);
    	if(x==a&&y==b)
    	{
    		score+=200;
    	    board_array[a][b]=0;
    	    Enemies[i]->set_ghost_alive(false);
    	}
    }

}
bool Board:: BomberMan_alive()
{
	   for(int i=0;i<14;++i)
	   			 	 for(int j=0;j<17;++j)
	   			    	  if (board_array[i][j]==4)
	   			    	  {  return true;
	   			    	      break;
	   			    	  }
return false;
}
void Board::again_start()
{
	lives=3;
    score=0;
	timer=0;
	option=0;
    on=0;
    boo.clear();
    num_bricks=0;
    total_bricks=0;
	Enemies.clear();
}
int Board::get_Direction_of_bomber(){return man->get_direction_man(); }
void Board::set_Direction_of_bomber(int a){man->set_direction_man(a);}
bool Board::win(){
	for(int i=0;i<14;++i)
		      for(int j=0;j<17;++j)
		    	  if(board_array[i][j]==2||board_array[i][j]==3)
		    		  return false;
	return true;
}
bool Board::percent_30_break()
{
   if(num_bricks<=(total_bricks-(total_bricks/3)))
	   return true;
   return false;
}
bool Board::percent_70_break()
{
   if(num_bricks<=(total_bricks/3))
	   return true;
   return false;
}
void Board::calculate_bricks()
{int num=0;
for(int i=0;i<14;++i)
	      for(int j=0;j<17;++j)
	    	  if(board_array[i][j]==2||board_array[i][j]==3)
	    		  num++;
set_num_bricks(num);
}
void Board::pinky_move()
{
	if(Enemies[0]->get_ghost_alive()){  int **ptr;
			Enemies[0]->copy_board_for_ghost(board_array);
	       Enemies[0]->random_mode();
	       ptr=Enemies[0]->get_board_from_ghost();
	       for(int i=0;i<14;++i)
		      for(int j=0;j<17;++j)
			     board_array[i][j]=ptr[i][j];
	}
}
void Board::blinky_move()
{
	if(Enemies[1]->get_ghost_alive())
	       {
		    if(Enemies[1]->get_ch_color())
		    	Enemies[1]->set_ch_color(false);
		    else
		    	Enemies[1]->set_ch_color(true);
	        int a,b;
	        int **ptr;
	        man->getBombermanposition(a,b);
	        Enemies[1]->getBMan_position_for_ghost(a,b);
		    Enemies[1]->copy_board_for_ghost(board_array);
		    if(Enemies[1]->get_mode()<=20)
		    	{
		    	    Enemies[1]->set_mode(Enemies[1]->get_mode()+1);
		    	    Enemies[1]->chasing_mode();

		    	}
		    else if(Enemies[1]->get_mode()>=21&&Enemies[1]->get_mode()<=27)
		        {
        	    	 Enemies[1]->set_mode(Enemies[1]->get_mode()+1);
		    	     Enemies[1]->scatter_mode();
		        }
		    else if(Enemies[1]->get_mode()>=28&&Enemies[1]->get_mode()<=38)
		        {
		    	     Enemies[1]->set_mode(Enemies[1]->get_mode()+1);
		             Enemies[1]->random_mode();
		             if(Enemies[1]->get_mode()==39)
		            	 Enemies[1]->set_mode(0);
		        }
		    ptr=Enemies[1]->get_board_from_ghost();
	       for(int i=0;i<14;++i)
	   	       for(int j=0;j<17;++j)
	   		      board_array[i][j]=ptr[i][j];
		}
}
void Board::inky_move()
{
	if(percent_30_break()&&Enemies[2]->get_ghost_alive())
		       {
		        int a,b;
		        int **ptr;
		        man->getBombermanposition(a,b);
		        Enemies[2]->getBMan_position_for_ghost(a,b);
			    Enemies[2]->copy_board_for_ghost(board_array);
			    if(Enemies[2]->get_mode()<=20)
			    	{
			    	    Enemies[2]->set_mode(Enemies[2]->get_mode()+1);
			    	    Enemies[2]->chasing_mode();

			    	}
			    else if(Enemies[2]->get_mode()>=21&&Enemies[2]->get_mode()<=27)
			        {
	        	    	 Enemies[2]->set_mode(Enemies[2]->get_mode()+1);
			    	     Enemies[2]->scatter_mode();
			        }
			    else if(Enemies[2]->get_mode()>=28&&Enemies[2]->get_mode()<=38)
			        {
			    	     Enemies[2]->set_mode(Enemies[2]->get_mode()+1);
			             Enemies[2]->random_mode();
			             if(Enemies[2]->get_mode()==39)
			            	 Enemies[2]->set_mode(0);
			        }
			    ptr=Enemies[2]->get_board_from_ghost();
		       for(int i=0;i<14;++i)
		   	       for(int j=0;j<17;++j)
		   		      board_array[i][j]=ptr[i][j];
                 }
}
void Board::Clyde_move()
{
	if(percent_70_break()&&Enemies[3]->get_ghost_alive())
			       {
			        int a,b;
			        int **ptr;
			        man->getBombermanposition(a,b);
			        Enemies[3]->getBMan_position_for_ghost(a,b);
				    Enemies[3]->copy_board_for_ghost(board_array);
				    if(Enemies[3]->get_mode()<=20)
				    	{
				    	    Enemies[3]->set_mode(Enemies[3]->get_mode()+1);
				    	    Enemies[3]->chasing_mode();

				    	}
				    else if(Enemies[3]->get_mode()>=21&&Enemies[3]->get_mode()<=27)
				        {
		        	    	 Enemies[3]->set_mode(Enemies[3]->get_mode()+1);
				    	     Enemies[3]->scatter_mode();
				        }
				    else if(Enemies[3]->get_mode()>=28&&Enemies[3]->get_mode()<=38)
				        {
				    	     Enemies[3]->set_mode(Enemies[3]->get_mode()+1);
				             Enemies[3]->random_mode();
				             if(Enemies[3]->get_mode()==39)
				            	 Enemies[3]->set_mode(0);
				        }
				    ptr=Enemies[3]->get_board_from_ghost();
			       for(int i=0;i<14;++i)
			   	       for(int j=0;j<17;++j)
			   		      board_array[i][j]=ptr[i][j];
	                 }
}
void Board::eat_energy()
{
	score+=100;
	int a,b;
	Energy->get_energizer(a,b);
	board_array[a][b]=NILL;
    Energy->set_eaten(false);
}
void Board::set_high_score()
{
   ifstream ifile;
   ifile.open("filer.txt",ios::app);
   	     if(!ifile)
   	     {
   	        cout<<"file can't be open "<<endl;
   	        exit(-1);
   	     }
   	     int fi;
   	     ifile>>fi;
   	     ifile.close();
   	     ofstream ofile;
   	     if(score>fi)
   	     {
   	    	ofile.open("filer.txt",ios::trunc);
   	    	   if(!ofile)
   	    	   {
   	    	      cout<<"file can't be open "<<endl;
   	    	      exit(-1);
   	    	   }
   	    		     ofile<<score;
   	     }
   	     ofile.close();
   	     ifile.open("filer.txt",ios::app);
   	     	     if(!ifile)
   	     	     {
   	     	        cout<<"file can't be open "<<endl;
   	     	        exit(-1);
   	     	     }
   	     	     ifile>>high_score;
   	     	     ifile.close();
}
