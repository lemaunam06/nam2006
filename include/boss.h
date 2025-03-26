#ifndef BOSS_H
#define BOSS_H
#include <SDL.h>
#include "object.h"
void spawnBoss(Boss& boss, const Uint32& currentTime, Uint32 bossAppearTime);
void removeBoss(Boss &boss);
#endif 