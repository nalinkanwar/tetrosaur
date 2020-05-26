#ifndef FONT_H
#define FONT_H

#include "SDL.h"
#include "SDL/SDL_ttf.h"
#include "drawable.h"
#include <string>


class Font
{
    private:
        TTF_Font *f=NULL;
        size_t fsize;
    public:
        Font(const char* path, int size);
        bool load(const char* path, int size);
        bool isLoaded();
        TTF_Font* getFont();
};

#endif // FONT_H
