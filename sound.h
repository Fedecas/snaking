#ifndef SNAKE_SOUND_H
#define SNAKE_SOUND_H

#include <SDL2/SDL_mixer.h>

#define SOUND_FREQ      MIX_DEFAULT_FREQUENCY // Frequency of audio
#define SOUND_FORMAT    MIX_DEFAULT_FORMAT    // The format of sound
#define SOUND_CHANNELS  MIX_DEFAULT_CHANNELS  // Number of channels to play sound simultaneously
#define SOUND_SIZE      2048                  // Size in bytes of each sample

#define SOUND_PATH  "assets/sounds/"  // Path for load sounds
#define SOUND_EXT   ".wav"            // Extension of sound files

typedef Mix_Chunk * sound_t;

sound_t SoundInit(char* name);
/*
 * Initialize a sound file from the path
 */

void SoundPlay(sound_t sound, int channel);
/*
 * Play a sound in given channel
 */

void SoundStop(int channel);
/*
 * Stop a playing channel
 */

sound_t SoundQuit(sound_t sound);
/*
 * Close a sound file opened
 */

#endif //SNAKE_SOUND_H