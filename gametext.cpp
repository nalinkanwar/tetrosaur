#include "gametext.h"

GameText::GameText() { }

GameText::GameText(Font *f) {
    this->f = f;
}

GameText::~GameText() {
    this->f = nullptr;

    if(this->fsurf != nullptr)
        SDL_FreeSurface(this->fsurf);

    if(this->ftext != nullptr)
        SDL_DestroyTexture(this->ftext);

}

void GameText::setFont(Font *f) {
    this->f = f;
}

bool GameText::setText(const char* tcstr) {

    this->gstr = tcstr;
    this->dirty = true;
    return true;
}

bool GameText::setText(std::string cstr) {

    this->gstr = cstr;
    this->dirty = true;
    return true;
}

bool GameText::prepare(SDL_Renderer *srend) {

    SDL_Color c;
    c.r = this->R(); c.g = this->G(); c.b = this->B(); c.a = this->A();

    /* we already prepared this string once; dont need to do it again */
    if(this->dirty == false) {
        return true;
    }

    if(this->f == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No Font set");
        return false;
    }

    if(this->gstr.empty()) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No string set");
        return false;
    }

    /* generate texture to be plotted */
    this->fsurf = TTF_RenderText_Blended(this->f->getFont(), this->gstr.c_str(), c);
    this->ftext = SDL_CreateTextureFromSurface(srend, this->fsurf);

    if(this->fsurf == nullptr || this->ftext == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Error in text");
        return false;
    }

    this->frect.x = this->X(); this->frect.y = this->Y();

    if(TTF_SizeText(this->f->getFont(), this->gstr.c_str(), &this->frect.w, &this->frect.h)) {
        return false;
    }

    this->dirty = false;
    //this->frect.w = (this->fsize * strlen(this->cstr)); this->frect.h = TTF_FontHeight(this->f);

}

bool GameText::Draw(SDL_Renderer *srend) {
    SDL_Color c;
    c.r = this->R(); c.g = this->G(); c.b = this->B(); c.a = this->A();

    if(this->gstr.empty()) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "No string set");
        return false;
    }

    /* generate texture to be plotted */
    if(this->fsurf == nullptr || this->ftext == nullptr) {
//        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Font not prepared");
//        return false;
        // If font was not prepared, prepare it first
        if(this->prepare(srend) == false) {
            return false;
        }
    }

    SDL_RenderCopy(srend, this->ftext, NULL, &this->frect);

    return true;
}
