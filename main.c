#include <SDL2/SDL.h>
#include <time.h>

#include "block.h"
#include "color.h"
#include "draw.h"
#include "food.h"
#include "window.h"

#define DELAY_IN_MS 30

int main(int argc, char* args[])
{
  // The window we'll be rendering to
  SDL_Window* window = NULL;

  // Surface of the window
  SDL_Surface* screenSurface = NULL;

  // For events on window
  SDL_Event event;

  // The snakes to play
  struct snake* snake = NULL;

  // The snakes to play
  struct food* food = NULL;

  //Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    // Create a window
    window = windowCreate(window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Initialize the surface of the window
    screenSurface = SDL_GetWindowSurface(window);

    // Create a snake
    snake = snakeCreate();

    // Create first food
    food = foodCreate();

    int arrow = 0;
    int quit = 0;
    int score = 0;

    int frames = 0;
    float seconds = 0;

    while(!quit) {
      clock_t start = clock();

      // Draw the blocks of the level
      drawSurface(screenSurface);

      // Draw the limits of the level
      drawLimits(screenSurface);

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

      // Move the snake according the last key pressed
      snakeMove(snake, arrow);

      // Draw the snake in the screen
      drawSnake(screenSurface, snake);

      // If snake eat the food
      if(foodInCollision(food, snake)) {
        food = foodEat(food, snake);
        score++;
        printf("SCORE: %d\n", score);
      }

      // Draw the actual food in the screen
      drawFood(screenSurface, food);

      // Update the changes in window
      SDL_UpdateWindowSurface(window);
      frames++;

      // Wait
      SDL_Delay(DELAY_IN_MS);

      clock_t end = clock();
      seconds = seconds + (float)(end - start) / CLOCKS_PER_SEC;

      if(seconds >= 1) {
        printf("FPS: %d\n", frames);
        frames = 0;
        seconds = 0;
      }
    }
  }

  // Destroy the food
  food = foodDestroy(food);

  // Destroy the snake
  snake = snakeDestroy(snake);

  SDL_FreeSurface(screenSurface);

  // Destroy the window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}