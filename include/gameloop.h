#ifndef GAMELOOP_H 
#define GAMELOOP_H
#include <vector>
#include <SDL.h>
#include "object.h"
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
void spawnBullet(const Uint8* keys, vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, const Uint32& currentTime, Uint32& lastBulletTime, const Uint32& bulletCooldown);
void bornChicken(vector<Chicken>& chickens, SDL_Texture* chickenTexture, const Uint32 &currentTime, Uint32& lastChickenSpawnTime, const Uint32 &chickenSpawnCooldown, int &chickenDirection);
void moveChicken(vector<Chicken>& chickens, int& chickenDirection, float speedX, float speedY, int windowWidth);
void spawnBee(vector<Bee>& bees, SDL_Texture* beeTexture, const Uint32 &currentTime, Uint32& lastBeeSpawnTime, const Uint32 &beeSpawnCooldown);
void spawnBom(vector<Bom1>& bom1s, vector<Bom2>& bom2s, SDL_Texture* bom1Texture, SDL_Texture* bom2Texture, const Uint32& currentTime, Uint32& lastBomTime, const Uint32& BomCooldown);
void spawnEgg(vector<Chicken>& chickens, vector<Egg>& eggs, SDL_Texture* eggTexture, const Uint32 &currentTime, Uint32 &lastEggSpawnTime, Uint32 eggSpawnCooldown);
void spawnBoss(Boss& boss, const Uint32& currentTime, Uint32 bossAppearTime);
void spawnBossBullet(Boss& boss, std::vector<BossBullet>& bossBullets, SDL_Texture* bulletTexture, const Uint32& currentTime, Uint32& lastBossBulletTime, Uint32 bossBulletCooldown);
void EggCollision(const vector<Egg>& eggs, const Spaceship& spaceship, bool& running, bool& died);
void BulletBeeCollision(vector<Bullet>& bullets, std::vector<Bee>& bees, int& score);
void BulletChickenCollision(std::vector<Bullet>& bullets, std::vector<Chicken>& chickens, int& score);
void Bom1Collision(const vector<Bom1>& bom1s, const Spaceship& spaceship, bool& running, bool& died);
void Bom2Collision(const vector<Bom2>& bom2s, const Spaceship& spaceship, bool& running, bool& died);
void ChickenCollision(const vector<Chicken>& chickens, const Spaceship& spaceship, bool& running, bool& died);
void BulletBossCollision(std::vector<Bullet>& bullets, Boss& boss, int damagePerHit);
void BeeCollision(const vector<Bee>& bees, const Spaceship& spaceship, bool& running, bool& died);
void Bom1BulletCollision(vector<Bom1>& bom1s, vector<Bullet>& bullets);
void BossBulletCollision(std::vector<BossBullet>& bossBullets, Spaceship& spaceship, bool& running, bool& died);
void removeBullets(vector<Bullet>& bullets);
void removeBees(std::vector<Bee>& bees);
void removeChickens(vector<Chicken>& chickens);
void removeBom1(vector<Bom1>& bom1s);
void removeBom2(vector<Bom2>& bom2s);
void removeEggs(vector<Egg>& eggs);
void removeBoss(Boss &boss);
void removeOutOfScreenBossBullets(vector<BossBullet>& bossBullets);
#endif