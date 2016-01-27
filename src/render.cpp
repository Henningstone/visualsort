#include <SDL2/SDL.h>

#include "render.h"
#include "util.h"
#include "visualsort.h"

void CRender::Color(vec4 color)
{
	SDL_SetRenderDrawColor(m_pMain->Renderer(), color.r, color.g, color.b, color.a);
}

void CRender::DoRect(Rect &r)
{
	SDL_RenderFillRect(m_pMain->Renderer(), r.SDL());
}

void CRender::DoRect(Rect &r, vec4 color)
{
	Color(color);
	DoRect(r);
}
