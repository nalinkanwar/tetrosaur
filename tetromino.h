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

enum tetro_direction {
    TETRO_DOWN,
    TETRO_LEFT,
    TETRO_RIGHT,
    TETRO_ROL,
    TETRO_ROR
};

extern uint8_t tetrominos[TETROMINO_MAX][4][2];
extern uint8_t tcolordata[TETROMINO_MAX][4];
extern uint8_t tpivotdata[TETROMINO_MAX];

class Gameboard;

class Tetromino
{
    private:
        std::vector<Rect> rlist;
        color c;
        tetro_types t;
        Rect ghost;
        bool hasGhost = false;
    public:
        Tetromino();
        ~Tetromino();

        Tetromino(tetro_types tt);
        Tetromino(tetro_types tt, Gameboard &gb, twoD& td);
        Tetromino(const Tetromino &ct);

        bool put(Gameboard &gb);
        bool rotate(Gameboard &gb, tetro_direction ttd);
        bool move(Gameboard &gb, tetro_direction ttd);

        void setType(tetro_types t);
        void setColor(color& tc);
        bool spawn(Gameboard &gb, twoD& td);
        void setPos(std::vector<Rect> &rv);
        bool checkPos(Gameboard &gb, int tx, int ty);
        void clearPos(Gameboard &gb);
        void clearGhostPos(Gameboard &gb);

        void Draw(SDL_Renderer *rend, Gameboard &gb);

        tetro_types getType() const;
};

#endif // TETROMINO_H
