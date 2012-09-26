#include <SDL/SDL.h>
#include "frame.h"

class Display
{
	public:
		Display(int width, int height);
		~Display();

		void render(Frame& frame);

	private:
		Display(const Display&);
		Display& operator=(const Display&);

		SDL_Surface* m_screen;
		int m_width;
		int m_height;
};
