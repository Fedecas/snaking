#include <SDL2/SDL.h>

#include "sound.h"

static sound_t SoundInit(char* SoundName)
{
  if(SDL_Init(SDL_INIT_AUDIO) < 0) {
    printf("SDL audio subsystem could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  if(Mix_OpenAudio(SOUND_FREQ, SOUND_FORMAT, SOUND_CHANNELS, SOUND_SIZE) < 0) {
    printf("Failed to open audio! Mix_Error: %s\n", Mix_GetError());
  }

  char SoundPath[30] = SOUND_PATH;
  strcat(SoundPath, SoundName);
  strcat(SoundPath, SOUND_EXT);

  sound_t GameSound = Mix_LoadWAV(SoundPath);

  if(GameSound == NULL) {
    printf("Failed to load sound effect! Mix_Error: %s\n", Mix_GetError());
  }
}

void SoundsInit()
{
  EatSound = SoundInit("SnakeEat");
  GameOverSound = SoundInit("GameOver");
  GameRestartSound = SoundInit("GameRestart");
}

void SoundPlay(sound_t GameSound)
{
  Mix_PlayChannel(0, GameSound, 0);
}

void SoundStop()
{
  Mix_HaltChannel(0);
}

static sound_t SoundQuit(sound_t GameSound)
{
  Mix_FreeChunk(GameSound);
  GameSound = NULL;

  return GameSound;
}

void SoundsQuit()
{
  EatSound = SoundQuit(EatSound);
  GameOverSound = SoundQuit(GameOverSound);
  GameRestartSound = SoundQuit(GameRestartSound);

  Mix_CloseAudio();
  Mix_Quit();
}