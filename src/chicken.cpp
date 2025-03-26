#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "object.h"
#include "chicken.h"
using namespace std;


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

void removeChickens(vector<Chicken>& chickens) {
    for (int i = chickens.size() - 1; i >= 0; --i) {
        if (chickens[i].isOutOfScreen()) {
            chickens.erase(chickens.begin() + i);
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
