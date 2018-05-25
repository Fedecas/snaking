#include "window.h"

struct _window_t {
    SDL_Window* context;
    surface_t surface;
};

void WindowAndSurfaceInit()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL video subsystem could not initialize! SDL_Error: %s\n", SDL_GetError());
  }

  SDL_Window* context = SDL_CreateWindow(WINDOW_TITLE,
                                         WINDOW_POSX, WINDOW_POSY,
                                         WINDOW_WIDTH, WINDOW_HEIGHT,
                                         SDL_WINDOW_BORDERLESS);

  if(context == NULL) {
    printf("[error] Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  surface_t surface = SDL_GetWindowSurface(context);

  if(surface == NULL) {
    printf("[error] Surface could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  GameWindow = (window_t) malloc(sizeof(struct _window_t));

  GameWindow->context = context;
  GameWindow->surface = surface;
}

surface_t WindowSurface()
{
  return (GameWindow->surface);
}

void WindowSurfaceUpdate()
{
  if(SDL_UpdateWindowSurface(GameWindow->context) == -1) {
    printf("[error] Surface could not be updated! SDL_Error: %s\n", SDL_GetError());
  }
}

void WindowAndSurfaceQuit()
{
  SDL_FreeSurface(GameWindow->surface);
  GameWindow->surface = NULL;

  SDL_DestroyWindow(GameWindow->context);
  GameWindow->context = NULL;

  free(GameWindow);
  GameWindow = NULL;

  SDL_Quit();
}