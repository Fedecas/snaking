#include <SDL2/SDL.h>

#include "window.h"

SDL_Window* windowCreate (SDL_Window* window, int posX, int posY, int width, int height)
{
  // Create window
  window = SDL_CreateWindow("snake test", posX, posY, width, height, SDL_WINDOW_SHOWN);

  if(window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  return window;
}

SDL_Surface* windowSurfaceColor (SDL_Surface* screenSurface, SDL_Window* window, SDL_Color color)
{
  // Get window surface
  screenSurface = SDL_GetWindowSurface(window);

  // Fill the surface white
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, color.r, color.g, color.b));

  // Update the surface
  SDL_UpdateWindowSurface(window);

  return screenSurface;
}
