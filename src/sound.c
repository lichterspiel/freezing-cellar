#include "sound.h"



void initSounds(void)
{
    memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

    music = NULL;

    loadSounds();
}


static void loadSounds()
{
    sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("sound/player_laser.wav");

    sounds[SND_ALIEN_FIRE] = Mix_LoadWAV("sound/enemy_laser.wav");

    sounds[SND_PLAYER_DIE] = Mix_LoadWAV("sound/player_die.wav");

    sounds[SND_ALIEN_DIE] = Mix_LoadWAV("sound/enemy_die.wav");

    sounds[SND_POINTS] = Mix_LoadWAV("sound/pods.wav");
}

void loadMusic(char* filename)
{
    if (music != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }
    music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
    Mix_PlayChannel(channel, sounds[id], 0);
}
