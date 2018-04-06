#include <SDL2/SDL.h>

#include "window.h"

SDL_Window* windowCreate (SDL_Window* window)
{
  window = SDL_CreateWindow(WINDOW_TITLE,
                            WINDOW_POSX, WINDOW_POSY,
                            WINDOW_WIDTH, (WINDOW_HEIGHT + (BLOCK_SIZE * WINDOW_EXTRA)),
                            SDL_WINDOW_SHOWN);

  if(window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  return window;
}