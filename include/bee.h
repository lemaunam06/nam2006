#ifndef BEE_H
#define BEE_H

#include <SDL.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "chicken.h"
using namespace std;

struct Bee {
    SDL_Rect rect;
    float posY;
    float speed;
    int hp;
    Bee(SDL_Texture* texture);
    bool isOutOfScreen();
    void move();
};

void spawnBee(vector<Bee>& bees, SDL_Texture* beeTexture, Uint32 currentTime, Uint32& lastBeeTime, Uint32 beeCooldown);
void spawnEggBee(vector<Bee>& bees, vector<Egg>& eggs, SDL_Texture* eggTexture, const Uint32 &currentTime, Uint32 &lastEggBeeSpawnTime, const Uint32 &eggBeeSpawnCooldown);
void removeBee(vector<Bee>& bees);





#endif
