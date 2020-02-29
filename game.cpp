//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Brick Slayer...
//============================================================================

#ifndef Bomberman_CPP_
#define Bomberman_CPP_
#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
enum direction {
	UP_man, DOWN_man, LEFT_man, RIGHT_man,
	};
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void DrawEnemy(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/, float gw/* = 6 Enemy Width in Units*/,
		float gh/* = 7Enemy Height in Units*/,ColorNames legs_color,ColorNames eyes_color){
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float) gw / ogw, sy = (float) gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw Enemy
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[legs_color]);
	DrawCircle(3.25, 1, 0.75, colors[legs_color]);
	DrawCircle(5.85, 1, 0.75, colors[legs_color]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[eyes_color]);
	DrawCircle(4.95, 3.95, 0.75, colors[eyes_color]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

//Number of Vertices used to draw Bomberman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/,
		const ColorNames &colorname/*Bomberman Colour*/,int  direct=1) {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);

	glBegin (GL_TRIANGLE_FAN);


	glVertex4f(sx, sy, 0, 1);
	if(direct==UP_man)
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx - pmvertices[i][1], sy - pmvertices[i][0], 0, 1);
	if(direct==DOWN_man)
		for (int i = 0; i < npmvertices; ++i)
			glVertex4f(sx + pmvertices[i][1], sy + pmvertices[i][0], 0, 1);
	if(direct==LEFT_man)
		for (int i = 0; i < npmvertices; ++i)
			glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	if(direct==RIGHT_man)
		for (int i = 0; i < npmvertices; ++i)
			glVertex4f(sx - pmvertices[i][0], sy - pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}
/*
 * Main Canvas drawing function.
 * */
Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0.1/*Red Component*/, 0.6,	//148.0/255/*Green Component*/,
			0.2/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	//
	if(b->get_timer()==-1&&b->get_option()==0 )
	{
		glClearColor(0.3/*Red Component*/, 0.3,	//148.0/255/*Green Component*/,
					0.5/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
			glClear (GL_COLOR_BUFFER_BIT); //Update the colors
			 b->Draw_manu();
	}
	else if(b->get_timer()!=-1&&b->get_option()==4)
	{
		glClearColor(0.2/*Red Component*/, 0.2,	//148.0/255/*Green Component*/,
								.5/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
						glClear (GL_COLOR_BUFFER_BIT); //Update the colors
         b->pause();
	}
	else if(b->get_timer()==-1 && b->get_option()==2)
	{

	glClearColor(0.2/*Red Component*/, 0.2,	//148.0/255/*Green Component*/,
						.5/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
				glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	       b->Draw_rule();
	}
	else if(b->get_lives()==0 && b->get_option()==3)
	{

		b->again_start();
		b->InitalizeBoard(1020, 840);
		b->Draw();
	}
	else if(b->win())
	{glClearColor(0.2/*Red Component*/, 0.2,	//148.0/255/*Green Component*/,
			.5/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		b->set_lives(0);
		b->set_high_score();
		b->Draw_wining();
	}
	else if(b->get_lives()==0)
	{
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
						0/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
				glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		b->Draw_GameOver();
	}
	else //(b->get_lives()>0)
    {
       b->Draw();
    }

//	int x, y;
//	cout << x << "  y= " << y << endl << flush;
////	DrawEnemy(x, y, PINK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
//
//	//	glPopMatrix();
//	//	DrawString(x, y, "Score = 000", colors[5]);

	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */
void MouseClick(int key,int state,int x,int y)
{
	int x_=x/60;
	int y_=(780-y)/60;
   if(key==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	   cout<<"x_="<<x_<<"x="<<x<<"  y_="<<y_<<"y="<<y<<endl;
}
void NonPrintableKeys(int key, int x, int y) {

	if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		b->set_Direction_of_bomber(LEFT_man);
		 b->move_left();
	} else if (key== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		b->set_Direction_of_bomber(RIGHT_man);
		b->move_right();
	} else if (key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		b->set_Direction_of_bomber(UP_man);
		b->move_up();
	}

	else if (key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		b->set_Direction_of_bomber(DOWN_man);
		b->move_down();

	}


	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	 glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.

 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		       int x_,y_;
		       b->GetBombermanPosition(x_,y_);
		       b->set_bomb_on_board(x_,y_);

	}
	if(key==49)
	{
		if(b->get_timer()==-1)
			b->set_timer(0);

	}
	if(key==50)
	{

 		if(b->get_timer()==-1)
           b->set_option(2);

	}
	if(key=='y'||key=='Y')
	   b->set_option(3);
	if(key=='p'||key=='P')
		b->set_option(4);
	if(key=='d'||key=='D')
		b->set_option(0);
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
     GameDisplay();
     if(b->get_timer()!=-1&&b->get_lives()>0 &&b->get_option()!=4){
    	 b->ghost_motion();
    	 b->set_timer(b->get_timer()+1);
     }

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(500.0, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	Bomberman m;
	bomb boo;
	b = new Board(m,boo,60, 60); // create a new board object to use in the Display Function ...
	int width = 1020, height = 840; // i have set my window size to be 800 x 600
		b->InitalizeBoard(width, height);
		for(int i=0;i<14;++i)
			     {	 for(int j=0;j<17;++j)
			         {
			    	    cout<<b->values_on_board(i,j)<<" ";
			         }
			     cout<<endl;
			     }


	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Bomber Bomberman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...


	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	glutMouseFunc(MouseClick);//Mouse Function
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */
