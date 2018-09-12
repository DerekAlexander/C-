#include "stdafx.h"
#include "BRUSH.h"

BRUSH::BRUSH()
{
}

BRUSH::~BRUSH()
{
}

HBRUSH BRUSH::createBrush(int red, int green, int blue) const
{
	HBRUSH hBrush = CreateSolidBrush( RGB(red, green, blue));
	return hBrush;
};
