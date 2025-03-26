#ifndef CHICKEN_H
#define CHICKEN_H
#include <vector>
#include <SDL.h>
#include "object.h"
using namespace std;

void bornChicken(vector<Chicken>& chickens, SDL_Texture* chickenTexture, const Uint32 &currentTime, Uint32& lastChickenSpawnTime, const Uint32 &chickenSpawnCooldown, int &chickenDirection);
void moveChicken(vector<Chicken>& chickens, int& chickenDirection, float speedX, float speedY, int windowWidth);
void spawnEgg(vector<Chicken>& chickens, vector<Egg>& eggs, SDL_Texture* eggTexture, const Uint32 &currentTime, Uint32 &lastEggSpawnTime, Uint32 eggSpawnCooldown);
void removeEggs(vector<Egg>& eggs);
void removeChickens(vector<Chicken>& chickens);
#endif