#ifndef COLOR_H
#define COLOR_H

#include "stdint.h"

class color
{
    private:
        int c[4]; //r,g,b,a
    public:
        color();
        color(const color &c);
        color(uint8_t tr, uint8_t tg, uint8_t tb, uint8_t ta);

        /* Setters */
        color& operator=(color &c);
        void setColor(uint8_t tr, uint8_t tg, uint8_t tb, uint8_t ta);
        void setColor(color &tc);

        /* Getters */
        uint8_t R() const;
        uint8_t G() const;
        uint8_t B() const;
        uint8_t A() const;
};

#endif // COLOR_H
