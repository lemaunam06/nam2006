#include "background.h"

float backgroundY = 0;
const float backgroundScrollSpeed = 0.15f;
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
