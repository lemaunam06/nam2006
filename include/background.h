#ifndef BACKGROUD_H
#define BACKGROUND_H

#include <SDL.h>
using namespace std;


extern float backgroundY;
extern const float backgroundScrollSpeed;
void updateBackground();
void renderBackground(SDL_Renderer* renderer, SDL_Texture* backgroundTex);

#endif