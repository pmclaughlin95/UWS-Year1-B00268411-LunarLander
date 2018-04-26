 
#include"Moon.h"
 #include<gl/glut.h>
#include"random.h"
 Moon::Moon()

{

	for (int i = 0; i < 100; i++) {	
		lineHeight[i] = rnd(50, 100); //picks random heights for the moon's spikey surface using the array "lineHeight[]"
	}
	  flatArea1 = (5, 20);
	  flatArea2 = (20, 45); // creates flat surfaces at random x and y coordinates for the lander to land on using the flat area variables from the header file 
	  flatArea3 = (45, 60);
 
	  // these insert each of the flat areas into the game using for loops
	float h = lineHeight[rnd(flatArea1)];
	for (int i = flatArea1; i < flatArea1 + 10; i++) {	 
		lineHeight[i] = h;
	}

	h = lineHeight[rnd(flatArea2)];
	for (int i = flatArea2; i < flatArea2 + 10; i++) {	 
		lineHeight[i] = h;
	}
	h = lineHeight[rnd(flatArea3)];
	for (int i = flatArea3; i < flatArea3 + 10; i++) {	 
		lineHeight[i] = h;
	}

}


void Moon::show()
{
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 1, 1);
	glLineWidth(7);

	glVertex2f(3, 1);
	for (int i = 0; i<500; i++) {
		glVertex2f(i * 10, lineHeight[i]);
	}
	glVertex2f(1000, 5);
	glEnd();
}

