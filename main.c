#include <time.h>

#include "block.h"
#include "draw.h"
#include "food.h"
#include "score.h"
#include "snake.h"
#include "terrain.h"
#include "wall.h"
#include "window.h"

#define OPTION_CONTINUE 0
#define OPTION_QUIT     1
#define OPTION_RESTART  2

#define DELAY_IN_MS 75

static void SleepMS(int timeinms)
{
  struct timespec timetosleep;

  timetosleep.tv_nsec = 1000 * 1000 * timeinms;
  timetosleep.tv_sec = 0;

  nanosleep(&timetosleep, NULL);
}

static int GameOver(window GameWindow, TTF_Font* font)
{
  // Draw "game over" text
  char* text = "GAME OVER";

  int fontwidth, fontheight;
  TTF_SizeText(font, text, &fontwidth, &fontheight);

  int textposX = (WINDOW_WIDTH / 2) - (fontwidth / 2);
  int textposY = (WINDOW_HEIGHT / 2) - fontheight;

  DrawText(GameWindow->surface, font, text, textposX, textposY, COLOR_SCORE);

  // Draw option quit button
  text = "QUIT";

  int buttonwidth = WINDOW_WIDTH / 6;
  int buttonheight = buttonwidth / 2;

  int buttonquitX = (WINDOW_WIDTH / 2) - (buttonwidth + buttonheight);
  int buttonquitY = textposY + buttonheight;

  DrawButton(GameWindow->surface, buttonquitX, buttonquitY,
             buttonwidth, buttonheight, COLOR_BLACK, text, COLOR_WHITE);

  // Draw option restart button
  text = "RESTART";

  int buttonrestartX = buttonquitX + (2 * buttonwidth);
  int buttonrestartY = textposY + buttonheight;

  DrawButton(GameWindow->surface, buttonrestartX, buttonrestartY,
             buttonwidth, buttonheight, COLOR_BLACK, text, COLOR_WHITE);

  WindowSurfaceUpdate(GameWindow);

  int quit = OPTION_CONTINUE;
  SDL_Event event;

  while(!quit) {
    while(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: quit = OPTION_QUIT; break;
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE: quit = OPTION_QUIT; break;
            default: break;
          } break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: quit = OPTION_QUIT; break;
            default: break;
          }
        /*
        case SDL_MOUSEMOTION: TODO ver drawinit, cambiar switch, funcion para la posicion del mouse
          if((event.motion.x >= buttonquitX) && (event.motion.x <= buttonquitX + buttonwidth)
            && (event.motion.y >= buttonquitY) && (event.motion.y <= buttonquitY + buttonheight)) {
            DrawButton(GameWindow->surface, buttonquitX, buttonquitY,
                       buttonwidth, buttonheight, COLOR_WHITE, "QUIT", COLOR_BLACK);
          } break;
        */
        case SDL_MOUSEBUTTONDOWN:
          if(event.button.button == SDL_BUTTON_LEFT) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if((mouseX >= buttonquitX) && (mouseX <= buttonquitX + buttonwidth)
               && (mouseY >= buttonquitY) && (mouseY <= buttonquitY + buttonheight)) {
              quit = OPTION_QUIT;
            } else if((mouseX >= buttonrestartX) && (mouseX <= buttonrestartX + buttonwidth)
                      && (mouseY >= buttonrestartY) && (mouseY <= buttonrestartY + buttonheight)) {
              quit = OPTION_RESTART;
            }
          } break;
        default: break;
      }
    }

    WindowSurfaceUpdate(GameWindow);

    SleepMS(DELAY_IN_MS);
  }

  return quit;
}

static void GameRestart(food ActualFood, snake PlayerSnake, score GameScore)
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
  TTF_Font* ScoreFont = DrawTextInit();

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
  int arrow = DIRECTION_NONE;
  int quit = OPTION_CONTINUE;

  // Draw the limits of the level
  WallsDraw(GameWindow->surface, LevelWalls);

  start:
  while(1) {
    clock_t start = clock();
    // Wait events in window/keyboard
    while(SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: quit = OPTION_QUIT; break;
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_CLOSE: quit = OPTION_QUIT; break;
            default: break;
          } break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: quit = OPTION_QUIT; break;
            case SDLK_LEFT: arrow = DIRECTION_LEFT; break;
            case SDLK_RIGHT: arrow = DIRECTION_RIGHT; break;
            case SDLK_UP: arrow = DIRECTION_UP; break;
            case SDLK_DOWN: arrow = DIRECTION_DOWN; break;
            default: break;
          } break;
        default: break;
      }
    }

    if(arrow > DIRECTION_NONE) {
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
      quit = GameOver(GameWindow, ScoreFont);
    }

    // If snake hit herself
    if(SnakeIsCollidingWithHerself(PlayerSnake)) {
      quit = GameOver(GameWindow, ScoreFont);
    }

    if(quit == OPTION_QUIT) {
      break;
    } else if(quit == OPTION_RESTART) {
      GameRestart(ActualFood, PlayerSnake, GameScore);
      arrow = DIRECTION_NONE;
      quit = OPTION_CONTINUE;
      goto start;
    }

    // Draw the blocks of the level
    TerrainDraw(GameWindow->surface, LevelTerrain);

    // Draw the snake in the screen
    SnakeDraw(GameWindow->surface, PlayerSnake);

    // Draw the actual food in the screen
    FoodDraw(GameWindow->surface, ActualFood);

    // Draw the score
    ScoreDraw(GameWindow->surface, ScoreFont, GameScore);

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
  DrawTextQuit(ScoreFont);

  // Destroy the window and her surface, quit SDL module
  WindowAndSurfaceQuit(GameWindow);

  return 0;
}