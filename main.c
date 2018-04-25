#include <time.h>

#include "block.h"
#include "draw.h"
#include "food.h"
#include "score.h"
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

static int youlose(window GameWindow)
{
  int textposX = (BLOCKS_X * BLOCK_SIZE) / 2 - 125;
  int textposY = (BLOCKS_Y * BLOCK_SIZE) / 2 - 25;

  SDL_Rect button1 = {WINDOW_WIDTH / 2 - 300, textposY + 100, 200, 100};
  SDL_FillRect(GameWindow->surface, &button1, 0);

  SDL_Rect button2 = {WINDOW_WIDTH / 2 + 100, textposY + 100, 200, 100};
  SDL_FillRect(GameWindow->surface, &button2, 0);

  TTF_Font* losefont = TTF_OpenFont(FONT_DIR, FONT_SIZE);
  SDL_Surface* textSurface = TTF_RenderText_Solid(losefont, "YOU LOSE", COLOR_SCORE);
  SDL_Rect textLocation = {textposX, textposY, 0, 0};
  SDL_BlitSurface(textSurface, NULL, GameWindow->surface, &textLocation);

  TTF_Font* buttonsfont = TTF_OpenFont(FONT_DIR, BLOCK_SIZE + BLOCK_SIZE / 4);
  textSurface = TTF_RenderText_Solid(buttonsfont, "SALIR", mk_SDL_Color(255, 255, 255, 255));
  textLocation.x = button1.x + button1.w / 2 - BLOCK_SIZE * 2;
  textLocation.y = button1.y + BLOCK_SIZE + BLOCK_SIZE / 4;
  SDL_BlitSurface(textSurface, NULL, GameWindow->surface, &textLocation);

  textSurface = TTF_RenderText_Solid(buttonsfont, "REINICIAR", mk_SDL_Color(255, 255, 255, 255));
  textLocation.x = button2.x + BLOCK_SIZE / 2;
  textLocation.y = button2.y + BLOCK_SIZE + BLOCK_SIZE / 4;
  SDL_BlitSurface(textSurface, NULL, GameWindow->surface, &textLocation);

  WindowSurfaceUpdate(GameWindow);

  int quit = 0;
  SDL_Event event;

  while(!quit) {
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
            default: break;
          }
        case SDL_MOUSEBUTTONDOWN:
          if(event.button.button == SDL_BUTTON_LEFT) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if((mouseX >= button1.x) && (mouseX <= button1.x + button1.w)
               && (mouseY >= button1.y) && (mouseY <= button1.y + button1.h)) {
              quit = 1;
            } else if((mouseX >= button2.x) && (mouseX <= button2.x + button2.w)
                      && (mouseY >= button2.y) && (mouseY <= button2.y + button2.h)) {
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
  TTF_CloseFont(buttonsfont);

  return quit;
}

static void restart(food ActualFood, snake PlayerSnake, score GameScore)
{
  // Restart the food
  FoodDestroy(ActualFood);
  ActualFood = FoodCreate();

  // Restart the snake
  SnakeDestroy(PlayerSnake);
  PlayerSnake = SnakeCreate();

  // Restart the score
  ScoreDestroy(GameScore);
  GameScore = ScoreInit();
}

int main(int argc, char* args[])
{
  // Init SDL, create the window and her surface
  window GameWindow = WindowAndSurfaceInit();

  // Initialize TTF module and the font for texts
  TTF_Font* font = DrawTextInit();

  // Create the terrain to move
  terrain LevelTerrain = TerrainCreate();

  // Create the limits
  wall* LevelWalls = WallsCreate();

  // Create the snake for use
  snake PlayerSnake = SnakeCreate();

  // Create first food
  food ActualFood = FoodCreate();

  // Initialize the score
  score GameScore = ScoreInit();

  // For events on window
  SDL_Event event;

  /* - Game running loop - */
  int arrow = 0;
  int quit = 0;

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

    if(arrow > 0) {
      // Move the snake according the last key pressed
      SnakeMove(PlayerSnake, arrow);
    }

    // If snake eat the food
    if(SnakeIsCollidingWithFood(PlayerSnake, ActualFood)) {
      int newsnakehunger = PlayerSnake->hunger - 1;

      if(newsnakehunger <= 0) {
        SnakeIncrease(PlayerSnake);

        newsnakehunger = newsnakehunger + SNAKE_HUNGER;
      }

      PlayerSnake->hunger = newsnakehunger;

      FoodDestroy(ActualFood);
      ActualFood = FoodCreate();

      ScoreIncrease(GameScore);
    }

    // If snake collide with some wall
    if(SnakeIsCollidingWithWall(PlayerSnake, LevelWalls)) {
      quit = youlose(GameWindow);
    }

    // If snake hit herself
    if(SnakeIsCollidingWithHerself(PlayerSnake)) {
      quit = youlose(GameWindow);
    }

    if(quit == 1) {
      break;
    } else if(quit == 2) {
      restart(ActualFood, PlayerSnake, GameScore);
      arrow = 0;
      quit = 0;
      goto start;
    }

    // Draw the blocks of the level
    TerrainDraw(GameWindow->surface, LevelTerrain);

    // Draw the limits of the level
    WallsDraw(GameWindow->surface, LevelWalls);

    // Draw the snake in the screen
    SnakeDraw(GameWindow->surface, PlayerSnake);

    // Draw the actual food in the screen
    FoodDraw(GameWindow->surface, ActualFood);

    // Draw the score
    ScoreDraw(GameWindow->surface, font, GameScore);

    // Update the changes in surface
    WindowSurfaceUpdate(GameWindow);

    float diff = (float)(clock() - start) * 1000 / CLOCKS_PER_SEC;

    // Wait
    SleepMS(DELAY_IN_MS - (int)diff);
  }

  // Destroy the score
  ScoreDestroy(GameScore);

  // Destroy the food
  FoodDestroy(ActualFood);

  // Destroy the snake
  SnakeDestroy(PlayerSnake);

  // Destroy the walls
  WallsDestroy(LevelWalls);

  // Destroy the terrain
  TerrainDestroy(LevelTerrain);

  // Close the font opened and exit TTF module
  DrawTextQuit(font);

  // Destroy the window and her surface, quit SDL module
  WindowAndSurfaceQuit(GameWindow);

  return 0;
}