#include "SDL.h"
#include "color.h"

color::color()
{
    this->setColor(0,0,0,0);
}

color::color(const color &c)
{
    this->setColor(c.c[0],c.c[1],c.c[2],c.c[3]);
}

color& color::operator=(color &c)
{
    this->setColor(c.c[0],c.c[1],c.c[2],c.c[3]);
}

color::color(uint8_t tr, uint8_t tg, uint8_t tb, uint8_t ta)
{
    this->setColor(tr,tg,tb,ta);
}

void color::setColor(uint8_t tr, uint8_t tg, uint8_t tb, uint8_t ta)
{
    this->c[0] = tr;
    this->c[1] = tg;
    this->c[2] = tb;
    this->c[3] = ta;
    //SDL_Log("SETTING color %d,%d,%d,%d \n", c[0], c[1], c[2], c[3]);
}


void color::setColor(color &tc)
{
    this->c[0] = tc.R();
    this->c[1] = tc.G();
    this->c[2] = tc.B();
    this->c[3] = tc.A();
    //SDL_Log("SETTING color %d,%d,%d,%d \n", c[0], c[1], c[2], c[3]);
}

uint8_t color::R() const
{
    return this->c[0];
}
uint8_t color::G() const
{
    return this->c[1];
}
uint8_t color::B() const
{
    return this->c[2];
}
uint8_t color::A() const
{
    return this->c[3];
}
