#include <iostream>
#include "SDL.h"
#include "gameboard.h"
#include "tetromino.h"

#define MAX_X ((SCALING_UNIT * 10) + (SCALING_UNIT / 10) )
#define MAX_Y ((SCALING_UNIT * 22) + (SCALING_UNIT / 10) )

uint8_t tetrominos[TETROMINO_MAX][4][2] = {
    {{0,0},{0,0},{0,0},{0,0}}, //NONE
    {{0,0},{1,0},{2,0},{3,0}}, //I
    {{0,0},{0,1},{1,0},{1,1}}, //O
    {{0,0},{1,0},{2,0},{1,1}}, //T
    {{0,1},{1,1},{1,0},{2,0}}, //S
    {{0,0},{1,0},{1,1},{2,1}}, //Z
    {{0,0},{1,0},{2,0},{2,1}}, //J
    {{0,0},{0,1},{1,0},{2,0}}, //L
};

uint8_t tcolordata[TETROMINO_MAX][4] = {
    {   0,  0,  0,  255}, //NONE
    {   0,255,255,  255}, //I
    { 255,255,  0,  255}, //O
    { 128,  0,128,  255}, //T
    {   0,255,  0,  255}, //S
    { 255,  0,  0,  255}, //Z
    {   0,  0,255,  255}, //J
    { 255,165,  0,  255}, //L
};



int main(int argc, char *argv[])
{
    bool quit = false;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Surface *surface = nullptr;
    Tetromino *t[TETROMINO_MAX] = {nullptr};
    twoD td(0,0), tro(2,2);
    color c(255,255,255,255);
    Gameboard gb(td);

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if ((window = SDL_CreateWindow("Tetrosaur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAX_X, MAX_Y, SDL_WINDOW_RESIZABLE)) == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        return 2;
    }

    if((renderer = SDL_CreateRenderer(window,  -1, SDL_RENDERER_ACCELERATED)) == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
        return 3;
    }

    srand (time(NULL));

//    for(int i = TETROMINO_NONE; i < TETROMINO_MAX; ++i) {
//        td.setXY(4, 1);
//        t[i] = new Tetromino(static_cast<tetro_types>(i), td);
//    }

    td.setXY(1, 1);
    t[TETROMINO_S] = new Tetromino(TETROMINO_S, td);

    while (!quit) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    {
                        switch(event.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                quit = true;
                                break;

                        }
                    }
                    break;
            }
        }

        /* Draw stuff and present it to the screen */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //DRAW STUFF HERE
        color tc(255,0,255,255);
        //gb.setRect(5,10, tc);

//        for(int i = TETROMINO_NONE; i < TETROMINO_MAX; ++i) {
//            td.setXY(1, i * 2);
//            t = new Tetromino(static_cast<tetro_types>(i), td);
//            t->Draw(renderer, gb);
//        }
        //t[TETROMINO_S]->move(gb, 0, 1);
        t[TETROMINO_S]->Draw(renderer, gb);

        gb.Draw(renderer);

        SDL_RenderPresent(renderer);

        SDL_Log("===================");
        SDL_Delay(500);
    }

    SDL_Quit();
    return 0;
}
