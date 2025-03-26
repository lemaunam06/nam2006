#ifndef BULLET_H
#define BULLET_H
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include "object.h"
using namespace std;

void spawnBullet(const Uint8* keys, vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, const Uint32& currentTime, Uint32& lastBulletTime, const Uint32& bulletCooldown);
void spawnDoubleBullet(const Uint8* keys, std::vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, Uint32& lastBulletTime, Uint32 bulletCooldown);
void spawnTripleBullet(const Uint8* keys, std::vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, Uint32& lastBulletTime, Uint32 bulletCooldown);
void spawnBonusBullet(vector<BonusBullet>& bonusBullets, SDL_Texture* BonusBulletTexture, const Uint32 &currentTime, Uint32& lastBonusSpawnTime, const Uint32 &bonusSpawnCooldown);
void spawnBossBullet(Boss& boss, std::vector<BossBullet>& bossBullets, SDL_Texture* bulletTexture, const Uint32& currentTime, Uint32& lastBossBulletTime, Uint32 bossBulletCooldown);
void removeBossBullets(vector<BossBullet>& bossBullets);
void removeBonusBullet(vector<BonusBullet>& bonusBullets);
void removeBullets(vector<Bullet>& bullets);
#endif 