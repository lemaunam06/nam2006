#ifndef GAME_H
#define GAME_H
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>
using namespace std;
extern SDL_Texture* scoreTexture; // Chỉ là khai báo
extern int score;                 // Chỉ là khai báo
extern int lastScore;
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const string WINDOW_TITLE;

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font);            // Chỉ là khai báo
void showMenu(SDL_Renderer* renderer, SDL_Texture* introlTexture, Mix_Music* menuMusic);
SDL_Texture* updateScoreTexture(SDL_Renderer* renderer, TTF_Font* font);
void saveHighScore(const int &score, const int highscore);
int loadHighScore();
void renderText(SDL_Renderer* renderer, TTF_Font* font, const string& text, int x, int y, SDL_Color color);
void waitForEnterSDL(SDL_Renderer *renderer, SDL_Texture *victoryTexture);
void renderHearts(SDL_Renderer* renderer, int hp, SDL_Texture* heartTexture);
#endif
