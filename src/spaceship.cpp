#include "spaceship.h"
#include <SDL.h>

Spaceship::Spaceship() {
    rect.x = 800 / 2 - 40;
    rect.y = 600 - 80;
    rect.w = 60;
    rect.h = 70;
    level =1;
    hp=3;
    posX = rect.x;
    posY = rect.y;
}

void Spaceship::move(SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        posX = event.motion.x - rect.w / 2;
        posY = event.motion.y - rect.h / 2;
    }

    rect.x = static_cast<int>(posX);
    rect.y = static_cast<int>(posY);
}







