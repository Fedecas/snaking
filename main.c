#include <SDL2/SDL.h>

#include "color.h"
#include "draw.h"
#include "window.h"

#define DELAY_IN_MS 33

int main(int argc, char* args[])
{
  // The window we'll be rendering to
  SDL_Window* window = NULL;

  // Surface of the window
  SDL_Surface* screenSurface = NULL;

  // The snakes to play
  struct snake* snake = NULL;

  // For events on window
  SDL_Event event;

  // Create the color to paint
  SDL_Color color;

  //Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    // Create a window
    window = windowCreate(window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create a snake
    snake = snakeCreate();
    snakeIncrease(snake);
    snakeIncrease(snake);

    int arrow = 0;
    int quit = 0;

    while(!quit) {
      // Wait events in window/keyboard
      while(SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT: quit = 1; break;
          case SDL_WINDOWEVENT:
            switch (event.window.event) {
              case SDL_WINDOWEVENT_CLOSE: quit = 1; break;
              default: break;
            } break;
          case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
              case SDLK_ESCAPE: quit = 1; break;
              case SDLK_LEFT: arrow = DIRECTION_LEFT; break;
              case SDLK_RIGHT: arrow = DIRECTION_RIGHT; break;
              case SDLK_UP: arrow = DIRECTION_UP; break;
              case SDLK_DOWN: arrow = DIRECTION_DOWN; break;
              default: break;
            } break;
          default: break;
        }
      }

      color = colorBuild(255, 255, 255, 255); // White color

      // Set the surface color to white
      screenSurface = windowSurfaceColor(screenSurface, window, color);

      color = colorBuild(255, 0, 0, 255); // Red color

      // Draw the snake in the screen
      screenSurface = drawSnake(screenSurface, snake, color);

      // Move the snake according the last key pressed
      snakeMove(snake, arrow);

      // Update the changes in window
      SDL_UpdateWindowSurface(window);

      // Wait
      SDL_Delay(DELAY_IN_MS);
    }
  }

  // Destroy snake
  snakeDestroy(snake);

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
