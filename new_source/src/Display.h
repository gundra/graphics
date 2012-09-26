#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL/SDL.h>

class Display
{
    public:
        Display(int w, int h);
        ~Display();

        void update() const;
        void clear(unsigned char c1 = 0, unsigned char c2 = 0, unsigned char c3 = 0) const;

        void putPixel(int x, int y, int pixel) const;

        int getWidth() const;
        int getHeight() const;

    private:
        Display(const Display&);
        Display& operator=(const Display&);

    public:
        SDL_Surface* surface;
};

#endif /* DISPLAY_H */
