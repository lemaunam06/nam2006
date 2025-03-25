#include "object.h"
#include <cstdlib>
#include <cmath>

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


BossBullet::BossBullet(int x, int y, SDL_Texture* tex) {
    rect.x = x + (75-30);
    rect.y = y + 200;
    rect.w = 60;
    rect.h = 65;
    posY = rect.y;
    speed = 0.5f;
    texture = tex;
}

void BossBullet::move() {
    posY += speed;
    rect.y = static_cast<int>(posY);
}

bool BossBullet::isOutOfScreen() {
    return rect.y > 600;
}


Chicken::Chicken(SDL_Texture* tex) {
    rect.x = 0 ;
    rect.y = 0;
    rect.w = 30;
    rect.h = 40;
    posX = rect.x;
    posY = rect.y;
    direction = 0;
    texture = tex;
}


bool Chicken::isOutOfScreen() {
    return rect.y > 600;
}

BonusBullet::BonusBullet(SDL_Texture* tex) {
    rect.x = rand() % (800 - 60 + 1);
    rect.y = -30;
    rect.w = 30;
    rect.h = 40;
    posY = rect.y;
    speedy = 0.2f; 
    texture = tex;
}

void BonusBullet::move() {
    posY += speedy;
    rect.y = static_cast<int>(posY);
}


bool BonusBullet::isOutOfScreen() {
    return rect.y > 600;
}

Egg::Egg(int x, int y, SDL_Texture* tex) {
    rect.x = x + 10;   // canh giữa trứng dưới gà
    rect.y = y + 40;   // dưới con gà 1 chút
    rect.w = 30;
    rect.h = 35;
    posY = rect.y;
    speed = 0.6f;
    texture = tex;
}

void Egg::move() {
    posY += speed;
    rect.y = static_cast<int>(posY);
}

bool Egg::isOutOfScreen() {
    return rect.y > 600;
}


Spaceship::Spaceship() {
    rect.x = 800 / 2 - 40;
    rect.y = 600 - 80;
    rect.w = 60;
    rect.h = 70;
    level =1;
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

Bullet::Bullet(int x, int y, SDL_Texture* tex) {
    rect.x = x ;
    rect.y = y;
    rect.w = 10;
    rect.h = 20;
    texture = tex;
    posY = rect.y;
}

float Bullet::speed = 0.5f;

void Bullet::move() {
    posY -= speed;
    rect.y = static_cast<int>(posY);
}

bool Bullet::isOutOfScreen() {
    return rect.y + rect.h < 0;
}

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



