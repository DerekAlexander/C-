#include "stdafx.h"
#include "RECTANGLE.h"
#include <stdlib.h>

//constructor 
RECTANGLE::RECTANGLE(int left, int top, int right, int bottom)
{
	assign(left, top, right, bottom);
}

//deconstructor
RECTANGLE::~RECTANGLE()
{
}

int	RECTANGLE::getTop(HDC hdc) const
{
	
	return myTop;

}

int	RECTANGLE::getBottom(HDC hdc) const
{
	
	return myBottom;

}

int	RECTANGLE::getRight(HDC hdc) const
{
	
	return myRight;

}

int	RECTANGLE::getLeft(HDC hdc) const
{

	return myLeft;

}

void RECTANGLE::assign(int left, int top, int right, int bottom)
{
	myTop = top;
	myLeft = left;
	myRight = right;
	myBottom = bottom;
}

void RECTANGLE::offset(int dx, int dy)
{
	myTop = myTop + dy;
	myLeft = myLeft + dx;
	myRight = myRight + dx;
	myBottom = myBottom + dy;
}

void RECTANGLE::inflate(int dx, int dy)
{
	myTop = myTop - dy;
	myLeft = myLeft - dx;
	myRight = myRight + dx;
	myBottom = myBottom + dy;
}

RECTANGLE RECTANGLE::random(const RECTANGLE& cr)
{

	int xPos = (rand() % cr.width());
	int yPos = (rand() % cr.heigth());

	int rw = rand() % (cr.width() - xPos);
	int rh = rand() % (cr.heigth() - yPos);

	RECTANGLE rr( xPos, yPos, (xPos - rw), (yPos - rh));

	return rr;

}

