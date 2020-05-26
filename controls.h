#ifndef CONTROLS_H
#define CONTROLS_H

#include "SDL.h"
#include <array>

enum control_types {
    GAMEKEY_UP,
    GAMEKEY_DOWN,
    GAMEKEY_LEFT,
    GAMEKEY_RIGHT,
    GAMEKEY_LSHIFT,
    GAMEKEY_RSHIFT,
    GAMEKEY_SPACE,
    GAMEKEY_MAX
};


class controls
{
    private:
        std::array<bool, GAMEKEY_MAX> keys;
    public:
        controls();

        void handleEvent(SDL_Event &event);
};

#endif // CONTROLS_H
