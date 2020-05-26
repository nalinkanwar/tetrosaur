#include <iostream>
#include "SDL.h"
#include "gameboard.h"
#include "tetromino.h"

#define MAX_X ((SCALING_UNIT * 10) + SCALING_UNIT )
#define MAX_Y ((SCALING_UNIT * 22) + SCALING_UNIT )

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

int initSDL(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if ((*window = SDL_CreateWindow("Tetrosaur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAX_X, MAX_Y, SDL_WINDOW_RESIZABLE)) == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        return 2;
    }

    if((*renderer = SDL_CreateRenderer(*window,  -1, SDL_RENDERER_ACCELERATED)) == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
        return 3;
    }
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
    return 0;
}


int main(int argc, char *argv[])
{
    bool quit = false;
    int retval = 0;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Surface *surface = nullptr;
    Tetromino *pt = nullptr;
    twoD td(0,0), tro(2,2);
    color c(255,255,255,255);
    Gameboard gb(td);


    if((retval = initSDL(&window, &renderer)) != 0) {
        return retval;
    }

    srand (time(NULL));

    /* spawn the first one */
    td.setXY(3, 1);
    pt = new Tetromino(static_cast<tetro_types>((rand() % (TETROMINO_MAX - 1)) + 1), td);

    /* Main game loop */
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
                            case SDLK_LEFT:
                                pt->move(gb, TETRO_LEFT);
                                break;
                            case SDLK_RIGHT:
                                pt->move(gb, TETRO_RIGHT);
                                break;
                            case SDLK_DOWN:
                                pt->move(gb, TETRO_DOWN);
                                break;
                            case SDLK_LSHIFT:
                                pt->move(gb, TETRO_ROL);
                                break;
                            case SDLK_UP:
                            case SDLK_RSHIFT:
                                pt->move(gb, TETRO_ROR);
                                break;
                        }
                    }
                    break;
            }
        }
        // Apply Gravity & Generate a new tetromino if old one gets 'putted'
        if(pt->move(gb, TETRO_DOWN) == false) {
            delete pt;
            td.setXY(3, 1);
            pt = new Tetromino(static_cast<tetro_types>((rand() % (TETROMINO_MAX - 1)) + 1), td);
        }


        /* Draw stuff and present it to the screen */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        pt->Draw(renderer, gb); //Draw the player controlled tetromino
        gb.Draw(renderer);      //Draw the gameboard

        SDL_RenderPresent(renderer);

        SDL_Log("===================");
        SDL_Delay(500);
    }

    SDL_Quit();
    return 0;
}
