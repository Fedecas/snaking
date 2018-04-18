#include <time.h>

#include "block.h"
#include "draw.h"
#include "food.h"
#include "snake.h"
#include "terrain.h"
#include "wall.h"
#include "window.h"

#define DELAY_IN_MS 75

static void SleepMS(int timeinms)
{
  struct timespec timetosleep;

  timetosleep.tv_nsec = 1000 * 1000 * timeinms;
  timetosleep.tv_sec = 0;

  nanosleep(&timetosleep, NULL);
}

static int youlose(window* GameWindow, food food, TTF_Font* font, terrain* terrain)
{
  SDL_Rect button_quit = {0, 0, 100, 100};
  SDL_FillRect(GameWindow->surface, &button_quit, 0);
  SDL_Rect button_restart = {WINDOW_WIDTH - 100, 0, 100, 100};
  SDL_FillRect(GameWindow->surface, &button_restart, 0);
  int textposX = (BLOCKS_X * BLOCK_SIZE) / 2 - 125;
  int textposY = (BLOCKS_Y * BLOCK_SIZE) / 2 - 25;
  TTF_Font* losefont = TTF_OpenFont(FONT_DIR, FONT_SIZE);
  SDL_Surface* textSurface = TTF_RenderText_Solid(losefont, "YOU LOSE", COLOR_RED);
  SDL_Rect textLocation = {textposX, textposY, 0, 0};
  SDL_BlitSurface(textSurface, NULL, GameWindow->surface, &textLocation);

  WindowSurfaceUpdate(GameWindow);

  int quit = 0;
  SDL_Event event;

  while(!quit) {
    while(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
          if(event.button.button == SDL_BUTTON_LEFT) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            printf("(%d, %d)\n", mouseX, mouseY);

            if((mouseX >= 0) && (mouseX <= 100) && (mouseY >= 0) && (mouseY <= 100)) {
              quit = 1;
            } else if((mouseX >= WINDOW_WIDTH - 100) && (mouseX <= WINDOW_WIDTH) && (mouseY >= 0) && (mouseY <= 100)) {
              quit = 2;
            }
          } break;
        default: break;
      }
    }

    SleepMS(DELAY_IN_MS);
  }

  SDL_FreeSurface(textSurface);

  TTF_CloseFont(losefont);

  return quit;
}

static void restart(food food, snake snake, wall wall1, wall wall2, wall wall3, wall wall4,
                    terrain* terrain, TTF_Font* font, window* window)
{
  food = FoodDestroy(food);
  food = FoodCreate();

  snake = SnakeDestroy(snake);
  snake = SnakeCreate();
}

int main(int argc, char* args[])
{
  // Init SDL, create the window and her surface
  window* window = WindowAndSurfaceInit();

  // Initialize TTF module and the font for texts
  TTF_Font* font = DrawTextInit();

  // Create the terrain to move
  terrain* terrain = TerrainCreate();

  // Create the limits
  wall wall1 = WallCreate(BLOCKS_Y - 1, 0, 0, WALL_VERTICAL);
  wall wall2 = WallCreate(BLOCKS_Y - 1, BLOCKS_X - 1, 1, WALL_VERTICAL);
  wall wall3 = WallCreate(BLOCKS_X - 1, 1, 0, WALL_HORIZONTAL);
  wall wall4 = WallCreate(BLOCKS_X - 1, 0, BLOCKS_Y - 1, WALL_HORIZONTAL);

  // Create the snake for use
  snake PlayerSnake = SnakeCreate();

  // Create first food
  food ActualFood = FoodCreate();

  // For events on window
  SDL_Event event;

  /* - Game running loop - */
  int arrow = 0;
  int quit = 0;
  int score = 0;

  start:
  while(1) {
    clock_t start = clock();
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
    SnakeMove(PlayerSnake, arrow);

    // If snake eat the food
    if(SnakeIsCollidingWithFood(PlayerSnake, ActualFood)) {
      int newsnakehunger = PlayerSnake->hunger - ActualFood->calories;

      if(newsnakehunger <= 0) {
        SnakeIncrease(PlayerSnake);

        newsnakehunger = newsnakehunger + SNAKE_HUNGER;
      }

      PlayerSnake->hunger = newsnakehunger;

      FoodDestroy(ActualFood);
      ActualFood = FoodCreate();

      score++;
    }

    // If snake hit herself
    if(SnakeIsCollidingWithHerself(PlayerSnake)) {
      printf("YOU LOSE\n");
    }

    // If snake collide with some wall
    if(arrow > 0 && arrow == SnakeIsCollidingWithWall(PlayerSnake, wall1, wall2, wall3, wall4)) {
      printf("YOU LOSE\n");
      quit = youlose(window, ActualFood, font, terrain);
    }

    if(quit == 1) {
      break;
    } else if(quit == 2) {
      restart(ActualFood, PlayerSnake, wall1, wall2, wall3, wall4, terrain, font, window);
      arrow = 0;
      quit = 0;
      score = 0;
      goto start;
    }

    // Draw the blocks of the level
    TerrainDraw(window->surface, terrain);

    // Draw the limits of the level
    WallDraw(window->surface, wall1);
    WallDraw(window->surface, wall2);
    WallDraw(window->surface, wall3);
    WallDraw(window->surface, wall4);

    // Draw the actual food in the screen
    FoodDraw(window->surface, ActualFood);

    // Draw the snake in the screen
    SnakeDraw(window->surface, PlayerSnake);

    // Draw the score
    DrawScore(window->surface, font, score);

    // Update the changes in surface
    WindowSurfaceUpdate(window);

    float diff = (float)(clock() - start) * 1000 / CLOCKS_PER_SEC;

    // Wait
    SleepMS(DELAY_IN_MS - (int)diff);
  }

  // Destroy the food
  FoodDestroy(ActualFood);

  // Destroy the snake
  SnakeDestroy(PlayerSnake);

  // Destroy the walls
  WallDestroy(wall1);
  WallDestroy(wall2);
  WallDestroy(wall3);
  WallDestroy(wall4);

  // Destroy the terrain
  TerrainDestroy(terrain);

  // Close the font opened and exit TTF module
  DrawTextQuit(font);

  // Destroy the window and her surface, quit SDL module
  WindowAndSurfaceQuit(window);

  return 0;
}