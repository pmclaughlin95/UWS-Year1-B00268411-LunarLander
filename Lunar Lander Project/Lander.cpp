/* Lander (Animated Sprite) class.
*
* Copyright (c) 2010, Alistair McMonnies
* alistair.mcmonnies@uws.ac.uk

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

alistair.mcmonnies@uws.ac.uk

last tested 14/10/2010
*
*/

#include "Bitmap.h"
#include<gl/glut.h>
#include"Lander.h"
#include <iostream>

using namespace std;

clock_t timeSinceLastUpdate;

// A general purpose initialization routine to support all constructors...
void Lander::init(int ix, int iy, int icols, int irows, int idx, int idy) {
	x = ix;
	y = iy;
	dx = idx;
	dy = idy;
	width = pic->getWidth();
	height = pic->getHeight();
	ncols = icols;
	nrows = irows;
	currentCell = 0;
	setSpriteSheetDimensions(width, height);
	ref_x = ref_y = 0;
	updatemode = UPDATEONASK;
	drawmode = NOFLIP;
	scale = 0.01;
	mass = 60;
	fuel = 100;
 	timeStep = 100;
	timeSinceLastUpdate = clock();
	gravityForce = -0.1622;
}

Lander::Lander(int initial_x, int initial_y, const char *file, int incols, int inrows)
{
	pic = new Bitmap(file, true);
	this->init(initial_x, initial_y, incols, inrows, 0.0, 0.0);
}

Lander::Lander(int initial_x, int initial_y, Bitmap *ipic, int incols, int inrows)
{
	pic = ipic;
	this->init(initial_x, initial_y, incols, inrows, 0.0, 0.0); 
}

Lander::Lander(int initial_x, int initial_y, int initial_dx, int initial_dy, const char *file, int incols, int inrows)
{
	pic = new Bitmap(file, true);
	this->init(initial_x, initial_y, incols, inrows, initial_dx, initial_dy);
}

Lander::Lander(int initial_x, int initial_y, int initial_dx, int initial_dy, Bitmap *ipic, int incols, int inrows)
{
	pic = ipic;
	this->init(initial_x, initial_y, incols, inrows, initial_dx, initial_dy);
}

void Lander::draw()
{
	int currentCol = currentCell % ncols;
	int currentRow = currentCell / ncols;
	int cx = cellWidth * currentCol;
	int cy = cellHeight * currentRow;
	if ((dx >= 0 && drawmode == AUTOFLIP) || drawmode == NOFLIP)
		pic->setOrientation(NORMAL);
	else
		pic->setOrientation(MIRROR_X);
	pic->drawAt(x - ref_x, y - ref_y, cx, cy, cellWidth, cellHeight);
}

void Lander::setUpdatemode(UpdateMode um) {
	updatemode = um;
}
void Lander::setDrawmode(DrawMode dm) {
	drawmode = dm;
}
void Lander::nextCell() {
	currentCell++;
	if (currentCell == ncols*nrows)
		currentCell = 0;
}
void Lander::prevCell() {
	currentCell--;
	if (currentCell<0)
		currentCell = ncols*nrows - 1;
}

//gravity implemented inside the move functions using variables and maths 
void Lander::move(){
if (clock() - timeSinceLastUpdate >= timeStep)
{

	prevY = y;
	force = mass*gravityForce + thrust;
	acceleration = force / mass;
	vel2 = (vel1 + acceleration*timeStep)*scale;
	averageVelocity = (vel1 + vel2) / 2;
	y = prevY + (averageVelocity*timeStep)*scale;
	vel1 += vel2;
 }
thrust = 0;
 if (updatemode == UPDATEONMOVE) {
	nextCell();
}


glutPostRedisplay();
}

void Lander::move(int by_x, int by_y) {
	x += by_x;

	if (by_y > 0 & fuel > 0)
	{
		thrust = 100;
		fuel = fuel - 1;

	}
	else
	{
		thrust = 0;
	}


	if (updatemode == UPDATEONMOVE) {
		nextCell();
	}
}


bool Lander::intersects(int xx, int yy, int ww, int hh) {
	if (x + cellWidth<xx || x>xx + ww)	// No overlap in x-axis
		return false;
	if (y + cellHeight<yy || y>yy + hh)	// No overlap in y-axis
		return false;
	// Overlaps in both axes, so...
	return true;
}

void Lander::calculate_cells() {
	// Figure out the cell width and height as a proportion of the picture...
	cellWidth = sheet_width / ncols;
	cellHeight = sheet_height / nrows;
}

void Lander::setSpriteSheetDimensions(int w, int h) {
	sheet_width = w;
	sheet_height = h;
	calculate_cells();
}
 
Lander::~Lander() {
	if (pic)
		delete pic;
}
 