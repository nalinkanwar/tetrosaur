#include "font.h"

Font::Font(const char* path, int size) {
    this->load(path, size);
}

bool Font::load(const char* path, int size) {

    this->f = TTF_OpenFont(path, size);
    if(this->f == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to init TTF library: %s!", TTF_GetError());
        return false;
    }
    this->fsize = size;

    return true;
}

TTF_Font* Font::getFont() {
    return this->f;
}

bool Font::isLoaded() {
    return (this->f != NULL);
}
