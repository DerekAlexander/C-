#include "stdafx.h"
#include "PEN.h"

PEN::PEN()
{
}

PEN::~PEN()
{
}

HPEN PEN::createPen(int red, int green, int blue, int width, int penStyle) const
{
	HPEN hpen =  CreatePen(penStyle, width, RGB(red, green, blue));
	return hpen;
};
