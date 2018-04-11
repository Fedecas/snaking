#include <SDL2/SDL.h>

#include "window.h"

SDL_Window* WindowCreate()
{
  SDL_Window* window = NULL;

  window = SDL_CreateWindow(WINDOW_TITLE,
                            WINDOW_POSX, WINDOW_POSY,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_BORDERLESS);

  if(window == NULL) {
    printf("[error] Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  return window;
}