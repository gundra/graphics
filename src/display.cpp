#include "display.h"

#include <assert.h>

Display::Display(int width, int height)
	: m_screen(0), m_width(width), m_height(height)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0) 
		throw 0;

	m_screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
	if(!m_screen) 
	{
		SDL_Quit();
		throw 1;
	}

	SDL_WM_SetCaption("sdl...", NULL);
}

Display::~Display()
{
	SDL_Quit();
}

void Display::render(Frame& frame)
{
	SDL_LockSurface(m_screen);

	for (int x=0; x<m_width; ++x)
		for (int y=0; y<m_height; ++y)
			//((uint32_t*)m_screen->pixels)[y * m_width + x] = frame.getPixel(x,y).toInt32();
			((uint32_t*)m_screen->pixels)[(m_height-1-y) * m_width + x] = frame.getPixel(x,y).toInt32();

	SDL_UnlockSurface(m_screen);

	SDL_UpdateRect(m_screen, 0, 0, 0, 0);
}
