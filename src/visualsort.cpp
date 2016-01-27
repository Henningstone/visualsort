#include <SDL2/SDL.h> // FOR WINDOWS, CHANGE THIS TO "sdl.h" !!
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "console.h"
#include "util.h"
#include "visualsort.h"


bool CVisualsort::Minsort(Sint16 *list, int numElements)
{
	if(numElements < 2)
		return true;

	for(int curr = 0; curr < numElements-1; curr++)
	{
		int minIndex = curr;
		for(int i = curr + 1; i < numElements; i++)
		{
			OnRender(curr, minIndex, i);

			if(list[i] < list[minIndex])
				minIndex = i;

		}
		SDL_Delay(1);

		if(minIndex != curr)
		{
			int temp = list[curr];
			list[curr] = list[minIndex];
			list[minIndex] = temp;
		}
		else if(curr==0) return true;
	}
	return false;
}


CVisualsort::CVisualsort()
{
	OnInit();
	mainloop();
}

CVisualsort::~CVisualsort()
{
	if(Window())
		SDL_DestroyWindow(Window());
	SDL_Quit();

	delete m_pConsole; m_pConsole = 0;
	delete m_pRender; m_pRender = 0;
}

void CVisualsort::OnInit()
{
	m_Running = true;
	m_pConsole = new CConsole();
	m_pRender = new CRender(this);
	memset(m_List, 0, sizeof(m_List));

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		char aBuf[256];
		snprintf(aBuf, sizeof(aBuf), "Failed to initialize! SDL_Error: %s\n", SDL_GetError());
		Console()->Print("SDL2", aBuf);
		Exit(1);
	}

	// Create window
	if(!(m_pWindow = SDL_CreateWindow("Some nizze schtuff", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
	{
		char aBuf[256];
		snprintf(aBuf, sizeof(aBuf), "Failed to create window! SDL_Error: %s\n", SDL_GetError());
		Console()->Print("SDL2", aBuf);
		Exit(2);
	}

	 // We must call SDL_CreateRenderer in order for draw calls to affect this window.
	if(!(m_pRenderer = SDL_CreateRenderer(Window(), -1, 0)))
	{
		char aBuf[256];
		snprintf(aBuf, sizeof(aBuf), "Failed to create renderer! SDL_Error: %s\n", SDL_GetError());
		Console()->Print("SDL2", aBuf);
		Exit(3);
	}
}

void CVisualsort::Exit(int status)
{
	delete this;

	exit(status);
}

void CVisualsort::OnUpdate()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			m_pConsole->Print("system", "Stopping!");
			m_Running = false; Exit(0);
			break;
		}
	}
}

int CVisualsort::OnRender(int h1, int h2, int h3)
{
	OnUpdate();


	//static Uint8 offset=0; static char direction = 1;
	SDL_SetRenderDrawColor(Renderer(), 0x88, 0x88, 0x88, 0xFF);//SDL_SetRenderDrawColor(Renderer(), (offset+=direction), 0xFF, 0xFF-offset, 0x01);
	SDL_RenderClear(Renderer());
	//if(offset >= 0xFF) direction = -1;
	//if(offset <= 0) direction = 1;


	Rect MainView(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), Bar;
	for(int i = 0; i < NUM_ELEMENTS; i++)
	{
		MainView.VSplitLeft(3, 0, &MainView);
		MainView.VSplitLeft(10, &Bar, &MainView);
		Bar.h = /*SCREEN_HEIGHT*/m_List[i]-5;
		Bar.y += SCREEN_HEIGHT - Bar.h;
		Render()->DoRect(Bar, vec4(i == h1 ? 0xFF : 0x00, h3 == i ? 0xFF : 0x00, h2 == i ? 0xFF : 0x00,      0xFF));
	}


	// Render the buffer to the screen
	SDL_RenderPresent(Renderer());

	return 0;
}

void CVisualsort::mainloop()
{
	// Create our list
	for(Sint16 i = 0; i < NUM_ELEMENTS; i++)
	{
		//int index = 0;
		//while(m_List[index = rand()%NUM_ELEMENTS]);
		m_List[i] = rand()%500+10;
	}

	/*
		Rect MainView(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), Bar;
		for(int i = 0; i < NUM_ELEMENTS; i++)
		{
			MainView.VSplitLeft(3, 0, &MainView);
			MainView.VSplitLeft(10, &Bar, &MainView);
			Bar.h = arr[i]+1;
			SDL_FillRect(m_pSurface, Bar.SDL(), SDL_MapRGB(m_pSurface->format, 0xFF-(i<<2), i<<1, 0xFF-i));
		}
	*/

	/* mainloop */
	while(Running())
	{
		// Update the surface
		//SDL_UpdateWindowSurface(Window());

		// Clear the entire screen to white
		static bool bla = false;
		if(!bla)
			bla = Minsort(m_List, NUM_ELEMENTS);
		OnUpdate();
		// Prepare the rendering buffer
/*		int status; static int curr=0, sorting=0;
		if((status = OnRender() != 0)
		{
			char aBuf[128];
			snprintf(aBuf, sizeof(aBuf), "Preparing render buffer errored! Status code: %i", status);
			m_pConsole->Print("system", aBuf);
			Exit(5|status<<8);
		}
*/

		SDL_Delay(100);
	}

	Exit(0);
}


int main(int argc, char* args[])
{
	srand(time(0));

	new CVisualsort;

	printf("<< exiting!");

	// Cleanup SDL subsystems
	SDL_Quit();

	return 0;
}
