#ifndef COLLISION_H
#define COLLISION_H
#include <vector>
#include <SDL.h>
#include "bee.h"
#include "bom.h"
#include "boss.h"
#include "bullet.h"
#include "chicken.h"
#include "spaceship.h"
using namespace std;


bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
void EggCollision(vector<Egg>& eggs, Spaceship& spaceship);
void BulletChickenCollision(vector<Bullet>& bullets, vector<Chicken>& chickens);
void bulletBeeCollision(vector<Bullet>& bullets, vector<Bee>& bees);
void Bom1Collision(vector<Bom1>& bom1s, Spaceship& spaceship);
void Bom2Collision(vector<Bom2>& bom2s, Spaceship& spaceship);
void ChickenCollision(vector<Chicken>& chickens, Spaceship& spaceship);
void BulletBossCollision(vector<Bullet>& bullets, Boss& boss, int damagePerHit);
void bonusBulletCollision(vector<BonusBullet>& bonusBullets, Spaceship& spaceship);
void Bom1BulletCollision(vector<Bom1>& bom1s, vector<Bullet>& bullets);
void BossBulletCollision(vector<BossBullet>& bossBullets, Spaceship& spaceship);
void BeesCollision(Spaceship& spaceship, vector<Bee>& bees);
#endif 