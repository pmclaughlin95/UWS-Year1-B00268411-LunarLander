/* A 2d Graphics Programming project - Lunar Lander
By B00268411


Lander.h, Lander.cpp and main were taken from Anisprite code from the module on moodle, they were added to and some parts, changed to suit my own code.

Bitmap.h, Bitmap.cpp, random.h and random.cpp were also taken from the moodle site.
*/


#include"Bitmap.h"
#include"Lander.h"
#include "Moon.h"
#include<gl/glut.h>
#include <iostream>
#include <time.h>
#include<cmath>
#include<stdio.h>
#include<string>
#include<sstream>	
#include<stdexcept>
#include <stdlib.h>

#define windowWidth	800
#define windowHeight 	600

 
 Bitmap *background;
 Lander *l;
 Moon *M;
 int ticks = 50;
float elapsedTime = 1.0;


using namespace std;

void init() {
	M = new Moon;
	// Just a bitmap file, with transparency enabled (true)...
	background = new Bitmap("space.bmp", true);
	// An animated sprite, at location 256, 0, based on a strip bitmap, 1 columns by 1 row,
	//i had tried to make this animated, however, it would not work so, just a single sprite	 
	l = new Lander(256,0, "landerStrip3.bmp", 1, 1);
	l->moveTo(300, 500);
  
}
 
 

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	// Draw the background...
	background->draw(0, 0, 800, 600);
	//...and then the sprite on top of it...
	//draws the lander sprite 
	l->draw();
	//shows the moon 
	M->show();
	glutSwapBuffers();
}

void update() {
 	l->move();  // updates the move function to make the lander move left, right or thrust up
 	glutPostRedisplay();
}

void timer(int arg) {
 	update();
 	glutTimerFunc(20, timer, 0);
	
}



void arrowKeys(int key, int x, int y)	
{
	// code for keyboard input -  up, left and right arrow keys
 
	switch (key)
	{
	case GLUT_KEY_UP:					
		if (l->getFuel() > 0)
			l->move(0, 3);

		break;
	case GLUT_KEY_RIGHT:
		if (l->getFuel() > 0) {
		l->move(3, 0);
	}
 			break;
		case GLUT_KEY_LEFT:					
			if(l->getFuel() > 0)
				l->move(-3, 0);
		 
			break;
	}
}
 

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Lunar lander window");
	glClearColor(0.0, 0.0, 1.0, 0.0);
	gluOrtho2D(0, windowWidth, 0, windowHeight);
	init();
	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutSpecialFunc(arrowKeys);
	glutMainLoop();
	return 0;
}
