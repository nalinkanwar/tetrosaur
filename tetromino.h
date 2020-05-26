#ifndef TETROMINO_H
#define TETROMINO_H

#include "rect.h"


enum tetro_types {
    TETROMINO_NONE,
    TETROMINO_I,
    TETROMINO_O,
    TETROMINO_T,
    TETROMINO_S,
    TETROMINO_Z,
    TETROMINO_J,
    TETROMINO_L,
    TETROMINO_MAX,
};
extern uint8_t tetrominos[TETROMINO_MAX][4][2];
extern uint8_t tcolordata[TETROMINO_MAX][4];

class Gameboard;

class Tetromino
{
    private:
        std::vector<Rect> rlist;
        color c;
        tetro_types t;
    public:
        Tetromino();
        ~Tetromino();

        Tetromino(tetro_types tt);
        Tetromino(tetro_types tt, twoD& td);
        Tetromino(std::vector<Rect> &rv, tetro_types tt);

        bool rotate(Gameboard &gb, int direction);
        bool move(Gameboard &gb, int tx, int ty);
        void setType(tetro_types t);
        void setColor(color& tc);
        void spawn(twoD& td);
        void setPos(std::vector<Rect> &rv);
        bool checkPos(Gameboard &gb, int tx, int ty);
        void Draw(SDL_Renderer *rend, Gameboard &gb);
};

#endif // TETROMINO_H
