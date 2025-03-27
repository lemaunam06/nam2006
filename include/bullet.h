#ifndef BULLET_H
#define BULLET_H
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include "spaceship.h"
#include "boss.h"
using namespace std;

struct BonusBullet {
    SDL_Rect rect;
    SDL_Texture* texture;
    float speedy,posY,posX;
    BonusBullet(SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
};


struct BossBullet {
    SDL_Rect rect;
    float posY;
    float speed;
    SDL_Texture* texture;

    BossBullet(int x, int y, SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
};

struct Bullet {
    SDL_Rect rect;
    SDL_Texture* texture;
    float posX, posY;
    static float speed;
    Bullet(int x, int y, SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
};

void spawnBullet(const Uint8* keys, vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, const Uint32& currentTime, Uint32& lastBulletTime, const Uint32& bulletCooldown);
void spawnDoubleBullet(const Uint8* keys, vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, Uint32& lastBulletTime, Uint32 bulletCooldown);
void spawnTripleBullet(const Uint8* keys, vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, Uint32& lastBulletTime, Uint32 bulletCooldown);
void spawnBonusBullet(vector<BonusBullet>& bonusBullets, SDL_Texture* BonusBulletTexture, const Uint32 &currentTime, Uint32& lastBonusSpawnTime, const Uint32 &bonusSpawnCooldown);
void spawnBossBullet(Boss& boss,vector<BossBullet>& bossBullets, SDL_Texture* bulletTexture, const Uint32& currentTime, Uint32& lastBossBulletTime, Uint32 bossBulletCooldown);
void removeBossBullets(vector<BossBullet>& bossBullets);
void removeBonusBullet(vector<BonusBullet>& bonusBullets);
void removeBullets(vector<Bullet>& bullets);
#endif 