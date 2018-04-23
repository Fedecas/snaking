#include "window.h"

window WindowAndSurfaceInit()
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
    printf("[error] Surface could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  window GameWindow = malloc(sizeof(struct window));

  GameWindow->context = context;
  GameWindow->surface = surface;

  return GameWindow;
}

void WindowSurfaceUpdate(window GameWindow)
{
  SDL_UpdateWindowSurface(GameWindow->context);
}

window WindowAndSurfaceQuit(window GameWindow)
{
  SDL_FreeSurface(GameWindow->surface);
  GameWindow->surface = NULL;

  SDL_DestroyWindow(GameWindow->context);
  GameWindow->context = NULL;

  free(GameWindow);
  GameWindow = NULL;

  SDL_Quit();

  return GameWindow;
}