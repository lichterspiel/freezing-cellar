typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} App;

typedef struct {
    float x;
    float y;
    SDL_Texture* texture;
} Entity;
