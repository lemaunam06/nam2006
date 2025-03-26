#include <SDL.h>
#include "object.h"
#include "boss.h"
using namespace std;


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