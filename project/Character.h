#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "League.h"

using namespace std;

class character
{
private:
    int name_width = 0;
    int name_height = 0;
    bool moving;
    int dx, dy, sx, sy;
    int err, e2;
    int cx, cy;

public:
    int x, y;
    int mx, my;
    const int width = 70;
    const int height = 70;
    int role;
    char IP[17] = {0};
    SDL_Rect rect;
    int health;
    SDL_Surface *imageSurface;
    SDL_Surface *nameSurface;
    SDL_Rect text_rect; //create a rect
    SDL_Texture *image;
    SDL_Texture *textTexture;
    char name[200] = {0};

    void init(int r, char character_name[], int x, int y, SDL_Renderer *renderer)
    {
        role = r;

        moving = false;
        rect.h = height;
        rect.w = width;
        rect.x = x;
        rect.y = y;
        TTF_Font *Sans = TTF_OpenFont("FreeSans.ttf", 12); //this opens a font style and sets a size
        TTF_SizeText(Sans, name, &name_width, &name_height);
        nameSurface = TTF_RenderText_Blended(Sans, name, Black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
        TTF_CloseFont(Sans);
        text_rect.x = (x + 35) - (name_width / 2); //controls the rect's x coordinate
        text_rect.y = y;                           // controls the rect's y coordinte
        text_rect.w = name_width;                  // controls the width of the rect
        text_rect.h = name_height;                 // controls the height of the rect
        cx = x + width / 2;
        cy = y + height / 2;

        switch (role)
        {
        case 0:
            imageSurface = SDL_LoadBMP("c1.bmp");
            break;
        case 1:
            imageSurface = SDL_LoadBMP("c2.bmp");
            break;
        case 2:
            imageSurface = SDL_LoadBMP("c3.bmp");
            break;
        case 3:
            imageSurface = SDL_LoadBMP("c4.bmp");
            break;
        case 4:
            imageSurface = SDL_LoadBMP("c5.bmp");
            break;
        case 5:
            imageSurface = SDL_LoadBMP("c6.bmp");
            break;
        default:
            imageSurface = SDL_LoadBMP("c6.bmp");
        }
        Uint32 colorkey = SDL_MapRGB(imageSurface->format, 255, 255, 255);
        SDL_SetColorKey(imageSurface, SDL_TRUE, colorkey);

        image = SDL_CreateTextureFromSurface(renderer, imageSurface);
        textTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
        SDL_FreeSurface(imageSurface);
        SDL_FreeSurface(nameSurface);
    }

    //Constructor for other players
    character(SDL_Renderer *renderer, char *IP_address, int CharacterRole, char character_name[], int x, int y, int character_health)
    {
        strcpy(IP, IP_address);
        health = character_health;
        strcpy(name, character_name);
        init(CharacterRole, character_name, x, y, renderer);
    }

    //Constructor for your character
    character(SDL_Renderer *renderer, char *IP_address, int CharacterRole, char character_name[])
    {
        /* generate secret number between 1 and 10: */
        x = rand() % 1024 + 1;
        y = rand() % 768 + 1;
        strcpy(IP, IP_address);
        health = 100;
        strcpy(name, character_name);
        init(CharacterRole, character_name, x, y, renderer);
    }

    ~character()
    {
        SDL_FreeSurface(nameSurface);
        SDL_FreeSurface(imageSurface);
        SDL_DestroyTexture(textTexture);
        SDL_DestroyTexture(image);
    }

    void Update_Location()
    {
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy; /* e_xy+e_x > 0 */
            cx += sx;
        }
        if (e2 <= dx) /* e_xy+e_y < 0 */
        {
            err += dx;
            cy += sy;
        }
        x = cx - width / 2;
        y = cy - height / 2;
    }

    void move(int mousex, int mousey)
    {

        moving = true;
        mx = mousex;
        my = mousey;
        if (cx == mx && cy == my)
        {
            moving = false;
        }
        else
        {
            dx = abs(mx - cx);
            sx = cx < mx ? 1 : -1;
            dy = -abs(my - cy);
            sy = cy < my ? 1 : -1;
            err = dx + dy; /* error value e_xy */
        }
    }

    void update()
    {
        if (moving)
        {
            Update_Location();
            if ((cx == mx) && (cy == my))
                moving = false;
        }
        rect.x = x;
        rect.y = y;
        text_rect.x = (x + 35) - (name_width / 2);
        text_rect.y = y + height;
    }

    int get_x()
    {
        return x;
    }

    int get_y()
    {
        return y;
    }

    int get_w()
    {
        return width;
    }

    int get_h()
    {
        return height;
    }
};