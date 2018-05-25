#include <time.h>

/* TODO
 * Ver includes
 * Uso de SDL en main
*/

#include "engine/handlers.h"

#include "level/food.h"
#include "level/score.h"
#include "level/snake.h"
#include "level/terrain.h"
#include "level/wall.h"

#include "colors.h"

#define SLEEP_DEFAULT   75

int sleep_in_ms;

static void Sleep()
{
  struct timespec timetosleep;

  timetosleep.tv_nsec = 1000 * 1000 * sleep_in_ms;
  timetosleep.tv_sec = 0;

  nanosleep(&timetosleep, NULL);
}

static int GameOver()
{
  SoundPlay(GameOverSound);

  // Create 'ButtonQuit' and 'ButtonRestart'
  ButtonsCreate();

  // Init 'ButtonFont'
  FontInitButton();

  // Draw "game over" text
  int fontwidth, fontheight;
  TTF_SizeText(ScoreFont, "GAME OVER", &fontwidth, &fontheight);

  int textposX = (WINDOW_WIDTH / 2) - (fontwidth / 2);
  int textposY = (WINDOW_HEIGHT / 2) - fontheight;

  DrawText(ScoreFont, "GAME OVER", textposX, textposY, COLOR_SCORE);

  // Wait for response loop
  quit = OPTION_CONTINUE;
  sleep_in_ms /= 2;

  while(!quit) {
    HandleInputOption();

    ButtonsDraw();

    WindowSurfaceUpdate();

    Sleep();
  }

  sleep_in_ms = SLEEP_DEFAULT;

  FontQuitButton();
  ButtonsDestroy();
  SoundStop();

  return quit;
}

static void GameRestart()
{
  SoundPlay(GameRestartSound);

  // Restart the snake
  SnakeDestroy();
  SnakeCreate();

  // Restart the food
  FoodDestroy();
  FoodCreate();

  // Restart the score
  ScoreRestart();

  arrow = DIRECTION_NONE;
  quit = OPTION_CONTINUE;
}

int main(void)
{
  // Init SDL, create the window and her surface
  WindowAndSurfaceInit();

  // Initialize TTF module and the font for texts
  FontInitModuleAndScore();

  // Initialize the sounds to play
  SoundsInit();

  // Create the terrain to move
  TerrainCreate();

  // Create the limits
  WallsCreate();

  // Create the snake for use
  SnakeCreate();

  // Create first food
  FoodCreate();

  // Initialize the score
  ScoreRestart();

  /* - Game running loop - */
  arrow = DIRECTION_NONE;
  quit = OPTION_CONTINUE;

  start:
  while(1) {
    sleep_in_ms = SLEEP_DEFAULT;
    clock_t start = clock();

    // Check for events in window/keyboard
    HandleInputDirection();

    // Move the snake according the last key pressed
    SnakeMove();

    // Snake eat the food if correspond
    SnakeEat();

    // If snake collide walls or her body, the game is over D:
    if(SnakeCollidingWallOrBody()) {
      quit = GameOver();
    }

    // Check if continue or quit the game
    switch (quit) {
      case OPTION_CONTINUE:
        break;
      case OPTION_QUIT:
        goto end;
      case OPTION_RESTART:
        GameRestart();
        goto start;
      default: break;
    }

    /* Draw game objects and wait */
    // Draw the base terrain
    TerrainDraw();

    // Draw the limits of the level
    WallsDraw();

    // Draw the snake in the screen
    SnakeDraw();

    // Draw the actual food in the screen
    FoodDraw();

    // Draw the score
    ScoreDraw();

    // Update the changes in surface
    WindowSurfaceUpdate();

    // Equal sleep time between frames
    int diff = (int)((clock() - start) * 1000 / CLOCKS_PER_SEC);
    sleep_in_ms -= diff;

    // Wait
    Sleep();
  }
  end:

  // Destroy the food
  FoodDestroy();

  // Destroy the snake
  SnakeDestroy();

  // Destroy the walls
  WallsDestroy();

  // Destroy the terrain
  TerrainDestroy();

  // Close the sounds
  SoundsQuit();

  // Close the font opened and exit TTF module
  FontQuitScore();

  // Destroy the window and her surface, quit SDL module
  WindowAndSurfaceQuit();

  return 0;
}