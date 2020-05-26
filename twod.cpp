#include "twod.h"

twoD::twoD():x(0), y(0) {}
twoD::twoD(int xparam, int yparam) : x(xparam), y(yparam) {}

twoD::twoD(const twoD& td)
{
    this->x = td.x;
    this->y = td.y;
}

twoD& twoD::operator=(twoD& td)
{
    this->x = td.x;
    this->y = td.y;
    return *this;
}

void twoD::setX(int tx) { this->x = tx; }
void twoD::setY(int ty) { this->y = ty; }
void twoD::setXY(int tx, int ty) { this->x = tx; this->y = ty; }

int twoD::X() const {return this->x;}
int twoD::Y() const {return this->y;}
