#ifndef BOM_H
#define BOM_H

#include <vector>
#include <SDL.h>
using namespace std;

struct Bom1 {
    SDL_Rect rect;
    SDL_Texture* texture;
    float speed, posY;
    Bom1(SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
    int hitCount;
};

struct Bom2 {
    SDL_Rect rect;
    SDL_Texture* texture;
    float v, a, posY;
    Bom2(SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
};

void spawnBom(vector<Bom1>& bom1s, vector<Bom2>& bom2s, SDL_Texture* bom1Texture, SDL_Texture* bom2Texture, const Uint32& currentTime, Uint32& lastBomTime, const Uint32& BomCooldown);
void removeBom1(vector<Bom1>& bom1s);
void removeBom2(vector<Bom2>& bom2s);
#endif 