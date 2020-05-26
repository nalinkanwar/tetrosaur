#include <iostream>
#include "SDL.h"
#include "SDL/SDL_timer.h"
#include "SDL/SDL_ttf.h"
#include "gameboard.h"
#include "tetromino.h"
#include "font.h"
#include "numberbag.h"

#define MAX_X ((SCALING_UNIT * 10) + (SCALING_UNIT * 5))
#define MAX_Y ((SCALING_UNIT * 22) + (SCALING_UNIT))
#define DROP_INTERVAL 1000

uint8_t tetrominos[TETROMINO_MAX][4][2] = {
    {{0,0},{0,0},{0,0},{0,0}}, //NONE
    {{0,0},{1,0},{2,0},{3,0}}, //I
    {{0,0},{0,1},{1,0},{1,1}}, //O
    {{0,0},{1,0},{2,0},{1,1}}, //T
    {{0,1},{1,1},{1,0},{2,0}}, //S
    {{0,0},{1,0},{1,1},{2,1}}, //Z
    {{0,0},{1,0},{1,1},{2,1}}, //J
    {{0,0},{1,0},{0,1},{2,0}}, //L
};

uint8_t tpivotdata[TETROMINO_MAX] = {
    0,     //NONE
    1,     // I
    1,     // O
    1,     // T
    1,     // S
    2,     // Z
    2,     // J
    1,     // L
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

int initSystems(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) != 0) {
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

    if(TTF_Init() == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to init TTF library: %s!", TTF_GetError());
        return 4;
    }

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
    return 0;
}

bool spawnNewTetromino(Gameboard &gb, Tetromino **pt, int type, int x, int y) {
    twoD td(x,y);

    if(*pt != nullptr) {
        delete *pt;
    }
    td.setXY(3, 1);
    *pt = new Tetromino(static_cast<tetro_types>(type));
    if(*pt == nullptr)
        return false;

    return((*pt)->spawn(gb, td));
}

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

int main(int argc, char *argv[])
{
    bool quit = false, gameover = false;
    int retval = 0;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Surface *surface = nullptr;
    Tetromino *pt = nullptr, *gt = nullptr;
    color c(255,255,255,255);
    Gameboard gb;
    font fs_title;
    NumberBag tetrobag(TETROMINO_NONE + 1, TETROMINO_MAX - 1);
    long base_timer, drop_timer, framerate;

    if((retval = initSystems(&window, &renderer)) != 0) {
        return retval;
    }

    srand (time(NULL));

    if((fs_title.load("FreeSans.ttf", 42)) == false) {
        return 5;
    }
    fs_title.setText("Tetrosaur");
    fs_title.setColor(0,150,0, 255);
    fs_title.setXY(GB_MAX_X * SCALING_UNIT + 10,10);
    fs_title.prepare(renderer);

    /* spawn the first one */
    spawnNewTetromino(gb, &pt, tetrobag.getNumber(), 3, 1);

    /* Timers */
    base_timer = drop_timer = SDL_GetTicks();

    /* Main game loop */
    while (!quit) {

        SDL_Event event;
        memset(&event, 0, sizeof(SDL_Event));
        while (SDL_PollEvent(&event)) {
            switch(event.type) {                
                case SDL_WINDOWEVENT:
                {
                    if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
                        SDL_Log("Window %d closed", event.window.windowID);
                        quit = true;
                    }
                    break;
                }
                break;
                case SDL_KEYUP: {
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_LEFT:
                        case SDLK_RIGHT:
                        case SDLK_DOWN:
                        case SDLK_SPACE:
                        case SDLK_LSHIFT:
                        case SDLK_UP:
                        case SDLK_RSHIFT:
                            break;
                    }
                }
                break;
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
                            if(pt->move(gb, TETRO_DOWN) == false) {
                                if(spawnNewTetromino(gb, &pt, tetrobag.getNumber(), 3, 1) == false) {
                                    gameover = true;
                                }
                            }
                            break;
                        case SDLK_SPACE:
                            while(pt->move(gb, TETRO_DOWN) != false);
                            if(spawnNewTetromino(gb, &pt, tetrobag.getNumber(), 3, 1) == false) {
                                gameover = true;
                            }
                            break;
                        case SDLK_LSHIFT:
                            pt->rotate(gb, TETRO_ROL);
                            break;
                        case SDLK_UP:
                        case SDLK_RSHIFT:
                            pt->rotate(gb, TETRO_ROR);
                            break;
                    }
                }
                break;
            }
        }

        // Apply Gravity every 500 ms & Generate a new tetromino if old one gets put on gameboard
        drop_timer = SDL_GetTicks();
        if((drop_timer - base_timer) > DROP_INTERVAL) {
            if(pt->move(gb, TETRO_DOWN) == false) {
                if(spawnNewTetromino(gb, &pt, tetrobag.getNumber(), 3, 1) == false) {
                    gameover = true;
                }
            }
            base_timer = drop_timer;
        }

        /* Draw stuff and present it to the screen */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Draw the player controlled tetromino; if false, gameboard is full
        pt->Draw(renderer, gb);
        gb.Draw(renderer);      //Draw the gameboard

        fs_title.Draw(renderer);

        SDL_RenderPresent(renderer);

        SDL_Log("===================");
        SDL_Delay(10);

        if(gameover == true) {
            break;
        }
    }

    SDL_Quit();
    TTF_Quit();
    return 0;
}
