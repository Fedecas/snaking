#ifndef SNAKING_SOUND_H
#define SNAKING_SOUND_H

#include <SDL2/SDL_mixer.h>

#define SOUND_FREQ      MIX_DEFAULT_FREQUENCY // Frequency of audio
#define SOUND_FORMAT    MIX_DEFAULT_FORMAT    // The format of sound
#define SOUND_SIZE      2048                  // Size in bytes of each sample

#define SOUND_PATH  "assets/sounds/"  // Path for load sounds
#define SOUND_EXT   ".wav"            // Extension of sound files

typedef Mix_Chunk * sound_t;

sound_t EatSound;
sound_t GameOverSound;
sound_t GameRestartSound;

void SoundsInit();
/*
 * Initialize all sound files from the path
 */

void SoundPlay(sound_t sound);
/*
 * Play a sound in given channel
 */

void SoundStop();
/*
 * Stop a playing channel
 */

void SoundsQuit();
/*
 * Close a sound file opened
 */

#endif //SNAKING_SOUND_H