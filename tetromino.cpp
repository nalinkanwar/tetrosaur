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
    SDL_Log("SPAWNT Tetromino %d\n", tt);

}

Tetromino::Tetromino(tetro_types tt, twoD& td)
{
    this->rlist.clear();
    this->setType(tt);
    this->spawn(td);
    SDL_Log("SPAWNT Tetromino %d at %d, %d\n", tt, td.X(), td.Y());
}

void Tetromino::setColor(color &tc)
{
    this->c = tc;
}

void Tetromino::setType(tetro_types tt)
{
    this->t = tt;
    this->c.setColor(tcolordata[this->t][0], tcolordata[this->t][1], tcolordata[this->t][2], tcolordata[this->t][3]);
    SDL_Log("Setting tetromino color to %d,%d,%d,%d \n", this->c.R(), this->c.G(), this->c.B(), this->c.A());
}

void Tetromino::spawn(twoD& td) {

    int i = 0;

    while(i != 4) {
        Rect r((td.X() + tetrominos[this->t][i][0]), (td.Y() + tetrominos[this->t][i][1]), SCALING_UNIT, SCALING_UNIT);
        SDL_Log("Spawn x,y = %d, %d\n", r.X(), r.Y());
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

        //SDL_Log("Spawn x,y = %d, %d\n", (*rit).X(), (*rit).Y());

        gb.setRect((*rit).X(), (*rit).Y(),this->c, true);
        rit++;
    }
}
