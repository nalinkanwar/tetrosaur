#ifndef FONT_H
#define FONT_H

#include <string>
#include "SDL.h"
#include "SDL/SDL_ttf.h"

class font
{
    private:
        TTF_Font *f=nullptr;
        SDL_Rect srect;
    public:
        font(const char* path, int size);
        ~font();
        bool setSize(int n);
        bool draw(SDL_Renderer *srend);
};

#endif // FONT_H
