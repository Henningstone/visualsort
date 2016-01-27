#ifndef VISUALSORT_H
#define VISUALSORT_H

//#include <stdlib.h>
//#include <memory>

#include "console.h"
#include "render.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
#define NUM_ELEMENTS 61

class CRender;

class CVisualsort
{
	bool m_Running;
	Sint16 m_List[NUM_ELEMENTS];

	CConsole *m_pConsole;
	CRender *m_pRender;

	/* The window we'll be rendering to */
	//std::shared_ptr<SDL_Window> m_pWindow;
	SDL_Window *m_pWindow;

	/* The renderer we'll be using */
	//std::shared_ptr<SDL_Renderer> m_pRenderer;
	SDL_Renderer *m_pRenderer;

	void OnUpdate();
	int OnRender(int h1, int h2, int h3);
	void mainloop();
	bool Minsort(Sint16 *list, int numElements);

public:
	CVisualsort();
	~CVisualsort();

	void Exit(int status);
	void OnInit();

	bool Running() const { return m_Running; }
	CRender *Render() const { return m_pRender; }
	CConsole *Console() const { return m_pConsole; }
	SDL_Window *Window() const { return m_pWindow; }
	SDL_Renderer *Renderer() const { return m_pRenderer; }


};

#endif
