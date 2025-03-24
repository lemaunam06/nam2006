#include <SDL.h>
#include "game.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
extern const int WINDOW_WIDTH = 800;
extern const int WINDOW_HEIGHT = 600;
extern const string WINDOW_TITLE = "MY GAME";

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Khoi Tao SDL Failed: " << SDL_GetError() << endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
        cerr << "Khoi tao SDL_Image Failed: " << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }

    if (TTF_Init() == -1) {
        cerr << "Lỗi khi khởi tạo SDL_ttf: " << TTF_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cerr << "Khoi tao cua so Failed: " << SDL_GetError() << endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Khoi tao Renderer Failed: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    font = TTF_OpenFont("assets/font.ttf", 20);
    if (!font) {
        cerr << "Lỗi khi tải font: " << TTF_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "Không thể khởi tạo SDL_mixer: " << Mix_GetError() << endl;
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

void showMenu(SDL_Renderer* renderer, SDL_Texture* menuTexture, SDL_Texture* textTexture,Mix_Music* menuMusic) {
    Mix_PlayMusic(menuMusic, -1); // phát nhạc
    bool menuRunning = true;
    SDL_Event event;
    SDL_Rect textRect = {(800-200)/2, (600-160)/2, 200, 160}; // Vị trí và kích thước chữ

    while (menuRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                menuRunning = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL); // Vẽ ảnh nền
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // Vẽ chữ
        SDL_RenderPresent(renderer);
    }
    Mix_HaltMusic();
    // Giải phóng bộ nhớ đúng cách
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(textTexture);
    Mix_FreeMusic(menuMusic);
}



SDL_Texture* updateScoreTexture(SDL_Renderer* renderer, TTF_Font* font) {
    // Nếu điểm số không thay đổi, trả về texture cũ
    if (scoreTexture != nullptr && score == lastScore) {
        return scoreTexture;
    }

    // Nếu có texture cũ, giải phóng nó
    if (scoreTexture != nullptr) {
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = nullptr;
    }
    // Tạo chuỗi văn bản mới cho điểm số
    string scoreText = "Score: " + to_string(score);
    SDL_Color textColor = {255, 255, 255, 255}; // Màu trắng

    // Tạo surface từ văn bản
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (!textSurface) {
        cerr << "Lỗi khi tạo surface từ văn bản: " << TTF_GetError() << endl;
        return nullptr;
    }

    // Chuyển surface thành texture
    scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // Cập nhật biến lastScore
    lastScore = score;

    return scoreTexture;
}

void saveHighScore(const int &score, const int highscore) {
    if (highscore < score){
        ofstream file("highscore.txt");
        if (file.is_open()){
            file << score;
            file.close();
        }
    }
}
int loadHighScore() {
    int highScore = 0;
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
    return highScore;
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const string& text, int x, int y, SDL_Color color) {
    // Tạo surface từ văn bản
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!textSurface) {
        SDL_Log("Không thể tạo surface: %s", TTF_GetError());
        return;
    }

    // Tạo texture từ surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface); // Giải phóng surface sau khi tạo texture
    if (!textTexture) {
        SDL_Log("Không thể tạo texture: %s", SDL_GetError());
        return;
    }

    // Lấy kích thước của văn bản
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Xác định vị trí hiển thị
    SDL_Rect renderQuad = {x, y, textWidth, textHeight};

    // Vẽ văn bản lên màn hình
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    SDL_DestroyTexture(textTexture);

}


void GameOver(SDL_Renderer* renderer, TTF_Font* font, const string& message) {
    SDL_Color red = {255, 0, 0};  // Màu đỏ
    // Hiển thị chuỗi truyền vào thay vì cố định
    renderText(renderer, font, message, 360, 280, red);

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
    // Chờ người chơi nhấn Enter
    SDL_Event e;
    bool waiting = true;
    while (waiting) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                waiting = false;
                break;
            }
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                waiting = false;
                break;
            }
        }
    }
}

void waitForEnterSDL(SDL_Renderer *renderer, SDL_Texture *victoryTexture) {
    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                running = false;
            } else if (e.type == SDL_QUIT) {
                running = false;
            }
            SDL_RenderCopy(renderer, victoryTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
        SDL_Delay(10);
    }
}









