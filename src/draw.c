#include "draw.h"

void prepareScene()
{
    // set color darkish green
    SDL_SetRenderDrawColor(app.renderer, 57, 148, 149, 255);

    // clear screen
    SDL_RenderClear(app.renderer);
}

void presentScene()
{
    SDL_RenderPresent(app.renderer);
}

SDL_Texture* loadTexture(char* filename)
{
    SDL_Texture* texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    texture = IMG_LoadTexture(app.renderer, filename);

    return texture;

}

void blit(SDL_Texture* texture, int x, int y, float scale)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;

    // get the dimensions of the texture and put it to the width and height of the rect
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    // scale pixture
    dest.h *= scale;
    dest.w *= scale;

    // actually render it to the screen the dest says where it should be rendered
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
   // SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    //SDL_RenderDrawRect(app.renderer, &dest);
}

void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(app.renderer, texture, src, &dest);
}
