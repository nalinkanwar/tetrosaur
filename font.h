#ifndef FONT_H
#define FONT_H

#include "SDL.h"
#include "SDL/SDL_ttf.h"
#include "drawable.h"

class font: public Drawable
{
    private:
        TTF_Font *f=NULL;
        SDL_Rect frect;
        SDL_Surface *fsurf=nullptr;
        SDL_Texture *ftext=nullptr;
        char *cstr=NULL;
        int fsize;
    public:
        font();
        font(const char* path, int size);
        ~font();

        bool load(const char* path, int size);
        bool prepare(SDL_Renderer *srend);
        bool setText(const char* tcstr);
        bool setSize(int n);
        bool Draw(SDL_Renderer *srend);
};

#endif // FONT_H
