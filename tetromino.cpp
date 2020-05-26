#include "rect.h"
#include "tetromino.h"
#include "gameboard.h"

Tetromino::Tetromino()
{
    this->rlist.clear();
    this->t = TETROMINO_NONE;
}

Tetromino::~Tetromino()
{
    this->rlist.clear();
}

Tetromino::Tetromino(tetro_types tt)
{
    this->rlist.clear();
    this->setType(tt);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "SPAWNT Tetromino %d\n", tt);

}

Tetromino::Tetromino(tetro_types tt, twoD& td)
{
    this->rlist.clear();
    this->setType(tt);
    this->spawn(td);
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "SPAWNT Tetromino %d at %d, %d\n", tt, td.X(), td.Y());
}

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

void Tetromino::spawn(twoD& td) {

    int i = 0;

    while(i != 4) {
        Rect r((td.X() + tetrominos[this->t][i][0]), (td.Y() + tetrominos[this->t][i][1]), SCALING_UNIT, SCALING_UNIT);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Spawn x,y = %d, %d\n", r.X(), r.Y());
        r.setMovable();
        r.setColor(tcolordata[this->t][0], tcolordata[this->t][1], tcolordata[this->t][2], tcolordata[this->t][3]);

        this->rlist.push_back(r);
        i++;
    }
}

void Tetromino::Draw(SDL_Renderer *rend, Gameboard &gb)
{
    auto rit = this->rlist.begin();

    /* here X,Y points to gameboard x,y values */
    while(rit != this->rlist.end()) {

        //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG, "Spawn x,y = %d, %d\n", (*rit).X(), (*rit).Y());

        gb.setRect((*rit).X(), (*rit).Y(),this->c, true);
        rit++;
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
    return true;
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
            /* TODO wallkicks here? */
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
        gb.resetRect((*rit).X(), (*rit).Y());
        rit++;
    }
}
