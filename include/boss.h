#ifndef BOSS_H
#define BOSS_H
#include <SDL.h>

struct Boss {
    SDL_Rect rect;
    SDL_Texture* texture;
    float speedX,posX;
    int bossHp;
    bool appeared = false; 
    Boss(SDL_Texture* tex);
    void move(const int &windowWidth);
    void renderHealthBar(SDL_Renderer* renderer);
    bool Died();
};

void spawnBoss(Boss& boss, const Uint32& currentTime, Uint32 bossAppearTime);
void removeBoss(Boss &boss);
#endif 