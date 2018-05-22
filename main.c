#include <time.h>

/* TODO
 * Ver includes
 * Sonidos
 * Sleep
 * Button y Handlers en main?
 * Fuente de buttons (y en general, se usa siempre la misma)
 * Uso de SDL en main
*/

#include "level/food.h"
#include "level/score.h"
#include "level/snake.h"
#include "level/terrain.h"
#include "level/wall.h"

#include "button.h"
#include "colors.h"
#include "handlers.h"

#define DELAY_IN_MS       75

static void SleepMS(int timeinms)
{
  struct timespec timetosleep;

  timetosleep.tv_nsec = 1000 * 1000 * timeinms;
  timetosleep.tv_sec = 0;

  nanosleep(&timetosleep, NULL);
}

static int GameOver(window_t GameWindow, TTF_Font* font, sound_t GameOverSound)
{
  SoundPlay(GameOverSound, 1);
  SDL_Surface* windowSurface = WindowSurface(GameWindow);

  // Draw "game over" text
  char* text = "GAME OVER";

  int fontwidth, fontheight;
  TTF_SizeText(font, text, &fontwidth, &fontheight);

  int textposX = (WINDOW_WIDTH / 2) - (fontwidth / 2);
  int textposY = (WINDOW_HEIGHT / 2) - fontheight;

  DrawText(windowSurface, font, text, textposX, textposY, COLOR_SCORE);

  // Draw the quit button
  int buttonwidth = WINDOW_WIDTH / 6;
  int buttonheight = buttonwidth / 2;

  int buttonquitX = (WINDOW_WIDTH / 2) - (buttonwidth + buttonheight);
  int buttonquitY = textposY + buttonheight;

  button_t buttonQuit = ButtonCreate(buttonquitX, buttonquitY,
                                     buttonwidth, buttonheight,
                                     COLOR_BLACK, COLOR_WHITE, "QUIT");

  int fontsize = (buttonwidth + buttonheight) / 10;
  TTF_Font* buttonfont = TTF_OpenFont(FONT_PATH, fontsize);

  // Draw the restart button
  int buttonrestartX = buttonquitX + (2 * buttonwidth);
  int buttonrestartY = textposY + buttonheight;

  button_t buttonRestart = ButtonCreate(buttonrestartX, buttonrestartY,
                                        buttonwidth, buttonheight,
                                        COLOR_BLACK, COLOR_WHITE, "RESTART");

  // Wait for response loop
  int quit = OPTION_CONTINUE;

  while(!quit) {
    HandleInputOption(&quit, buttonQuit, buttonRestart);

    ButtonDraw(windowSurface, buttonQuit, buttonfont);
    ButtonDraw(windowSurface, buttonRestart, buttonfont);

    WindowSurfaceUpdate(GameWindow);

    SleepMS(DELAY_IN_MS / 2);
  }

  ButtonDestroy(buttonQuit);
  ButtonDestroy(buttonRestart);

  TTF_CloseFont(buttonfont);

  SoundStop(1);

  return quit;
}

static void GameRestart(food_t* ActualFood, snake_t* PlayerSnake, score_t* GameScore)
{
  // Restart the snake
  SnakeDestroy(*PlayerSnake);
  *PlayerSnake = SnakeCreate();

  // Restart the food
  FoodDestroy(*ActualFood);
  *ActualFood = FoodCreate();

  // Restart the score
  ScoreDestroy(*GameScore);
  *GameScore = ScoreCreate();
}

int main(int argc, char* args[])
{
  // Init SDL, create the window and her surface
  window_t GameWindow = WindowAndSurfaceInit();

  // Initialize TTF module and the font for texts
  TTF_Font* ScoreFont = DrawTextInit();

  // Initialize the sounds to play
  sound_t IncreaseSound = SoundInit("SnakeIncrease");
  sound_t EatSound = SoundInit("SnakeEat");
  sound_t GameOverSound = SoundInit("GameOver");
  sound_t GameRestartSound = SoundInit("GameRestart");

  // Create the terrain to move
  terrain_t LevelTerrain = TerrainCreate();

  // Create the limits
  wall_t* LevelWalls = WallsCreate();

  // Create the snake for use
  snake_t PlayerSnake = SnakeCreate();

  // Create first food
  food_t ActualFood = FoodCreate();

  // Initialize the score
  score_t GameScore = ScoreCreate();

  /* - Game running loop - */
  int arrow = DIRECTION_NONE;
  int quit = OPTION_CONTINUE;

  start:
  while(1) {
    clock_t start = clock();
    // Wait events in window/keyboard
    HandleInputDirection(&quit, &arrow);

    /* React to event */
    // Move the snake according the last key pressed
    SnakeMove(PlayerSnake, arrow);

    // Snake eat the food if colliding it
    SnakeEat(PlayerSnake, &ActualFood, GameScore, IncreaseSound, EatSound);

    // If snake collide walls or her body, show lose menu
    if(SnakeCollidingWallOrBody(PlayerSnake, LevelWalls)) {
      quit = GameOver(GameWindow, ScoreFont, GameOverSound);
    }

    // Check if continue or quit the game
    switch (quit) {
      case OPTION_CONTINUE:
        break;
      case OPTION_QUIT:
        goto end;
      case OPTION_RESTART:
        GameRestart(&ActualFood, &PlayerSnake, &GameScore);
        SoundPlay(GameRestartSound, 1);
        arrow = DIRECTION_NONE;
        quit = OPTION_CONTINUE;
        goto start;
      default: break;
    }

    /* Draw game objects and wait */
    // Draw the base terrain
    TerrainDraw(WindowSurface(GameWindow), LevelTerrain);

    // Draw the limits of the level
    WallsDraw(WindowSurface(GameWindow), LevelWalls);

    // Draw the snake in the screen
    SnakeDraw(WindowSurface(GameWindow), PlayerSnake);

    // Draw the actual food in the screen
    FoodDraw(WindowSurface(GameWindow), ActualFood);

    // Draw the score
    ScoreDraw(WindowSurface(GameWindow), ScoreFont, GameScore);

    // Update the changes in surface
    WindowSurfaceUpdate(GameWindow);

    int diff = (int)((clock() - start) * 1000 / CLOCKS_PER_SEC);

    // Wait
    SleepMS(DELAY_IN_MS - diff);
  }
  end:

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

  // Close the sounds
  SoundQuit(GameRestartSound);
  SoundQuit(GameOverSound);
  SoundQuit(EatSound);
  SoundQuit(IncreaseSound);

  // Close the font opened and exit TTF module
  DrawTextQuit(ScoreFont);

  // Destroy the window and her surface, quit SDL module
  WindowAndSurfaceQuit(GameWindow);

  return 0;
}