#include "input.h"


void doInput()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
                exit(0);
                break;

            default:
                break;
        }

    }
}

void movement(float* x, float* y)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_D])
    {
        *x += 10;
    }
    if (state[SDL_SCANCODE_A])
    {
        *x -= 10;
    }
    if (state[SDL_SCANCODE_W])
    {
        *y -= 10;
    }
    if (state[SDL_SCANCODE_S])
    {
        *y += 10;
    }
}
