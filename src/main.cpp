#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "object.h"
#include "game.h"
#include "gameloop.h"
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const string WINDOW_TITLE = "SpaceShip War";
int chickenDirection=1;
SDL_Texture* scoreTexture = nullptr; // Texture lưu điểm số hiện tại
int score=0, lastScore = -1;


int main(int argc, char* argv[]) {
    srand(time(0));
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;
    if (!initSDL(window, renderer, font)) {
        return 1;
    }
    // Khơi tạo font chữ
    SDL_Color textColor = {255, 255, 255, 255}; // Màu trắng 

    
    // Nhạc
    Mix_Music* menuMusic = Mix_LoadMUS("assets/menu_music.mp3");
    Mix_Music* bgMusic = Mix_LoadMUS("assets/background_music.mp3");
    Mix_Music* winSound = Mix_LoadMUS("assets/winsound.mp3");
    Mix_Chunk* shootSound = Mix_LoadWAV("assets/shoot.wav");
    
  

    // Ảnh game
    SDL_Texture* BackGroundTexture = IMG_LoadTexture(renderer, "assets/BackGround.png");
    SDL_Texture* spaceshipTexture = IMG_LoadTexture(renderer, "assets/player.png");                         
    SDL_Texture* bulletTexture = IMG_LoadTexture(renderer, "assets/bullet.png");
    SDL_Texture* chickenTexture = IMG_LoadTexture(renderer, "assets/chicken.png");
    SDL_Texture* bom1Texture = IMG_LoadTexture(renderer, "assets/bom.png");
    SDL_Texture* bom2Texture = IMG_LoadTexture(renderer, "assets/bom2.png");
    SDL_Texture* introlTexture = IMG_LoadTexture(renderer, "assets/introl.png");
    SDL_Texture* BonusBulletTexture = IMG_LoadTexture(renderer, "assets/BonusBullet.png");
    SDL_Texture* eggTexture = IMG_LoadTexture(renderer, "assets/egg.png");
    SDL_Texture* bossTexture = IMG_LoadTexture(renderer, "assets/Boss.png");
    SDL_Texture* bossbulletTexture = IMG_LoadTexture(renderer, "assets/bossBullet.png");
    SDL_Texture* victoryTexture = IMG_LoadTexture(renderer, "assets/victory.png");
    SDL_Texture* gameoverTexture = IMG_LoadTexture(renderer, "assets/gameover.png");



    Spaceship spaceship;
    spaceship.texture = spaceshipTexture;
    Boss boss(bossTexture);
    vector <Chicken> chickens;
    vector<BonusBullet> bonusBullets;
    vector <Egg> eggs;  
    vector<Bullet> bullets;
    vector <BossBullet> bossBullets;
    vector <Bom1> bom1s;
    vector <Bom2> bom2s;

    showMenu(renderer,introlTexture,menuMusic);
    Mix_VolumeMusic(20);       // Giảm âm lượng nhạc nền xuống 25% (32/128)
    Mix_VolumeChunk(shootSound, 100);
    Mix_PlayMusic(bgMusic, -1);

    Uint32 lastEggSpawnTime = 0;
    const Uint32 eggSpawnCooldown = 3000; // 3 giây kiểm tra 1 lần 
    Uint32 lastBulletTime = 0;
    const Uint32 bulletCooldown = 200;
    Uint32 lastChickenSpawnTime = 0;
    const Uint32 chickenSpawnCooldown = 10000;
    Uint32 lastBonusSpawnTime=0;
    const Uint32 bonusSpawnCooldown = 20000;
    Uint32 lastBomTime = 0;
    const Uint32 BomCooldown = 6000;
    Uint32 bossAppearTime = 60000; // 60 giây
    Uint32 lastBossBulletTime = 0;
    Uint32 ExitTime = 0;
    
    const int highscore = loadHighScore();
    const string highscoreText = "High Score: " + to_string(highscore);
    bool running = true;
    bool died = false;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            spaceship.move(event);
        }
        const Uint8* keys = SDL_GetKeyboardState(NULL);

        Uint32 currentTime = SDL_GetTicks();

        // sinh ra ong
        spawnEgg(chickens, eggs, eggTexture, currentTime, lastEggSpawnTime, eggSpawnCooldown);
        if (spaceship.level >= 5) {
            spawnTripleBullet(keys, bullets, spaceship, bulletTexture, shootSound, lastBulletTime, bulletCooldown);
        } else if (spaceship.level >= 3) {
            spawnDoubleBullet(keys, bullets, spaceship, bulletTexture, shootSound, lastBulletTime, bulletCooldown);
        } else {
            spawnBullet(keys, bullets, spaceship, bulletTexture, shootSound, currentTime, lastBulletTime, bulletCooldown);
        }

        spawnBonusBullet(bonusBullets,BonusBulletTexture,currentTime,lastBonusSpawnTime,bonusSpawnCooldown);
        bornChicken(chickens,chickenTexture,currentTime,lastChickenSpawnTime,chickenSpawnCooldown,chickenDirection);
        // sinh ra bom loại 1
        spawnBom(bom1s, bom2s, bom1Texture, bom2Texture, currentTime, lastBomTime, BomCooldown);
        spawnBoss(boss, currentTime, bossAppearTime);
        spawnBossBullet(boss, bossBullets, bossbulletTexture, currentTime, lastBossBulletTime, 1000);
        // di chuyển
        moveChicken(chickens,chickenDirection,0.1f,(float)10,800);
        
        for (auto& egg : eggs) {
            egg.move();
        }

        for (auto& bossbullet : bossBullets) {
            bossbullet.move();
        }

        for (auto& bonus : bonusBullets){
            bonus.move();
        }
        for (auto& bullet : bullets) {
            bullet.move();
        }

        for (auto& bom : bom1s){
            bom.move();
        }

        for (auto& bom : bom2s){
            bom.move();
        }
        // Xử lí va chạm Đạn và gà 
        BulletChickenCollision(bullets,chickens,score);

        // Xử lí va chạm Bom loại 1,2 voi spaceship
        Bom1Collision(bom1s,spaceship,running,died);

        bonusBulletCollision(bonusBullets,spaceship);

        Bom2Collision(bom2s,spaceship,running,died);

        // Xử lí va chạm chicken and spaceship
       ChickenCollision(chickens,spaceship,running,died);
       // xử lí va chạm tàu và trứng
       EggCollision(eggs,spaceship,running,died);
       BulletBossCollision(bullets,boss,2);
       BossBulletCollision(bossBullets, spaceship, running, died);


        // Xử lí va chạm Bullet and Bom1
        Bom1BulletCollision(bom1s, bullets);



        // Kiểm tra đạn ra khỏi màn hình chưa
        removeBullets(bullets);

        // Kiểm ra gà ra khỏi màn hình chưa
        removeChickens(chickens);
        // Kiểm tra ong ra khỏi màn hình chưa
        removeBonusBullet(bonusBullets);

        // Kiểm tra bom1 ra khỏi màn hình 
        removeBom1(bom1s);
        // Kiểm tra bom2 ra khỏi màn hình
        removeBom2(bom2s);
        // Kiểm tra trứng ra khỏi màn hình
        removeEggs(eggs);
        removeOutOfScreenBossBullets(bossBullets);

        SDL_Texture* currentScoreTexture = updateScoreTexture(renderer, font);
        updateBackground();  

        SDL_RenderClear(renderer);
        renderBackground(renderer, BackGroundTexture);
        SDL_RenderCopy(renderer, spaceship.texture, NULL, &spaceship.rect);
        renderText(renderer,font,highscoreText,20,40,textColor);
        if (boss.appeared) {
            boss.move(WINDOW_WIDTH);
            SDL_RenderCopy(renderer, boss.texture, NULL, &boss.rect);
            removeBoss(boss);
        }
        for (const auto& bullet : bullets) {
            SDL_RenderCopy(renderer, bullet.texture, NULL, &bullet.rect);
        }
        for (const auto& chicken : chickens) {
            SDL_RenderCopy(renderer, chicken.texture, NULL, &chicken.rect);
        }
        for (const auto& bonus : bonusBullets) {
            SDL_RenderCopy(renderer, bonus.texture, NULL, &bonus.rect);
        }
        for (const auto& bom : bom1s) {
            SDL_RenderCopy(renderer, bom.texture, NULL, &bom.rect);
        }
        for (const auto& bom : bom2s) {
            SDL_RenderCopy(renderer, bom.texture, NULL, &bom.rect);
        }
        for (const auto& egg : eggs) {
            SDL_RenderCopy(renderer, egg.texture, NULL, &egg.rect);
        }
        for (auto& bossbullet : bossBullets) {
            SDL_RenderCopy(renderer, bossbullet.texture, NULL, &bossbullet.rect);
        }
        if (currentScoreTexture != nullptr) {
            SDL_Rect scoreRect;
            scoreRect.x = 20;  // Vị trí hiển thị điểm
            scoreRect.y = 20;
            SDL_QueryTexture(currentScoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);
            SDL_RenderCopy(renderer, currentScoreTexture, NULL, &scoreRect);
        }
        if (ExitTime==0 && boss.Died()){
            lastBomTime = SDL_GetTicks();
            ExitTime = SDL_GetTicks();
        }
        if(ExitTime!=0 && SDL_GetTicks()- ExitTime >= 2000) running = false;
        SDL_RenderPresent(renderer);
    }
    Mix_HaltMusic();
    saveHighScore(score,highscore);
    SDL_RenderClear(renderer);
    if (died) {
        waitForEnterSDL(renderer,gameoverTexture);
    }
    else if (boss.Died()){
        Mix_PlayMusic(winSound, -1);
        waitForEnterSDL(renderer,victoryTexture);
        Mix_HaltMusic();
    }


    SDL_DestroyTexture(BackGroundTexture);
    SDL_DestroyTexture(spaceshipTexture);
    SDL_DestroyTexture(bom1Texture);
    SDL_DestroyTexture(bom2Texture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(BonusBulletTexture);
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyTexture(eggTexture);
    SDL_DestroyTexture(bossbulletTexture);
    SDL_DestroyTexture(introlTexture);
    SDL_DestroyTexture(gameoverTexture); 
    SDL_DestroyTexture(bossTexture);
    SDL_DestroyTexture(victoryTexture);           // Đóng hệ thống âm thanh
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    Mix_FreeMusic(bgMusic);      // Giải phóng nhạc nền
    Mix_FreeChunk(shootSound);
    Mix_FreeMusic(winSound);   // Giải phóng hiệu ứng âm thanh bắn đạn
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
