#if !defined(__RECTANGLE_H__)
#define __RECTANGLE_H__
#pragma once


class RECTANGLE
{
public:
	RECTANGLE(int left = 0, int top = 0, int right = 0, int bottom = 0 );

	~RECTANGLE();

	int getTop(HDC hdc) const;
	int getRight(HDC hdc)const;
	int getLeft(HDC hdc) const;
	int getBottom(HDC hdc)const;

	void assign(int left = 0, int top = 0, int right = 0, int bottom = 0);

	void offset(int dx, int dy);

	void inflate(int dx, int dy);

	int width() const
	{
		return  (myRight - myLeft);
	}

	int heigth()const
	{
		return (myBottom - myTop);
	}

	static RECTANGLE random(const RECTANGLE& cr);


private:
	int myTop, myBottom, myRight, myLeft;
	HWND myHWND;
};

#endif
