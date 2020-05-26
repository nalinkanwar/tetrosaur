#ifndef GAMETEXT_H
#define GAMETEXT_H

#include <string>
#include "font.h"

class GameText: public Drawable
{
    private:
        Font* f=nullptr;
        SDL_Rect frect;
        SDL_Surface *fsurf=nullptr;
        SDL_Texture *ftext=nullptr;
        std::string gstr;
        bool dirty = false;
    public:
        GameText();
        GameText(Font *f);
        ~GameText();

        bool prepare(SDL_Renderer *srend);
        void setFont(Font *f);
        bool setText(const char* tcstr);
        bool setText(std::string cstr);

        bool Draw(SDL_Renderer *srend);
};

#endif // GAMETEXT_H
