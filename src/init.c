#include "init.h"

void initSDL()
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = SDL_WINDOW_SHOWN;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("could not initialize SDL %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if (!app.window)
    {
        printf("Failed to open window %s", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer)
    {
        printf("Failed to create Renderer %s\n", SDL_GetError());
        exit(1);
    }

    // init audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Could not initialize SDL Mixer \n");
        exit(1);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);
}

void initGame(void)
{
	initBackground();

	initStarfield();

	initSounds();

	initFonts();

	memset(&stage, 0, sizeof(Stage));

}

void cleanup()
{
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}
