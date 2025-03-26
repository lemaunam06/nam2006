#ifndef COLLISION_H
#define COLLISION_H
#include <vector>
#include <SDL.h>
#include "object.h"
#include "bee.h"
using namespace std;


bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
void EggCollision(vector<Egg>& eggs, Spaceship& spaceship);
void BulletChickenCollision(vector<Bullet>& bullets, vector<Chicken>& chickens);
void bulletBeeCollision(vector<Bullet>& bullets, std::vector<Bee>& bees);
void Bom1Collision(vector<Bom1>& bom1s, Spaceship& spaceship);
void Bom2Collision(vector<Bom2>& bom2s, Spaceship& spaceship);
void ChickenCollision(vector<Chicken>& chickens, Spaceship& spaceship);
void BulletBossCollision(std::vector<Bullet>& bullets, Boss& boss, int damagePerHit);
void bonusBulletCollision(vector<BonusBullet>& bonusBullets, Spaceship& spaceship);
void Bom1BulletCollision(vector<Bom1>& bom1s, vector<Bullet>& bullets);
void BossBulletCollision(std::vector<BossBullet>& bossBullets, Spaceship& spaceship);
void BeesCollision(Spaceship& spaceship, vector<Bee>& bees);
#endif 