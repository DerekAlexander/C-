#if !defined(__PEN_H__)
#define __PEN_H__
#pragma once

class PEN
{
public:

	PEN();
	~PEN();

	HPEN createPen(int red, int green, int blue, int width , int penStyle)const;

};

#endif

