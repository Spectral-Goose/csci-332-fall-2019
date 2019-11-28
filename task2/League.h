#ifndef _SDL2_Header
#define _SDL2_Header
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#ifndef _Color_Def
#define _Color_Def
SDL_Color Red = {255, 0, 0};
SDL_Color Black = {0, 0, 0};
SDL_Color White = {0xff, 0xff, 0xff};
#endif

#ifndef _League_Constant
#define _League_Constant

enum align
{
    alignLeft,
    alignCenter,
    alignRight
};

enum ActionType
{
    Hit,
    Move,
    Pickup,
    QuitGame,
    Update,
    None
};
#endif
