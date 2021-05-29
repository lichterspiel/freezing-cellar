#include "title.h"

static SDL_Texture* titleTexture;
static SDL_Texture* shooterTexture;
static int reveal = 0;
static int timeout;

void initTitle()
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    titleTexture = loadTexture("gfx/title.png");
    shooterTexture = loadTexture("gfx/shooter.png");

    timeout = FPS * 5;
}

static void logic(void)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    doBackground();

    doStarfield();

    if (reveal < SCREEN_HEIGHT)
    {
        reveal++;
    }

    if (--timeout <= 0)
    {
        //initHighscores();
    }

    if (state[SDL_SCANCODE_L])
    {
        initStage();
    }

}

static void draw()
{
    drawBackground();

    drawStarfield();

    drawLogo();


    if (timeout % 40 < 20)
    {
        drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "PRESS FIRE TO PLAY!");
    }


}

static void drawLogo()
{
    SDL_Rect r;

    r.x = 0;
    r.y = 0;

    SDL_QueryTexture(titleTexture, NULL, NULL, &r.w, &r.h);

    r.h = MIN(reveal, r.h);

    blitRect(titleTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 100);

    SDL_QueryTexture(shooterTexture, NULL, NULL, &r.w, &r.h);

    r.h = MIN(reveal, r.h);

    blitRect(shooterTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 250);
}
