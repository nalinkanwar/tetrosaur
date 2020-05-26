#include "drawable.h"
#include "color.h"

Drawable::Drawable(): color(), twoD() { }

Drawable::Drawable(twoD &td) : color(), twoD(td) { }
Drawable::Drawable(int tx, int ty) : color(), twoD(tx, ty) { }

Drawable::Drawable(twoD &td, color &tc) : color(tc), twoD(td) { }

bool Drawable::setPos(twoD &td)
{
    this->setXY(td.X(),td.Y());
}

bool Drawable::Draw(SDL_Renderer *rend) {}
