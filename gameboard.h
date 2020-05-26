#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <array>
#include "SDL.h"
#include "rect.h"

#define GB_MAX_X 10
#define GB_MAX_Y 22

class Gameboard
{
    private:
        std::array<std::array<Rect,GB_MAX_X>, GB_MAX_Y> gb;
        twoD offset;
    public:
        Gameboard();
        Gameboard(twoD &toff);

        void setOffset(twoD &toff);
        void setRectOffset(twoD &toff);

        bool setRect(int gb_x, int gb_y, color & tc, bool movable);
        bool setGhostRect(int gb_x, int gb_y);
        bool resetRect(int gb_x, int gb_y);
        bool checkRect(int gb_x, int gb_y);

        bool checkLines();
        void applyGravity(int line);

        bool Draw(SDL_Renderer *srend);        
        void Reset();

};

#endif // GAMEBOARD_H
