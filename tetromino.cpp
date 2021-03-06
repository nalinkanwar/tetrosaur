#include "rect.h"
#include "tetromino.h"
#include "gameboard.h"

/* Ctors/Dtors */

Tetromino::Tetromino()
{
    this->rlist.clear();
    this->t = TETROMINO_NONE;
}

Tetromino::~Tetromino()
{
    this->rlist.clear();
}


Tetromino::Tetromino(const Tetromino &ct)
{
    auto rit = ct.rlist.begin();
    color col(ct.c.R(), ct.c.G(), ct.c.B(), ct.c.A());

    this->rlist.clear();
    while(rit != ct.rlist.end()) {
        Rect r;
        twoD td((*rit).X(), (*rit).Y());

        r.setPos(td);
        r.setColor(col);
        r.setSize((*rit).getWidth(), (*rit).getHeight());
        r.resetMovable();
        this->rlist.push_back(r);
        rit++;
    }

    this->t = ct.t;

    this->setColor(col);
}

Tetromino::Tetromino(tetro_types tt)
{
    this->rlist.clear();
    this->setType(tt);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "SPAWNT Tetromino %d\n", tt);

}

Tetromino::Tetromino(tetro_types tt, Gameboard &gb, twoD& td)
{
    this->rlist.clear();
    this->setType(tt);
    this->spawn(gb, td);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "SPAWNT Tetromino %d at %d, %d\n", tt, td.X(), td.Y());
}

/* Methods */

void Tetromino::setColor(color &tc)
{
    this->c = tc;
}

void Tetromino::setType(tetro_types tt)
{
    this->t = tt;
    this->c.setColor(tcolordata[this->t][0], tcolordata[this->t][1], tcolordata[this->t][2], tcolordata[this->t][3]);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Setting tetromino color to %d,%d,%d,%d \n", this->c.R(), this->c.G(), this->c.B(), this->c.A());
}

bool Tetromino::spawn(Gameboard &gb, twoD& td) {

    int i = 0;

    if(this->t == TETROMINO_NONE || this->t == TETROMINO_MAX) {
        return false;
    }

    while(i != 4) {
        Rect r((td.X() + tetrominos[this->t][i][0]), (td.Y() + tetrominos[this->t][i][1]), SCALING_UNIT, SCALING_UNIT);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Spawn [%d]block x,y = %d, %d\n", i, r.X(), r.Y());
        r.setMovable();
        r.setColor(tcolordata[this->t][0], tcolordata[this->t][1], tcolordata[this->t][2], tcolordata[this->t][3]);

        this->rlist.push_back(r);
        i++;
    }
    if(this->checkPos(gb, 0, 0) == false) {
        return false;
    }
    return true;
}

void Tetromino::Draw(SDL_Renderer *rend, Gameboard &gb)
{
    auto rit = this->rlist.begin();
    int y = 1;

    /* here X,Y points to gameboard x,y values */
    while(rit != this->rlist.end()) {

        //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Spawn x,y = %d, %d\n", (*rit).X(), (*rit).Y());
        gb.setRect((*rit).X(), (*rit).Y(),this->c, true);
        rit++;
    }

    /* Draw ghost tetromino on gameboard */
    if(this->hasGhost == false) {
        while(this->checkPos(gb, 0, y) != false) y++;
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Calculated %d\n", y);

        if(y > 2 && y < GB_MAX_Y) {
            twoD ttd(0, y-1);
            this->ghost.setPos(ttd);

            rit = this->rlist.begin();
            while(rit != this->rlist.end()) {
                gb.setGhostRect((*rit).X(), (*rit).Y() + y - 1);
                rit++;
            }
            this->hasGhost = true;
        }
    }
}


bool Tetromino::checkPos(Gameboard &gb, int tx, int ty) {

    auto rit = this->rlist.begin();
    /* check if we can actually move to that place */
    while(rit != this->rlist.end()) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "CHECKING x,y = %d, %d\n", (*rit).X() + tx, (*rit).Y() + ty);

        if(gb.checkRect((*rit).X() + tx, (*rit).Y() + ty) == false) {
            return false;
        }
        rit++;
    }
    return true;
}

bool Tetromino::put(Gameboard &gb)
{
    auto rit = this->rlist.begin();
    while(rit != this->rlist.end()) {
        (*rit).resetMovable();        
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Putting tetromino %x,%y\n", (*rit).X(), (*rit).Y());
        gb.setRect((*rit).X(), (*rit).Y(), this->c, false);        
        rit++;
    }
    gb.checkLines();
    return true;
}

bool Tetromino::rotate(Gameboard &gb, tetro_direction ttd)
{
    auto rit = this->rlist.begin();
    int x[4], y[4], ctr = 0, xoffset = 0;
    int pivotx = 0, pivoty = 0;

    if(this->rlist.empty()) {
        return false;
    }

    pivotx = this->rlist[tpivotdata[this->t]].X();
    pivoty = this->rlist[tpivotdata[this->t]].Y();

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Pivoting tetromino around %d,%d\n", pivotx, pivoty);
    while(rit != this->rlist.end())
    {
        switch(ttd) {
            case TETRO_ROL:
                x[ctr] = pivotx + (pivoty - (*rit).Y()) + xoffset;
                y[ctr] = pivoty - (pivotx - (*rit).X());
            break;
            case TETRO_ROR:
                x[ctr] = pivotx - (pivoty - (*rit).Y()) + xoffset;
                y[ctr] = pivoty + (pivotx - (*rit).X());
            break;
        }

        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Rotating tetromino from %d,%d\n", (*rit).X(), (*rit).Y());

        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Rotating tetromino to [%d]%d,%d\n", ctr, x[ctr], y[ctr]);

        if(gb.checkRect(x[ctr], y[ctr]) == false) {
            /* simple wallkick algo; try one space left & one space right if still fail, then actually fail */
            if(xoffset == 0) {
                xoffset = 1;
            } else if (xoffset == 1) {
                xoffset = -1;
            } else {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Rotating tetromino fail\n");
                return false;
            }
            ctr = 0;
            rit = this->rlist.begin();

            pivotx = this->rlist[tpivotdata[this->t]].X() + xoffset;
            pivoty = this->rlist[tpivotdata[this->t]].Y();
        } else {
            ctr++;
            rit++;
        }
    }

    rit = this->rlist.begin();
    ctr = 0;

    this->clearPos(gb);

    while(rit != this->rlist.end()) {
        if(gb.resetRect((*rit).X(), (*rit).Y()) == false) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "impossible happened!\n");
            return false;
        }
        (*rit).setXY(x[ctr], y[ctr]);
        ctr++;
        rit++;
    }
    return true;
}

tetro_types Tetromino::getType() const {
    return this->t;
}

bool Tetromino::move(Gameboard &gb, tetro_direction ttd)
{
    auto rit = this->rlist.begin();
    int xoff = 0, yoff = 0;

    switch(ttd) {
        case TETRO_DOWN:
            yoff = 1;
            break;
        case TETRO_LEFT:
            xoff = -1;
            break;
        case TETRO_RIGHT:
            xoff = 1;
            break;
        case TETRO_ROL:
        case TETRO_ROR:
            //TODO: maybe separate rotate() for these two ?
            break;
        default:
            break;
    }


    /* check if xoff, yoff offset is movable on gameboard */
    if(this->checkPos(gb, xoff, yoff) == false) {
        switch(ttd) {
            case TETRO_DOWN:
                /* if we can't move down, that means that
                 * we need to fix the tetromino
                 * (and destroy ourselves?)
                 */
                this->put(gb);
                break;
            case TETRO_LEFT:
            case TETRO_RIGHT:
            case TETRO_ROL:
            case TETRO_ROR:
                /* TODO wallkicks here? */
            default:
                break;
        }
        return false;
    }

    this->clearPos(gb);

    /* create new */
    rit = this->rlist.begin();
    while(rit != this->rlist.end()) {
        (*rit).setXY((*rit).X() + xoff, (*rit).Y() + yoff);
        rit++;
    }
    return true;
}

void Tetromino::clearPos(Gameboard &gb)
{
    /* clean old footprint on gameboard */
    auto rit = this->rlist.begin();
    while(rit != this->rlist.end()) {
        /* clean original piece */
        gb.resetRect((*rit).X(), (*rit).Y());

        /* clean ghost piece */
        if(this->hasGhost == true)
            gb.resetRect((*rit).X() + this->ghost.X(), (*rit).Y() + this->ghost.Y());
        rit++;
    }
    this->hasGhost = false;
}
