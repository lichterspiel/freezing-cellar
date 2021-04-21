#include "common.h"

//outside functions
extern void blit(SDL_Texture* texture, int x, int y, float scale);
extern SDL_Texture* loadTexture(char* filename);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
extern void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

//prototype
static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer(void);
static void doFighters(void);
static void doBullets(void);
static void doEnemies(void);
static void drawFighters(void);
static void drawBullets(void);
static void spawnEnemies(void);
static int bulletHitFighter(Entity *b);
static void resetStage();
static void clipPlayer();
static void fireAlienBullet(Entity* e);
static void drawBackground(void);
static void initStarfield(void);
static void drawStarfield(void);
static void doBackground(void);
static void doStarfield(void);
static void drawExplosions(void);
static void doExplosions(void);
static void addExplosions(int x, int y, int num);
static void addDebris(Entity *e);
static void doDebris(void);
static void drawDebris(void);


// variables
static Entity *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *playerTexture;
static SDL_Texture* background;
static SDL_Texture* explosionTexture;
static int enemySpawnTimer;
static int stageResetTimer;
static int backgroundX;
static Star stars[MAX_STARS];


extern App app;
extern Stage stage;
