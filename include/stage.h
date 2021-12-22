#include "common.h"

//outside functions
extern void addHighscore(int score);
extern void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
extern void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern void doBackground(void);
extern void doStarfield(void);
extern void drawBackground(void);
extern void blit(SDL_Texture* texture, int x, int y, float scale);
extern void drawStarfield(void);
extern void drawText(int x, int y, int r, int g, int b, int align, char *format, ...);
extern void initHighscores(void);
extern SDL_Texture *loadTexture(char *filename);
extern void playSound(int id, int channel);

//prototype
static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer(void);
static void doFighters(void);
static void doBullets(void);
static void drawFighters(void);
static void drawBullets(void);
static void spawnEnemies(void);
static int bulletHitFighter(Entity *b);
static void doEnemies(void);
static void fireAlienBullet(Entity *e);
static void clipPlayer(void);
static void resetStage(void);
static void drawExplosions(void);
static void doExplosions(void);
static void addExplosions(int x, int y, int num);
static void addDebris(Entity *e);
static void doDebris(void);
static void drawDebris(void);
static void drawHud(void);
static void doPointsPods(void);
static void drawPointsPods(void);
static void addPointsPod(int x, int y);

// variables
static Entity *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *playerTexture;
static SDL_Texture* background;
static SDL_Texture* explosionTexture;
static SDL_Texture* pointsTexture;
static int enemySpawnTimer;
static int stageResetTimer;
static int backgroundX;
static Star stars[MAX_STARS];
static int highscore;

extern App app;
extern Stage stage;
