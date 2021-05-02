typedef struct Entity Entity;
typedef struct Explosion Explosion;
typedef struct Debris Debris;

struct Explosion
{
    float x;
    float y;
    float dx;
    float dy;
    int r, g, b, a;
    Explosion* next;
};

 struct Debris
{
    float x;
    float y;
    float dx;
    float dy;
    SDL_Rect rect;
    SDL_Texture* texture;
    int life;
    Debris* next;
};

typedef struct{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;


typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
    Delegate delegate;
    int fire;
} App;

struct Entity {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int health;
    int reload;
    int side;
    SDL_Texture* texture;
    Entity* next;
};

// linked lists
typedef struct {
    Entity fighterHead, *fighterTail;
    Entity bulletHead, *bulletTail;
    Explosion explosionHead, *explosionTail;
    Debris debrisHead, *debrisTail;
    int score;
} Stage;

typedef struct
{
    int x;
    int y;
    int speed;
} Star;
