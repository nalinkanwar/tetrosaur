#include <vector>
#include "gameboard.h"

Gameboard::Gameboard()
{    
    this->Reset();
}

Gameboard::Gameboard(twoD &toff)
{
    this->offset = toff;
    SDL_Log("setting offset %d,%d\n", toff.X(), toff.Y());
    this->Reset();
}

void Gameboard::setOffset(twoD &toff)
{
    this->offset = toff;
    SDL_Log("setting offset %d,%d\n", toff.X(), toff.Y());
}

void Gameboard::Reset()
{
    for(auto yit = this->gb.begin(); yit != this->gb.end(); yit++) {
        for(auto xit = yit->begin(); xit != yit->end(); xit++) {
            int xpos = (xit - yit->begin()) * SCALING_UNIT;
            int ypos = (yit - this->gb.begin()) * SCALING_UNIT;

            twoD t(xpos + this->offset.X(), ypos + this->offset.Y());
            SDL_Log("setting pos (%d,%d)\n", t.X(), t.Y());
            (*xit).setPos(t);
            (*xit).setSize(0, 0);
            (*xit).setColor(255,255,255,255);
        }
    }
    SDL_Log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`Done Resetting~~~~~~~~~~~~~~~~~~~~~~~~~~~``\n");
}

bool Gameboard::checkRect(int gb_x, int gb_y)
{
    if(gb_x < 0 && gb_x >= GB_MAX_X) {
        return false;
    }
    if(gb_y < 0 && gb_y >= GB_MAX_Y) {
        return false;
    }
    Rect &tr = this->gb[gb_y][gb_x];

    if(tr.isMovable() == false && tr.getHeight() == SCALING_UNIT) {
        return false;
    }
    return true;
}

bool Gameboard::resetRect(int gb_x, int gb_y)
{
    if(gb_x < 0 || gb_x >= GB_MAX_X) {
        SDL_Log("overshooting X %d >= %d\n", gb_x, GB_MAX_X);
        return false;
    }
    if(gb_y < 0 || gb_y >= GB_MAX_Y) {
        SDL_Log("overshooting Y %d >= %d\n", gb_y, GB_MAX_Y);
        return false;
    }

    Rect &tr = this->gb[gb_y][gb_x];
    SDL_Log("Setting GB %d,%d\n", gb_x, gb_y);
    SDL_Log("Setting    %d,%d\n", tr.X(), tr.Y());

    tr.color::setColor(255,255,255,255);
    tr.setSize(0,0);
    return true;
}

bool Gameboard::setRect(int gb_x, int gb_y, color & tc, bool movable)
{
    if(gb_x < 0 || gb_x >= GB_MAX_X) {
        SDL_Log("overshooting X %d >= %d\n", gb_x, GB_MAX_X);
        return false;
    }
    if(gb_y < 0 || gb_y >= GB_MAX_Y) {
        SDL_Log("overshooting Y %d >= %d\n", gb_y, GB_MAX_Y);
        return false;
    }

    Rect &tr = this->gb[gb_y][gb_x];
    SDL_Log("Setting GB %d,%d\n", gb_x, gb_y);
    SDL_Log("Setting    %d,%d\n", tr.X(), tr.Y());

    tr.color::setColor(tc);
    tr.setSize(SCALING_UNIT, SCALING_UNIT);
    tr.setMovable();

    return true;
}

bool Gameboard::Draw(SDL_Renderer *srend)
{
    if(srend == nullptr) {
        return false;
    }

    for(auto yit = this->gb.begin(); yit != this->gb.end(); yit++) {
        for(auto xit = yit->begin(); xit != yit->end(); xit++) {
            (*xit).Draw(srend);
            if((*xit).isMovable() == true) {
                this->resetRect((*xit).X(), (*xit).Y());
            }
        }
    }
    return true;
}

