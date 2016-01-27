#ifndef UTIL_H
#define UTIL_H
#include <SDL2/SDL.h>

class Rect
{
	SDL_Rect *sdl;

public:
	Sint16 x; Sint16 y; Uint16 w; Uint16 h;

	Rect() { sdl = new SDL_Rect; x=0; y=0; w=0; h=0; }
	Rect(Sint16 _x, Sint16 _y, Uint16 _w, Uint16 _h) : x(_x), y(_y), w(_w), h(_h) { sdl = new SDL_Rect; }
	Rect(SDL_Rect &r) : x(r.x), y(r.y), w(r.w), h(r.h) { sdl = new SDL_Rect; }
	~Rect() { delete sdl; }

	SDL_Rect *SDL() const { sdl->x = x; sdl->y = y; sdl->w = w; sdl->h = h; return sdl; }

	void VSplitLeft(Uint16 cut, Rect *left, Rect *right) const;
	void VSplitRight(Uint16 cut, Rect *left, Rect *right) const;
	void VSplitMid(Rect *left, Rect *right) const;

};


class vec4
{
public:

	union
	{
		struct { Uint8 r, g, b, a; };
		struct { Uint8 x, y, p, q; };
	};

	vec4() { r=0; g=0; b=0; a=0; }
	vec4(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a) : r(_r), g(_g), b(_b), a(_a) { }
};


#endif
