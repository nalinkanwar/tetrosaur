#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>
#include "SDL.h"
#include "color.h"
#include "twod.h"

#define SCALING_UNIT 40

class Drawable: public twoD, public color
{
    private:
        /* maybe SDL_* objects will come here */
    public:
        Drawable();
        Drawable(twoD &);
        Drawable(twoD &, color &);
        Drawable(int tx, int ty);

        bool setPos(twoD &);
        bool Draw(SDL_Renderer *rend);
};

#endif // DRAWABLE_H
