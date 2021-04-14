#include "main.h"

int main(int argc, char* argv[])
{
    // clear app/player object
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));

    initSDL();

    player.x = 100;
    player.y = 100;
    player.texture = loadTexture("bulb.png");

    // pointer to coordinates of player
    float* x = &player.x;
    float* y = &player.y;

    atexit(cleanup);

    while(1)
    {
        prepareScene();

        doInput();

        movement(x, y);

        blit(player.texture, player.x, player.y, 0.25);

        presentScene();

        SDL_Delay(16);
    }

    return 0;
}
