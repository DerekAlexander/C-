#if !defined(__BRUSH_H__)
#define __BRUSH_H__
#pragma once

class BRUSH
{
public:
	BRUSH();
	~BRUSH();

	HBRUSH createBrush(int red, int green, int blue)const;

};

#endif
