#if !defined(__PAINT_H__)
#define __PAINT_H__
#pragma once

#include "RECTANGLE.h"
#include "PEN.h"
#include "BRUSH.h"


class PAINT
{
public:
	PAINT(HWND hWnd);

	~PAINT();

	void usePen(const PEN pen, int red, int green, int blue, int width = 5, int penStyle = PS_SOLID);

	void useBrush(const BRUSH brush, int red, int green, int blue);

	void drawRectangle ( const RECTANGLE&  rect);
	void drawCircle(const RECTANGLE&  rect);
	
	void drawLine( int x1, int y1,   int x2, int y2 );		//draws a line from (x1, y1) to (x2, y2)
	void PAINT::moveTo(int x1, int y1);
	void PAINT::lineTo(int x2, int y2);



private:
	HDC			myHDC;
	HWND		myHWND;
	PAINTSTRUCT myPS;
};


#endif
