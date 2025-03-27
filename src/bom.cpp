#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "bom.h"
using namespace std;

Bom1::Bom1(SDL_Texture* tex) {
    rect.x = 0 + rand() % (800 - 40 + 1);
    rect.y = -30;
    rect.w = 45;
    rect.h = 45;
    posY = rect.y;
    texture = tex;
    speed = 0.15f;
    hitCount = 0;
}

void Bom1::move() {
    posY += speed;
    rect.y = static_cast<int>(posY);
}

bool Bom1::isOutOfScreen() {
    return rect.y > 600;
}

Bom2::Bom2(SDL_Texture* tex){
    rect.x = 0 + rand() % (800 - 30 + 1);
    rect.y = -5;
    rect.w = 40;
    rect.h = 40;
    posY = rect.y;
    texture = tex;
    v = 0.6f;
    a = 0.0005f;
}
void Bom2:: move(){
    v += a;
    posY += v;
    rect.y = (int)posY;
}

bool Bom2::isOutOfScreen() {
    return rect.y > 600;
}

void spawnBom(vector<Bom1>& bom1s, vector<Bom2>& bom2s, SDL_Texture* bom1Texture, SDL_Texture* bom2Texture, const Uint32& currentTime, Uint32& lastBomTime, const Uint32& BomCooldown) {
    if (currentTime - lastBomTime >= BomCooldown) {
        int numBoms = 1 + rand() % 3; // Sinh từ 1 đến 3 quả bom
        int randomCase = 1 + rand() % 2; // Chọn loại bom: 1 hoặc 2

        if (randomCase == 1) {
            for (int i = 0; i < numBoms; i++) {
                bom1s.emplace_back(bom1Texture);
            }
        } else {
            for (int i = 0; i < numBoms; i++) {
                bom2s.emplace_back(bom2Texture);
            }
        }

        lastBomTime = currentTime;
    }
}
void removeBom1(vector<Bom1>& bom1s) {
    for (int i = bom1s.size() - 1; i >= 0; --i) {
        if (bom1s[i].isOutOfScreen()) {
            bom1s.erase(bom1s.begin() + i);
        }
    }
}

void removeBom2(vector<Bom2>& bom2s) {
    for (int i = bom2s.size() - 1; i >= 0; --i) {
        if (bom2s[i].isOutOfScreen()) {
            bom2s.erase(bom2s.begin() + i);
        }
    }
}