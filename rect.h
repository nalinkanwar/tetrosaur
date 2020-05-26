#ifndef RECT_H
#define RECT_H

#include "SDL.h"
#include "drawable.h"

enum rect_types {
    RECT_NORMAL = 0,
    RECT_FILLED,
    RECT_GHOST
};

class Rect: public Drawable
{
    private:
        rect_types type = RECT_NORMAL;
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
        color& getColor();
        void setType(rect_types rt);
        rect_types getType() const;

        void move(int tx, int ty);
        void setMovable();
        void resetMovable();
        bool isMovable() const;
        bool isFilled() const;
};

#endif // RECT_H
