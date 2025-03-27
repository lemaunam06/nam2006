#ifndef OBJECT_H
#define OBJECT_H
#include <SDL.h>

struct Spaceship {
    SDL_Texture* texture;
    SDL_Rect rect;
    int level, hp;
    float speed, posX, posY;
    Spaceship();
    void move(SDL_Event& event);
};





#endif
