#include "common.h"

extern void cleanup();
extern void initSDL();
extern void initStage();
extern void prepareScene();
extern void presentScene();
extern void doInput();

static void capFrameRate(long *then, float *remainder);

App app;
Stage stage;
