#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "draw.h"
#include "food.h"
#include "window.h"

#define DELAY_IN_MS 30

int main(int argc, char* args[])
{
  // Initialize TTF
  TTF_Init();

  // Initialize SDL
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    // The window we'll be rendering to
    SDL_Window* window = WindowCreate();

    // Surface of the window
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // The snakes to play
    struct snake* snake = SnakeCreate();

    // The snakes to play
    struct food* food = FoodCreate();

    // For events on window
    SDL_Event event;

    /* - Game running loop - */
    int arrow = 0;
    int quit = 0;
    int score = 0;

    while(!quit) {
      // Draw the blocks of the level
      DrawTerrain(screenSurface);

      DrawExtra(screenSurface);

      // Draw the limits of the level
      DrawWalls(screenSurface);

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
      SnakeMove(snake, arrow);

      // Draw the snake in the screen
      SnakeDraw(screenSurface, snake);

      // If snake eat the food
      if(FoodInCollision(food, snake)) {
        food = FoodEat(food, snake);
        score++;
      }

      // Draw the actual food in the screen
      FoodDraw(screenSurface, food);

      // Draw the score
      DrawScore(screenSurface, score);

      // Update the changes in window
      SDL_UpdateWindowSurface(window);

      // Wait
      SDL_Delay(DELAY_IN_MS);
    }

    // Destroy the food
    food = FoodDestroy(food);

    // Destroy the snake
    snake = SnakeDestroy(snake);

    // Free the surface
    SDL_FreeSurface(screenSurface);

    // Destroy the window
    SDL_DestroyWindow(window);
  }

  // Exit TTF
  TTF_Quit();

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}