#include "rect.h"

Rect::Rect(): Drawable(), w(0), h(0) { }
Rect::Rect(int tx, int ty, int tw, int th): w(tw),h(th), Drawable(tx,ty) { }
Rect::Rect(twoD& td, int tw, int th): w(tw), h(th), Drawable(td) { }

Rect::Rect(const Rect &tr)
{
    //SDL_Log("copy ctor called\n");
    this->setXY(tr.X(), tr.Y());
    this->w = tr.w;
    this->h = tr.h;
    this->setColor(tr.R(), tr.G(), tr.B(), tr.A());
    this->movestate = tr.isMovable();
}

Rect& Rect::operator=(const Rect& tr)
{
//    this->setXY(tr.X(), tr.Y());
//    this->w = tr.w;
//    this->h = tr.h;
//    this->setColor(tr.R(), tr.G(), tr.B(), tr.A());
//    this->movestate = tr.isMovable();
    return (*this);
}

void Rect::move(int tx, int ty)
{
    if(this->isMovable() == true) {
        this->setXY(this->X() + tx, this->Y() + ty);
    }
}

void Rect::setColor(uint8_t tr, uint8_t tg, uint8_t tb, uint8_t ta)
{
    this->color::setColor(tr, tg, tb, ta);
}

void Rect::setColor(color& c)
{
    this->color::setColor(c);
}

void Rect::resetPos()
{
    this->setXY(0,0);
}

int Rect::getWidth() const
{
    return this->w;
}

int Rect::getHeight() const
{
    return this->h;
}

void Rect::setSize(int tw, int th)
{
    this->w = tw;
    this->h = th;
}

void Rect::setMovable()
{
    this->movestate = true;
}

void Rect::resetMovable()
{
    this->movestate = false;
}


bool Rect::isMovable() const
{
    return this->movestate;
}

bool Rect::Draw(SDL_Renderer *rend)
{
    SDL_Rect rect, srect;

    //SDL_Log("Drawing at %d,%d\n", this->X(), this->Y());
    /* draw board boxes */
//    srect = rect;
//    srect.x = this->X() + (SCALING_UNIT/10);
//    srect.y = this->Y() + (SCALING_UNIT/10);
//    srect.w = SCALING_UNIT - (SCALING_UNIT/10);
//    srect.h = SCALING_UNIT - (SCALING_UNIT/10);
//    SDL_SetRenderDrawColor(rend, 55,55,55,255);
//    SDL_RenderFillRect(rend, &srect);

    srect.x = this->X() + SCALING_UNIT;
    srect.y = this->Y() + SCALING_UNIT;
    srect.w = (SCALING_UNIT/10);
    srect.h = (SCALING_UNIT/10);
    SDL_SetRenderDrawColor(rend, 55,55,55,255);
    SDL_RenderFillRect(rend, &srect);

    /* now draw the actual rects */
    rect.x = this->X() + (SCALING_UNIT/10);
    rect.y = this->Y() + (SCALING_UNIT/10);
    if(this->w == 0 && this->h == 0) {
        return false;
    }
    rect.w = this->w - (SCALING_UNIT/10);
    rect.h = this->h - (SCALING_UNIT/10);

    SDL_SetRenderDrawColor(rend, this->R(), this->G(), this->B(), this->A());
    SDL_RenderFillRect(rend, &rect);

    return true;    
}
