#include <stdio.h>
#include <SDL2/SDL.h>
#include "console.h"

void CConsole::Print(const char *sys, const char *msg)
{
	printf("[%s] %s\n", sys, msg);
}
