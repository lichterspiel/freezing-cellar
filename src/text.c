#include "text.h"

static SDL_Texture *fontTexture;
static char drawTextBuffer[MAX_LINE_LENGTH];

void initFonts()
{
    fontTexture = loadTexture("gfx/font.png");
}

void drawText(int x, int y, int r, int g, int b, char* format, ...)
{
    int i , len, c;
    SDL_Rect rect;
    va_list args;

    memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

    // format string
    va_start(args, format);
    vsprintf(drawTextBuffer, format, args);
    va_end(args);

    len = strlen(drawTextBuffer);

    // to get region of the font png
    rect.w = GLYPH_WIDTH;
    rect.h = GLYPH_HEIGHT;
    rect.y = 0;

    // set colour of font
    SDL_SetTextureColorMod(fontTexture, r, g, b);

    for (i = 0; i < len; i++)
    {
        c = drawTextBuffer[i];

        if (c >= ' ' && c <= 'Z')
        {
            // subtract by ' ' Space because the font textures first glyph is space
            // so that x coordinates match up to the texture
            rect.x = (c - ' ') * GLYPH_WIDTH;

            blitRect(fontTexture, &rect, x, y);

            x += GLYPH_WIDTH;
        }
    }
}
