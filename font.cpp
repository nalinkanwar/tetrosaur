#include "font.h"

font::font(const char* path, int size) {
    this->fsize = size;
    this->load(path, size);
}

font::font() {

}

font::~font() {
    if(this->f == NULL)
        TTF_CloseFont(this->f);
    this->f = NULL;

    if(this->fsurf != nullptr)
        SDL_FreeSurface(this->fsurf);

    if(this->ftext != nullptr)
        SDL_DestroyTexture(this->ftext);

    free(this->cstr);
}

bool font::load(const char* path, int size) {

    this->f = TTF_OpenFont(path, size);
    if(this->f == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to init TTF library: %s!", TTF_GetError());
        return false;
    }
    this->fsize = size;

    return true;
}

bool font::setText(const char* tcstr) {

    this->cstr = strdup(tcstr);
    if(this->cstr == NULL) return false;
    return true;
}

bool font::prepare(SDL_Renderer *srend) {

    SDL_Color c;
    c.r = this->R(); c.g = this->G(); c.b = this->B(); c.a = this->A();

    if(this->cstr == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No string set");
        return false;
    }

    /* generate texture to be plotted */
    this->fsurf = TTF_RenderText_Blended(this->f, this->cstr, c);
    this->ftext = SDL_CreateTextureFromSurface(srend, this->fsurf);

    if(this->fsurf == nullptr || this->ftext == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Error in text");
        return false;
    }

    this->frect.x = this->X(); this->frect.y = this->Y();

    if(TTF_SizeText(this->f, this->cstr, &this->frect.w, &this->frect.h)) {
        return false;
    }

    //this->frect.w = (this->fsize * strlen(this->cstr)); this->frect.h = TTF_FontHeight(this->f);

}

bool font::Draw(SDL_Renderer *srend) {
    SDL_Color c;
    c.r = this->R(); c.g = this->G(); c.b = this->B(); c.a = this->A();

    if(this->cstr == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No string set");
        return false;
    }

    /* generate texture to be plotted */
    if(this->fsurf == nullptr || this->ftext == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Font not prepared");
        return false;
    }
    SDL_RenderCopy(srend, this->ftext, NULL, &this->frect);

    return true;
}
