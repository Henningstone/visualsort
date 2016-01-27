#include "util.h"

void Rect::VSplitLeft(Uint16 cut, Rect *left, Rect *right) const
{
	if(left)
	{
		left->w = cut;
		left->y = this->y;
		left->x = this->x;
		left->h = this->h;
	}

	if(right)
	{
		right->w = this->w - cut;
		right->y = this->y;
		right->x = this->x + cut;
		right->h = this->h;
	}
}

void Rect::VSplitRight(Uint16 cut, Rect *left, Rect *right) const
{
	if(right)
	{
		right->w = cut;
		right->y = this->y;
		right->x = this->x + this->w - cut;
		right->h = this->h;
	}

	if(left)
	{
		left->w = this->w - cut;
		left->y = this->y;
		left->x = this->x;
		left->h = this->h;
	}
}

void Rect::VSplitMid(Rect *left, Rect *right) const
{
	if(left)
	{
		left->w = this->w>>1;
		left->y = this->y;
		left->x = this->x;
		left->h = this->h;
	}

	if(right)
	{
		right->w = this->w>>1;
		right->y = this->y;
		right->x = this->x + (this->w>>1);
		right->h = this->h;
	}
}
