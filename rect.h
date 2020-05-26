#ifndef RECT_H
#define RECT_H

#include "SDL.h"
#include "drawable.h"

class Rect: public Drawable
{
    private:
        int w,h;
        bool movestate = false;
    public:
        Rect();
        Rect(int tx, int ty, int tw, int th);
        Rect(twoD& td, int tw, int th);
        Rect(const Rect &tr);
        Rect& operator=(const Rect&);

        int getWidth() const;
        int getHeight() const;
        bool Draw(SDL_Renderer *rend);
        void resetPos();
        void setSize(int tw, int th);

        void setColor(color& c);
        void setColor(uint8_t tr, uint8_t tg, uint8_t tb, uint8_t ta);

        void move(int tx, int ty);
        void setMovable();
        void resetMovable();
        bool isMovable() const;
};

#endif // RECT_H
