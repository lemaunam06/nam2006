#ifndef BOM_H
#define BOM_H

#include <vector>
#include <SDL.h>
#include "object.h"
using namespace std;
void spawnBom(vector<Bom1>& bom1s, vector<Bom2>& bom2s, SDL_Texture* bom1Texture, SDL_Texture* bom2Texture, const Uint32& currentTime, Uint32& lastBomTime, const Uint32& BomCooldown);
void removeBom1(vector<Bom1>& bom1s);
void removeBom2(vector<Bom2>& bom2s);
#endif 