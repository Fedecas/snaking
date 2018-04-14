#include "window.h"

window* WindowAndSurfaceInit()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  SDL_Window* context = SDL_CreateWindow(WINDOW_TITLE,
                            WINDOW_POSX, WINDOW_POSY,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_BORDERLESS);

  if(context == NULL) {
    printf("[error] Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  SDL_Surface* surface = SDL_GetWindowSurface(context);

  if(surface == NULL) {
    printf("[error] Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  window* window = malloc(sizeof(struct window));

  window->context = context;
  window->surface = surface;

  return window;
}

void WindowSurfaceUpdate(window* window)
{
  SDL_UpdateWindowSurface(window->context);
}

window* WindowAndSurfaceQuit(window* window)
{
  SDL_FreeSurface(window->surface);
  window->surface = NULL;

  SDL_DestroyWindow(window->context);
  window->context = NULL;

  free(window);
  window = NULL;

  SDL_Quit();

  return window;
}