#include <SDL2/SDL.h>

#include "color.h"

SDL_Color colorBuild(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  SDL_Color color;

  color.r = red;
  color.g = green;
  color.b = blue;
  color.a = alpha;

  return color;
}