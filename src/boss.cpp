#include <SDL.h>
#include "boss.h"
using namespace std;

Boss::Boss(SDL_Texture* tex) {
    rect.x = 400;     // Lúc đầu để ngoài màn hình
    rect.y = 0;
    rect.w = 150;
    rect.h = 200;
    bossHp = 500;
    posX = rect.x;
    speedX = 0.15f;
    texture = tex;
    appeared = false;  // Chưa xuất hiện
}

void Boss::move(const int &windowWidth) {
    posX += speedX;
    if (posX <= 0 || posX + rect.w >= windowWidth) {
        speedX = -speedX;  // Đổi hướng khi chạm mép
    }
    rect.x = (int)posX;
}

bool Boss::Died() {
    return bossHp <= 0;
}


void spawnBoss(Boss &boss, const Uint32 &currentTime, Uint32 bossAppearTime) {
    if (currentTime >= bossAppearTime && !boss.appeared) {
        boss.appeared = true;      // Hồi đầy máu
    }
}


void removeBoss(Boss &boss) {
    if (boss.Died()) {
        boss.appeared = false; 
        boss.posX = -200;   // Đẩy boss ra khỏi màn hình
        boss.rect.x = -200;
        boss.bossHp = 0;
    }
}