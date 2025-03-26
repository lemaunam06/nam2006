#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "object.h"
#include "bullet.h"
using namespace std;



void spawnBullet(const Uint8* keys, vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, const Uint32& currentTime, Uint32& lastBulletTime, const Uint32& bulletCooldown) {
    if (keys[SDL_SCANCODE_SPACE] && currentTime - lastBulletTime >= bulletCooldown) {
        bullets.emplace_back(spaceship.rect.x+25, spaceship.rect.y, bulletTexture);
        Mix_PlayChannel(-1, shootSound, 0);  // Phát âm thanh bắn
        lastBulletTime = currentTime;
    }
}

void spawnBossBullet(Boss& boss, vector<BossBullet>& bossBullets, SDL_Texture* bossbulletTexture, const Uint32& currentTime, Uint32& lastBossBulletTime, Uint32 bossBulletCooldown) {
    if (boss.appeared && (currentTime - lastBossBulletTime >= bossBulletCooldown)) {
        bossBullets.emplace_back(boss.rect.x, boss.rect.y, bossbulletTexture);
        lastBossBulletTime = currentTime;
    }
}

void spawnDoubleBullet(const Uint8* keys, vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, Uint32& lastBulletTime, Uint32 bulletCooldown) {
    Uint32 currentTime = SDL_GetTicks();
    if (keys[SDL_SCANCODE_SPACE] && currentTime - lastBulletTime >= bulletCooldown) {
        int bulletY = spaceship.rect.y;
        int bulletXLeft = spaceship.rect.x + spaceship.rect.w / 2 -10; // Đạn trái
        int bulletXRight = spaceship.rect.x + spaceship.rect.w / 2 ; // Đạn phải

        Bullet bullet1(bulletXLeft, bulletY, bulletTexture);
        Bullet bullet2(bulletXRight, bulletY, bulletTexture);

        bullets.push_back(bullet1);
        bullets.push_back(bullet2);

        Mix_PlayChannel(-1, shootSound, 0);
        lastBulletTime = currentTime;
    }
}

void spawnTripleBullet(const Uint8* keys, vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, Uint32& lastBulletTime, Uint32 bulletCooldown) {
    Uint32 currentTime = SDL_GetTicks();
    if (keys[SDL_SCANCODE_SPACE] && currentTime - lastBulletTime >= bulletCooldown) {
        int bulletY = spaceship.rect.y;
        int centerX = spaceship.rect.x + spaceship.rect.w / 2;

        // Đạn trái, đạn giữa và đạn phải
        int bulletXLeft = centerX - 15;
        int bulletXCenter = centerX - 5;
        int bulletXRight = centerX + 5;

        bullets.push_back(Bullet(bulletXLeft, bulletY, bulletTexture));
        bullets.push_back(Bullet(bulletXCenter, bulletY, bulletTexture));
        bullets.push_back(Bullet(bulletXRight, bulletY, bulletTexture));

        Mix_PlayChannel(-1, shootSound, 0);
        lastBulletTime = currentTime;
    }
}

void spawnBonusBullet(vector<BonusBullet>& bonusBullets, SDL_Texture* BonusBulletTexture, const Uint32 &currentTime, Uint32& lastBonusSpawnTime, const Uint32 &bonusSpawnCooldown) {
    if (currentTime - lastBonusSpawnTime >= bonusSpawnCooldown) {
        int numBonus = 1 + rand() % 2; // Random từ 1 đến 4 gà
        for (int i = 0; i < numBonus; i++) {
            bonusBullets.emplace_back(BonusBulletTexture); // Thêm gà mới
        }
        lastBonusSpawnTime = currentTime; // Cập nhật thời gian spawn
    }
}


void removeBullets(vector<Bullet>& bullets) {
    for (int i = bullets.size() - 1; i >= 0; --i) {
        if (bullets[i].isOutOfScreen()) {
            bullets.erase(bullets.begin() + i);
        }
    }
}

void removeBonusBullet(vector<BonusBullet>& bonusBullets) {
    for (int i = bonusBullets.size() - 1; i >= 0; --i) {
        if (bonusBullets[i].isOutOfScreen()) {
            bonusBullets.erase(bonusBullets.begin() + i);
        }
    }
}

void removeBossBullets(vector<BossBullet>& bossBullets) {
    for (int i = bossBullets.size() - 1; i >= 0; --i) {
        if (bossBullets[i].isOutOfScreen()) {
            bossBullets.erase(bossBullets.begin() + i);
        }
    }
}