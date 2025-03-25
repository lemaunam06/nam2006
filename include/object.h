#ifndef OBJECT_H
#define OBJECT_H
#include <SDL.h>
#include <SDL_image.h>

struct Egg {
    SDL_Rect rect;
    float posY;
    float speed;
    SDL_Texture* texture;

    Egg(int x, int y, SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
};


struct Chicken {
    SDL_Rect rect;
    SDL_Texture* texture;
    float posX, posY;
    int direction;
    Chicken(SDL_Texture* tex);
    bool isOutOfScreen();
};

struct BonusBullet {
    SDL_Rect rect;
    SDL_Texture* texture;
    float speedy,posY,posX;
    BonusBullet(SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
};

struct Boss {
    SDL_Rect rect;
    SDL_Texture* texture;
    float speedX,posX;
    int bossHp;
    bool appeared = false; 
    Boss(SDL_Texture* tex);
    void move(const int &windowWidth);
    bool Died();
};

struct BossBullet {
    SDL_Rect rect;
    float posY;
    float speed;
    SDL_Texture* texture;

    BossBullet(int x, int y, SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
};

struct Bullet {
    SDL_Rect rect;
    SDL_Texture* texture;
    float posX, posY;
    static float speed;
    Bullet(int x, int y, SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
};

struct Spaceship {
    SDL_Texture* texture;
    SDL_Rect rect;
    int level;
    float speed, posX, posY;
    Spaceship();
    void move(SDL_Event& event);
};

struct Bom1 {
    SDL_Rect rect;
    SDL_Texture* texture;
    float speed, posY;
    Bom1(SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
    int hitCount;
};

struct Bom2 {
    SDL_Rect rect;
    SDL_Texture* texture;
    float v, a, posY;
    Bom2(SDL_Texture* tex);
    void move();
    bool isOutOfScreen();
};




#endif
