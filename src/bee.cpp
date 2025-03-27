#include <vector>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "bee.h"
#include "chicken.h"
using namespace std;

Bee::Bee(SDL_Texture* texture) {
    rect.x = rand() % (800 - 50); // Bee xuất hiện ngẫu nhiên trong khung màn hình
    rect.y = -50; 
    rect.w = 50;
    rect.h = 50;
    posY = rect.y;
    speed = 0.05f;
    hp=2;
}

void Bee::move() {
    posY += speed;
    rect.y = static_cast<int>(posY);
}

bool Bee::isOutOfScreen(){
    return (rect.y > 600);
}

void spawnBee(vector<Bee>& bees, SDL_Texture* beeTexture, Uint32 currentTime, Uint32& lastBeeTime, Uint32 beeCooldown) {
    if (currentTime - lastBeeTime >= beeCooldown) {
        int numBees = 1 + rand() % 2; // Tạo từ 1 đến 3 con ong mỗi lần
        for (int i = 0; i < numBees; i++) {
            bees.emplace_back(beeTexture);
        }
        lastBeeTime = currentTime;
    }
}

void spawnEggBee(vector<Bee>& bees, vector<Egg>& eggs, SDL_Texture* eggTexture, const Uint32 &currentTime, Uint32 &lastEggBeeSpawnTime, const Uint32 &eggBeeSpawnCooldown) {
    if (currentTime - lastEggBeeSpawnTime >= eggBeeSpawnCooldown) {
        for (auto &bee : bees) {
            eggs.emplace_back(bee.rect.x, bee.rect.y, eggTexture);
        }
        lastEggBeeSpawnTime = currentTime;
    }
}


void removeBee(vector<Bee>& bees) {
    for (int i = bees.size() - 1; i >= 0; --i) {
        if (bees[i].isOutOfScreen()) {
            bees.erase(bees.begin() + i);
        }
    }
}

