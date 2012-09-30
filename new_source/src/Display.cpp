#include "Display.h"

Display::Display(int w, int h)
    : surface(0)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) 
        throw 0;

    surface = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
}

Display::~Display()
{
    if (!surface)
        return;

    SDL_FreeSurface(surface);

    SDL_Quit();
}

void Display::update() const
{
    if (surface)
        SDL_Flip(surface);
}

void Display::clear(unsigned char c1, unsigned char c2, unsigned char c3) const
{
    if (surface)
        SDL_FillRect(surface,NULL, SDL_MapRGB(surface->format, c1, c2, c3));
}

void Display::putPixel(int x, int y, int pixel) const
{
    if (x<0 || y<0 || x >= getWidth() || y >= getHeight())
        return;

    y=getHeight()-y-1;

    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } 
            else 
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

int Display::getWidth() const
{
    if (!surface)
        return -1;

    return surface->w;
} 

int Display::getHeight() const
{
    if (!surface)
        return -1;

    return surface->h;
} 
