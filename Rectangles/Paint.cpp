#include "stdafx.h"
#include "PAINT.h"
#include "RECTANGLE.h"
#include "PEN.h"
#include "BRUSH.h"

PAINT::PAINT(HWND hWnd)
{	
	myHWND = hWnd;
    myHDC = BeginPaint(myHWND, &myPS);
}


PAINT::~PAINT()
{
	EndPaint(myHWND, &myPS);
}

void PAINT::usePen(const PEN myPen, int red, int green, int blue, int width, int penStyle)
{
	
	
	HGDIOBJ obj = SelectObject(myHDC,myPen.createPen(red, green, blue, width, penStyle) );

	DeleteObject(obj);

}

void PAINT::useBrush(const BRUSH myBrush, int red, int green, int blue)
{

	HGDIOBJ obj = SelectObject(myHDC, myBrush.createBrush(red, green, blue));

	DeleteObject(obj);

}

void PAINT::drawRectangle ( const RECTANGLE& rect )
{
	
	Rectangle(myHDC, rect.getLeft(myHDC), rect.getTop(myHDC), rect.getRight(myHDC), rect.getBottom(myHDC) );

}

void PAINT::drawCircle ( const RECTANGLE&  rect )
{

	Ellipse(myHDC, rect.getLeft(myHDC), rect.getTop(myHDC), rect.getRight(myHDC), rect.getBottom(myHDC));

}

void PAINT::drawLine( int x1, int y1, int x2, int y2 )
{
	MoveToEx(myHDC, x1, y1, NULL);
	LineTo(myHDC, x2, y2);
}

void PAINT::moveTo(int x1, int y1)
{
	MoveToEx(myHDC, x1, y1, NULL);
}

void PAINT::lineTo(int x2, int y2)
{
	LineTo(myHDC, x2, y2);
}


