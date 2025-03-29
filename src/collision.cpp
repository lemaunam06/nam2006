#include <vector>
#include <SDL.h>
#include "collision.h"
#include "bee.h"
#include "bom.h"
#include "boss.h"
#include "bullet.h"
#include "chicken.h"
#include "spaceship.h"
using namespace std;

extern int score;
extern int lastscore;

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

void BulletBossCollision(vector<Bullet>& bullets, Boss& boss, int damagePerHit) {
    if (!boss.appeared) return; // Nếu boss chưa xuất hiện thì không xử lý

    for (int i = bullets.size() - 1; i >= 0; --i) {
        if (checkCollision(bullets[i].rect, boss.rect)) {
            boss.bossHp -= damagePerHit; // Trừ máu boss
            bullets.erase(bullets.begin() + i); // Xóa viên đạn đã bắn trúng
        }
    }
}

void BulletChickenCollision(vector<Bullet>& bullets, vector<Chicken>& chickens) {
    for (int i = bullets.size() - 1; i >= 0; --i) {
        for (int j = chickens.size() - 1; j >= 0; --j) {
            if (checkCollision(bullets[i].rect, chickens[j].rect)) {
                bullets.erase(bullets.begin() + i); // Xóa viên đạn
                chickens.erase(chickens.begin() + j); // Xóa con gà
                score+=5;
                break; 
            }
        }
    }
}

void bulletBeeCollision(vector<Bullet>& bullets, std::vector<Bee>& bees) {
    for (int i = bullets.size() - 1; i >= 0; --i) {
        for (int j = bees.size() - 1; j >= 0; --j) {
            if (checkCollision(bullets[i].rect, bees[j].rect)) {
                // Nếu va chạm, xóa cả đạn và ong
                bullets.erase(bullets.begin() + i);
                bees[j].hp--;
                if (bees[j].hp==0){
                    bees.erase(bees.begin() + j);
                    // Cộng điểm nếu muốn
                    score += 10;
                } 
                break; // Đạn đã va chạm thì không cần kiểm tra tiếp
            }
        }
    }
}


void Bom1Collision(vector<Bom1>& bom1s, Spaceship& spaceship) {
    for (int i = bom1s.size() - 1; i >= 0; --i) {
        if (checkCollision(bom1s[i].rect, spaceship.rect)) {
            spaceship.hp--;
            bom1s.erase(bom1s.begin()+i);
            break;
        }
    }
}

void Bom2Collision(vector<Bom2>& bom2s, Spaceship& spaceship) {
    for (int i = bom2s.size() - 1; i >= 0; --i) {
        if (checkCollision(bom2s[i].rect, spaceship.rect)) {
            spaceship.hp--;
            bom2s.erase(bom2s.begin()+i);
            break;
        }
    }
}

void ChickenCollision(vector<Chicken>& chickens, Spaceship& spaceship) {
    for (int i = chickens.size() - 1; i >= 0; --i) {
        if (checkCollision(chickens[i].rect, spaceship.rect)) {
            spaceship.hp--;
            chickens.erase(chickens.begin()+i);
            break;
        }
    }
}



void EggCollision(vector<Egg>& eggs, Spaceship& spaceship) {
    for (int i = eggs.size() - 1; i >= 0; --i) {
        if (checkCollision(eggs[i].rect, spaceship.rect)) {
            spaceship.hp--;
            eggs.erase(eggs.begin()+i);
            break;
        }
    }
}

void BossBulletCollision(std::vector<BossBullet>& bossBullets, Spaceship& spaceship) {
    for (int i = bossBullets.size() - 1; i >= 0; --i) {
        if (checkCollision(bossBullets[i].rect, spaceship.rect)) {
            spaceship.hp--;
            bossBullets.erase(bossBullets.begin() + i);  // Xóa đạn khi va chạm
            break;
        }
    }
}

void BeesCollision(Spaceship& spaceship, vector<Bee>& bees) {
    for (int i = bees.size() - 1; i >= 0; i--) {
        if (checkCollision(spaceship.rect, bees[i].rect)) {
            // Xử lý khi va chạm (ví dụ: giảm máu, kết thúc game hoặc hiệu ứng nổ)
            spaceship.hp--;  // nếu có biến hp
            bees.erase(bees.begin() + i);
        }
    }
}

void bonusBulletCollision(vector<BonusBullet>& bonusBullets, Spaceship& spaceship) {
    for (int i = bonusBullets.size() - 1; i >= 0; --i) {
        if (checkCollision(bonusBullets[i].rect, spaceship.rect)) {
            spaceship.level++;
            Bullet::speedY += 0.1f;
            bonusBullets.erase(bonusBullets.begin()+i);
        }
    }
}


void Bom1BulletCollision(vector<Bom1>& bom1s, vector<Bullet>& bullets) {
    for (int i = bom1s.size() - 1; i >= 0; --i) {
        for (int j = bullets.size() - 1; j >= 0; --j) {
            if (checkCollision(bom1s[i].rect, bullets[j].rect)) {
                bullets.erase(bullets.begin() + j); // Xóa đạn
                bom1s[i].hitCount++;             // Tăng hitCount của bom1
            }
        }
        if (bom1s[i].hitCount >= 5) {  
            bom1s.erase(bom1s.begin() + i);
            score+=5;        
        }  
    }
}