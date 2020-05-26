#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <array>
#include "SDL.h"
#include "rect.h"
#include "gametext.h"

#define GB_MAX_X 10
#define GB_MAX_Y 22

enum GB_TEXTS {
    GBT_SCORE=0,
    GBT_LINES,
    GBT_LEVEL
};

class Gameboard
{
    private:
        std::array<std::array<Rect,GB_MAX_X>, GB_MAX_Y> gb;
        twoD offset;
        int score = 0;
        int lines_cleared = 0;
        int level = 0;
        std::vector<GameText> texts;
        //tscore, tlevel, tlines;

        void initText(Font *f);
    public:
        Gameboard(Font *f);
        Gameboard(Font *f, twoD &toff);

        void setOffset(twoD &toff);
        void setRectOffset(twoD &toff);

        bool setRect(int gb_x, int gb_y, color & tc, bool movable);
        bool setGhostRect(int gb_x, int gb_y);
        bool resetRect(int gb_x, int gb_y);
        bool checkRect(int gb_x, int gb_y);

        bool checkLines();
        void applyGravity(int line);

        void prepareText(SDL_Renderer *renderer);
        bool Draw(SDL_Renderer *srend);        
        void Reset();

};

#endif // GAMEBOARD_H
