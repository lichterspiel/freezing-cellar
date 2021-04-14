#include "common.h"

extern void cleanup();
extern void initSDL();
extern void prepareScene();
extern void presentScene();
extern void doInput();
extern SDL_Texture* loadTexture(char*);
extern void blit(SDL_Texture*, int, int, float);
extern void movement(float*, float*);

App app;
Entity player;
