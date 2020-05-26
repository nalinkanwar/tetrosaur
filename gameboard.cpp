#include <vector>
#include "gameboard.h"

Gameboard::Gameboard()
{    
    this->Reset();
}

Gameboard::Gameboard(twoD &toff)
{
    this->offset = toff;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "setting offset %d,%d\n", toff.X(), toff.Y());
    this->Reset();
}

void Gameboard::setOffset(twoD &toff)
{
    this->offset = toff;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "setting offset %d,%d\n", toff.X(), toff.Y());
}

void Gameboard::Reset()
{
    for(auto yit = this->gb.begin(); yit != this->gb.end(); yit++) {
        for(auto xit = yit->begin(); xit != yit->end(); xit++) {
            int xpos = (xit - yit->begin()) * SCALING_UNIT;
            int ypos = (yit - this->gb.begin()) * SCALING_UNIT;

            twoD t(xpos + this->offset.X(), ypos + this->offset.Y());
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "setting pos (%d,%d)\n", t.X(), t.Y());
            (*xit).setPos(t);
            (*xit).setSize(0, 0);
            (*xit).setColor(255,255,255,255);
        }
    }
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`Done Resetting~~~~~~~~~~~~~~~~~~~~~~~~~~~``\n");
}

bool Gameboard::checkRect(int gb_x, int gb_y)
{
    if(gb_x < 0 || gb_x >= GB_MAX_X) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "checkRect failed overshooting X %d >= %d\n", gb_x, GB_MAX_X);
        return false;
    }
    if(gb_y < 0 || gb_y >= GB_MAX_Y) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "checkRect failed overshooting Y %d >= %d\n", gb_y, GB_MAX_Y);
        return false;
    }
    Rect &tr = this->gb[gb_y][gb_x];

//    if(tr.isFilled() == true && tr.isMovable() == false) {
    if(tr.getType() == RECT_FILLED && tr.isMovable() == false) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "FILLED\n");
        return false;
    }
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "NOT FILLED\n");
    return true;
}

bool Gameboard::resetRect(int gb_x, int gb_y)
{
    if(gb_x < 0 || gb_x >= GB_MAX_X) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "overshooting X %d >= %d\n", gb_x, GB_MAX_X);
        return false;
    }
    if(gb_y < 0 || gb_y >= GB_MAX_Y) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "overshooting Y %d >= %d\n", gb_y, GB_MAX_Y);
        return false;
    }

    Rect &tr = this->gb[gb_y][gb_x];
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Setting GB %d,%d\n", gb_x, gb_y);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Setting    %d,%d\n", tr.X(), tr.Y());

    tr.color::setColor(255,255,255,255);
    tr.setSize(0,0);
    tr.resetMovable();
    tr.setType(RECT_NORMAL);

    return true;
}

bool Gameboard::setGhostRect(int gb_x, int gb_y)
{
    if(gb_x < 0 || gb_x >= GB_MAX_X) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "overshooting X %d >= %d\n", gb_x, GB_MAX_X);
        return false;
    }
    if(gb_y < 0 || gb_y >= GB_MAX_Y) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "overshooting Y %d >= %d\n", gb_y, GB_MAX_Y);
        return false;
    }

    Rect &tr = this->gb[gb_y][gb_x];
    color col(100,100,100,255);

    tr.setColor(col);
    tr.setSize(SCALING_UNIT/2, SCALING_UNIT/2);
    tr.setType(RECT_GHOST);
    tr.resetMovable();
}

bool Gameboard::setRect(int gb_x, int gb_y, color & tc, bool movable)
{
    if(gb_x < 0 || gb_x >= GB_MAX_X) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "overshooting X %d >= %d\n", gb_x, GB_MAX_X);
        return false;
    }
    if(gb_y < 0 || gb_y >= GB_MAX_Y) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "overshooting Y %d >= %d\n", gb_y, GB_MAX_Y);
        return false;
    }

    Rect &tr = this->gb[gb_y][gb_x];
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Setting GB %d,%d\n", gb_x, gb_y);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Setting    %d,%d\n", tr.X(), tr.Y());

    tr.color::setColor(tc);
    tr.setSize(SCALING_UNIT, SCALING_UNIT);
    tr.setType(RECT_FILLED);
    if(movable == true)
        tr.setMovable();
    else
        tr.resetMovable();

    return true;
}

bool Gameboard::Draw(SDL_Renderer *srend)
{
    if(srend == nullptr) {
        return false;
    }

    /* here X,Y points to pixel values */
    for(auto yit = this->gb.begin(); yit != this->gb.end(); yit++) {
        for(auto xit = yit->begin(); xit != yit->end(); xit++) {
            (*xit).Draw(srend);
            if((*xit).isMovable() == true) {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Drew %d,%d\n", (*xit).X(), (*xit).Y());
            }
        }
    }


    /* Draw Bounding Box */
    SDL_Rect gb_r;
    gb_r.x = this->offset.X();
    gb_r.y = this->offset.Y();
    gb_r.w = GB_MAX_X * SCALING_UNIT + (SCALING_UNIT/10);
    gb_r.h = GB_MAX_Y * SCALING_UNIT + (SCALING_UNIT/10);

    SDL_SetRenderDrawColor(srend, 255,255,255,255);
    SDL_RenderDrawRect(srend, &gb_r);

    return true;
}

/* lines start to end are missing; shift blocks above them to the ground */
void Gameboard::applyGravity(int line)
{
    int x,y;

    for(y = line-1; y > 0; y--) {
        for(x = 0; x < GB_MAX_X; x++) {
            if(this->checkRect(x, y) == false) {
                Rect &rtemp = this->gb[y][x];
                color col(rtemp.R(), rtemp.G(), rtemp.B(), rtemp.A());
                this->setRect(x, y+1, col, false);
                this->resetRect(x,y);
            }
        }
    }
}

bool Gameboard::checkLines()
{
    int x,y, check;
    bool flag = false;

    for(y = 0; y < GB_MAX_Y; y++) {
        check = 0;
        for(x = 0; x < GB_MAX_X; x++) {
            if(this->checkRect(x, y) == false) {
                check++;
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "check %d != %d", check, GB_MAX_X);
            }
        }
        if(check == GB_MAX_X) {
            flag = true;
            //blast this line;
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "BLAST check %d != %d", check, GB_MAX_X);
            for(x = 0; x < GB_MAX_X; x++) {
                this->resetRect(x, y);
            }
            this->applyGravity(y);
        }
    }

    return flag;
}
