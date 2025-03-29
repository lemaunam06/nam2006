#include <SDL.h>
#include "boss.h"
using namespace std;

Boss::Boss(SDL_Texture* tex) {
    rect.x = 400;     // Lúc đầu để ngoài màn hình
    rect.y = 20;
    rect.w = 150;
    rect.h = 200;
    bossHp = 500;
    posX = rect.x;
    speedX = 0.05f;
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

void Boss::renderHealthBar(SDL_Renderer* renderer) {
    if (!appeared) return;

    int barWidth = 150;
    int barHeight = 10;
    int barX = rect.x;
    int barY = rect.y -15;

    float healthPercentage = (float)bossHp / 500;
    int currentBarWidth = (int)(barWidth * healthPercentage);

    // Vẽ nền thanh máu (màu đen)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect backgroundBar = { barX, barY, barWidth, barHeight };
    SDL_RenderFillRect(renderer, &backgroundBar);

    // Vẽ thanh máu (màu đỏ)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect healthBar = { barX, barY, currentBarWidth, barHeight };
    SDL_RenderFillRect(renderer, &healthBar);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
