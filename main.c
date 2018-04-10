#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <time.h>

#include "draw.h"
#include "food.h"
#include "window.h"

#define DELAY_IN_MS 75

static void sleepms(int timeinms)
{
  struct timespec timetosleep;

  timetosleep.tv_nsec = timeinms * (1000 * 1000);
  timetosleep.tv_sec = 0;

  nanosleep(&timetosleep, NULL);
}

int main(int argc, char* args[])
{
  // Initialize TTF module
  TTF_Init();

  // Initialize SDL module
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    // Init the window to render
    SDL_Window* window = WindowCreate();

    // Init the surface of window
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    // Initialize the font for texts
    TTF_Font* font = DrawTextInit();

    // Create the snake for use
    struct snake* snake = SnakeCreate();

    // Create first food
    struct food* food = FoodCreate();

    // For events on window
    SDL_Event event;

    /* - Game running loop - */
    int arrow = 0;
    int quit = 0;
    int score = 0;

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

      // Move the snake according the last key pressed
      SnakeMove(snake, arrow);

      // If snake eat the food
      if(FoodInCollision(food, snake)) {
        food = FoodEat(food, snake);
        score++;
      }

      // Draw the blocks of the level
      DrawTerrain(surface);

      // Draw the limits of the level
      DrawWalls(surface);

      // Draw the actual food in the screen
      FoodDraw(surface, food);

      // Draw the snake in the screen
      SnakeDraw(surface, snake);

      // Draw the score
      DrawScore(surface, font, score);

      // Update the changes in surface
      SDL_UpdateWindowSurface(window);

      // Wait
      sleepms(DELAY_IN_MS);
    }

    // Destroy the food
    FoodDestroy(food);

    // Destroy the snake
    SnakeDestroy(snake);

    // Close the font opened
    TTF_CloseFont(font);

    // Free the screen surface
    SDL_FreeSurface(surface);

    // Destroy the window
    SDL_DestroyWindow(window);
  }

  // Exit TTF
  TTF_Quit();

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}