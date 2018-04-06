#include <SDL2/SDL.h>

#include "window.h"

SDL_Window* windowCreate (SDL_Window* window, int width, int height)
{
  window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  if(window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  return window;
}