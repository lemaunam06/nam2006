#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include "object.h"
#include "gameloop.h"
using namespace std;

float backgroundY = 0;
const float backgroundScrollSpeed = 0.5;


bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

void spawnBullet(const Uint8* keys, vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, const Uint32& currentTime, Uint32& lastBulletTime, const Uint32& bulletCooldown) {
    if (keys[SDL_SCANCODE_SPACE] && currentTime - lastBulletTime >= bulletCooldown) {
        bullets.emplace_back(spaceship.rect.x+25, spaceship.rect.y, bulletTexture);
        Mix_PlayChannel(-1, shootSound, 0);  // Phát âm thanh bắn
        lastBulletTime = currentTime;
    }
}

void spawnBossBullet(Boss& boss, std::vector<BossBullet>& bossBullets, SDL_Texture* bossbulletTexture, const Uint32& currentTime, Uint32& lastBossBulletTime, Uint32 bossBulletCooldown) {
    if (boss.appeared && (currentTime - lastBossBulletTime >= bossBulletCooldown)) {
        bossBullets.emplace_back(boss.rect.x, boss.rect.y, bossbulletTexture);
        lastBossBulletTime = currentTime;
    }
}

void spawnDoubleBullet(const Uint8* keys, std::vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, Uint32& lastBulletTime, Uint32 bulletCooldown) {
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

void spawnTripleBullet(const Uint8* keys, std::vector<Bullet>& bullets, const Spaceship& spaceship, SDL_Texture* bulletTexture, Mix_Chunk* shootSound, Uint32& lastBulletTime, Uint32 bulletCooldown) {
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


void bornChicken(vector<Chicken>& chickens, SDL_Texture* chickenTexture, const Uint32 &currentTime, Uint32& lastChickenSpawnTime, const Uint32 &chickenSpawnCooldown, int &chickenDirection) 
{
    if (currentTime - lastChickenSpawnTime >= chickenSpawnCooldown) {
        int rows = 3;                  // 3 hàng gà
        int cols = 6;                  // 6 cột gà (tạo thành hình chữ nhật)
        int startX = 100;              // Điểm bắt đầu theo trục X
        int startY = 50;               // Điểm bắt đầu theo trục Y
        int offsetX = 40;              // Khoảng cách giữa các gà theo trục X
        int offsetY = 30;              // Khoảng cách giữa các gà theo trục Y
        // Tạo đội hình
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                Chicken chicken(chickenTexture);
                chicken.rect.x = startX + col * offsetX;
                chicken.rect.y = startY + row * offsetY;
                chicken.posX = chicken.rect.x;
                chicken.posY = chicken.rect.y;
                chicken.direction = chickenDirection; // Gán hướng bay chung cho cả đội
                chickens.push_back(chicken);
            }
        }
        lastChickenSpawnTime = currentTime;
    }
}

void moveChicken(vector<Chicken>& chickens, int& chickenDirection, float speedX, float speedY, int windowWidth) 
{
    if (chickens.empty()) return;

    // Tính biên trái và biên phải của cả đội gà
    int leftMost = chickens[0].rect.x;
    int rightMost = chickens[0].rect.x;

    for (auto& chicken : chickens) {
        if (chicken.rect.x < leftMost) leftMost = chicken.rect.x;
        if (chicken.rect.x > rightMost) rightMost = chicken.rect.x;
    }
    // Nếu đội gà chạm biên trái hoặc phải, đảo chiều và hạ xuống
    if (leftMost <= 0 || rightMost >= windowWidth - chickens[0].rect.w) {
        chickenDirection *= -1;
        for (auto& chicken : chickens) {
            chicken.posY += speedY;  // Hạ xuống 1 đoạn
        }
    }

    // Di chuyển theo hướng hiện tại
    for (auto& chicken : chickens) {
        chicken.posX += chickenDirection * speedX;
        chicken.rect.x = static_cast<int>(chicken.posX);
        chicken.rect.y = static_cast<int>(chicken.posY);
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

void spawnEgg(vector<Chicken>& chickens, vector<Egg>& eggs, SDL_Texture* eggTexture, const Uint32 &currentTime, Uint32 &lastEggSpawnTime, Uint32 eggSpawnCooldown) {
    if (currentTime - lastEggSpawnTime >= eggSpawnCooldown) {
        for (auto &chicken : chickens) {
            // 30% xác suất mỗi con gà đẻ trứng
            if (rand() % 100 < 30) {
                eggs.emplace_back(chicken.rect.x, chicken.rect.y, eggTexture);
            }
        }
        lastEggSpawnTime = currentTime;
    }
}

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


void spawnBom(vector<Bom1>& bom1s, vector<Bom2>& bom2s, SDL_Texture* bom1Texture, SDL_Texture* bom2Texture, const Uint32& currentTime, Uint32& lastBomTime, const Uint32& BomCooldown) {
    if (currentTime - lastBomTime >= BomCooldown) {
        int numBoms = 1 + rand() % 3; // Sinh từ 1 đến 3 quả bom
        int randomCase = 1 + rand() % 2; // Chọn loại bom: 1 hoặc 2

        if (randomCase == 1) {
            for (int i = 0; i < numBoms; i++) {
                bom1s.emplace_back(bom1Texture);
            }
        } else {
            for (int i = 0; i < numBoms; i++) {
                bom2s.emplace_back(bom2Texture);
            }
        }

        lastBomTime = currentTime;
    }
}


void BulletBossCollision(std::vector<Bullet>& bullets, Boss& boss, int damagePerHit) {
    if (!boss.appeared) return; // Nếu boss chưa xuất hiện thì không xử lý

    for (int i = bullets.size() - 1; i >= 0; --i) {
        if (checkCollision(bullets[i].rect, boss.rect)) {
            boss.bossHp -= damagePerHit; // Trừ máu boss
            bullets.erase(bullets.begin() + i); // Xóa viên đạn đã bắn trúng
        }
    }
}

void BulletChickenCollision(std::vector<Bullet>& bullets, std::vector<Chicken>& chickens, int& score) {
    for (int i = bullets.size() - 1; i >= 0; --i) {
        for (int j = chickens.size() - 1; j >= 0; --j) {
            if (checkCollision(bullets[i].rect, chickens[j].rect)) {
                bullets.erase(bullets.begin() + i); // Xóa viên đạn
                chickens.erase(chickens.begin() + j); // Xóa con gà
                score++;
                break; 
            }
        }
    }
}

void Bom1Collision(const vector<Bom1>& bom1s, const Spaceship& spaceship, bool& running, bool& died) {
    for (int i = bom1s.size() - 1; i >= 0; --i) {
        if (checkCollision(bom1s[i].rect, spaceship.rect)) {
            running = false;
            died = true;
            break;
        }
    }
}

void Bom2Collision(const vector<Bom2>& bom2s, const Spaceship& spaceship, bool& running, bool& died) {
    for (int i = bom2s.size() - 1; i >= 0; --i) {
        if (checkCollision(bom2s[i].rect, spaceship.rect)) {
            running = false;
            died = true;
            break;
        }
    }
}

void ChickenCollision(const vector<Chicken>& chickens, const Spaceship& spaceship, bool& running, bool& died) {
    for (int i = chickens.size() - 1; i >= 0; --i) {
        if (checkCollision(chickens[i].rect, spaceship.rect)) {
            running = false;
            died = true;
            break;
        }
    }
}

void EggCollision(const vector<Egg>& eggs, const Spaceship& spaceship, bool& running, bool& died) {
    for (int i = eggs.size() - 1; i >= 0; --i) {
        if (checkCollision(eggs[i].rect, spaceship.rect)) {
            running = false;
            died = true;
            break;
        }
    }
}

void BossBulletCollision(std::vector<BossBullet>& bossBullets, Spaceship& spaceship, bool& running, bool& died) {
    for (int i = bossBullets.size() - 1; i >= 0; --i) {
        if (checkCollision(bossBullets[i].rect, spaceship.rect)) {
            running = false;  // Game over
            died = true;
            bossBullets.erase(bossBullets.begin() + i);  // Xóa đạn khi va chạm
            break;
        }
    }
}



void bonusBulletCollision(vector<BonusBullet>& bonusBullets, Spaceship& spaceship) {
    for (int i = bonusBullets.size() - 1; i >= 0; --i) {
        if (checkCollision(bonusBullets[i].rect, spaceship.rect)) {
            spaceship.level++;
            Bullet::speed += 0.1f;
            bonusBullets.erase(bonusBullets.begin()+i);
        }
    }
}


void Bom1BulletCollision(vector<Bom1>& bom1s, vector<Bullet>& bullets) {
    for (int i = bom1s.size() - 1; i >= 0; --i) {
        for (int j = bullets.size() - 1; j >= 0; --j) {
            if (checkCollision(bom1s[i].rect, bullets[j].rect)) {
                bullets.erase(bullets.begin() + j); // Xóa đạn
                bom1s[i].hitCount++;               // Tăng hitCount của bom1
            }
        }
        if (bom1s[i].hitCount >= 5) {  
            bom1s.erase(bom1s.begin() + i);
        }
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


void removeChickens(vector<Chicken>& chickens) {
    for (int i = chickens.size() - 1; i >= 0; --i) {
        if (chickens[i].isOutOfScreen()) {
            chickens.erase(chickens.begin() + i);
        }
    }
}

void removeBom1(vector<Bom1>& bom1s) {
    for (int i = bom1s.size() - 1; i >= 0; --i) {
        if (bom1s[i].isOutOfScreen()) {
            bom1s.erase(bom1s.begin() + i);
        }
    }
}

void removeBom2(vector<Bom2>& bom2s) {
    for (int i = bom2s.size() - 1; i >= 0; --i) {
        if (bom2s[i].isOutOfScreen()) {
            bom2s.erase(bom2s.begin() + i);
        }
    }
}

void removeEggs(vector<Egg>& eggs) {
    for (int i = eggs.size() - 1; i >= 0; --i) {
        if (eggs[i].isOutOfScreen()) {
            eggs.erase(eggs.begin() + i);
        }
    }
}

void removeOutOfScreenBossBullets(vector<BossBullet>& bossBullets) {
    for (int i = bossBullets.size() - 1; i >= 0; --i) {
        if (bossBullets[i].isOutOfScreen()) {
            bossBullets.erase(bossBullets.begin() + i);
        }
    }
}


// Hàm cập nhật vị trí background
void updateBackground() {
    backgroundY += backgroundScrollSpeed;
    if (backgroundY >= 600) {   // 600 là chiều cao ảnh background
        backgroundY = 0;
    }
}

// Hàm vẽ background
void renderBackground(SDL_Renderer* renderer, SDL_Texture* backgroundTex) {
    SDL_Rect bgRect1 = { 0, (int)backgroundY, 800, 600 };      // ảnh chính
    SDL_Rect bgRect2 = { 0, (int)backgroundY - 600, 800, 600 }; // ảnh phụ để liền mạch

    SDL_RenderCopy(renderer, backgroundTex, NULL, &bgRect1);
    SDL_RenderCopy(renderer, backgroundTex, NULL, &bgRect2);
}












