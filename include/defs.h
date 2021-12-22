

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

#define PLAYER_SPEED          4
#define PLAYER_BULLET_SPEED   20

#define MAX_KEYBOARD_KEYS 350

#define SIDE_PLAYER 0
#define SIDE_ALIEN  1

#define FPS 60
#define ALIEN_BULLET_SPEED 8

#define MAX_STARS 500

#define MAX_LINE_LENGTH 1024

// number of sound effects thath can be played at same time
#define MAX_SND_CHANNELS 8

// specify channel which sound will play
enum
{
    CH_ANY = -1,
    CH_PLAYER,
    CH_POINTS,
    CH_ALIEN_FIRE
};

// to identify which sound effect
enum
{
    SND_PLAYER_FIRE,
    SND_ALIEN_FIRE,
    SND_PLAYER_DIE,
    SND_ALIEN_DIE,
    SND_POINTS,
    SND_MAX
};

enum
{
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};
