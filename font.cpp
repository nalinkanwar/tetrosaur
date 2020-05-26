#include "font.h"

font::font(const char* path, int size) {
    this->f = TTF_OpenFont(path, size);
}


font::~font() {
    if(this->f)
        TTF_CloseFont(this->f);
    this->f = nullptr;
}

/*
SDL_Color c;
SDL_Rect trect;
const char *cstr;

trect.x = this->X() + 2; trect.y = this->Y() + 2;
trect.w = SCALING_UNIT - 4; trect.h = SCALING_UNIT - 4;
c.r = 255; c.g = 255; c.b = 255; c.a = 255;
if(this->isMovable())
    cstr = "1";
else
    cstr = "0";

text_surface = TTF_RenderText_Solid(font, cstr, c);
stexture = SDL_CreateTextureFromSurface(rend, text_surface);

if(text_surface == nullptr || stexture == nullptr) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Error in text");
}
SDL_RenderCopy(rend, stexture, NULL, &trect);
*/
