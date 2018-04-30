#include <time.h>
#include <SDL2/SDL_mixer.h>

#include "draw.h"
#include "food.h"
#include "score.h"
#include "snake.h"
#include "terrain.h"
#include "wall.h"
#include "window.h"
#include "sound.h"

#define OPTION_CONTINUE   0
#define OPTION_QUIT       1
#define OPTION_RESTART    2

#define DELAY_IN_MS       75

static void SleepMS(int timeinms)
{
  struct timespec timetosleep;

  timetosleep.tv_nsec = 1000 * 1000 * timeinms;
  timetosleep.tv_sec = 0;

  nanosleep(&timetosleep, NULL);
}

static int MouseInButton(SDL_Event event, int buttonX, int buttonY,
                         int buttonwidth, int buttonheight)
{
  int MouseInX = (event.motion.x >= buttonX)
                 && (event.motion.x <= buttonX + buttonwidth);
  int MouseInY = (event.motion.y >= buttonY)
                 && (event.motion.y <= buttonY + buttonheight);

  return (MouseInX && MouseInY);
}

static int GameOver(window GameWindow, TTF_Font* font, sound GameOverSound)
{
  SoundPlay(GameOverSound, 1);

  // Draw "game over" text
  char* text = "GAME OVER";

  int fontwidth, fontheight;
  TTF_SizeText(font, text, &fontwidth, &fontheight);

  int textposX = (WINDOW_WIDTH / 2) - (fontwidth / 2);
  int textposY = (WINDOW_HEIGHT / 2) - fontheight;

  DrawText(GameWindow->surface, font, text, textposX, textposY, COLOR_SCORE);

  // Draw the quit button
  int buttonwidth = WINDOW_WIDTH / 6;
  int buttonheight = buttonwidth / 2;

  int buttonquitX = (WINDOW_WIDTH / 2) - (buttonwidth + buttonheight);
  int buttonquitY = textposY + buttonheight;

  int fontsize = (buttonwidth + buttonheight) / 10;
  TTF_Font* buttonfont = TTF_OpenFont(FONT_PATH, fontsize);

  DrawButton(GameWindow->surface, buttonquitX, buttonquitY,
             buttonwidth, buttonheight, COLOR_BLACK,
             buttonfont, "QUIT", COLOR_WHITE);

  // Draw the restart button
  int buttonrestartX = buttonquitX + (2 * buttonwidth);
  int buttonrestartY = textposY + buttonheight;

  DrawButton(GameWindow->surface, buttonrestartX, buttonrestartY,
             buttonwidth, buttonheight, COLOR_BLACK,
             buttonfont, "RESTART", COLOR_WHITE);

  // Wait for response loop
  SDL_Color boxbuttoncolor, textbuttoncolor;
  int quit = OPTION_CONTINUE;
  SDL_Event event;

  while(!quit) {
    WindowSurfaceUpdate(GameWindow);

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
        case SDL_MOUSEMOTION:
          if(MouseInButton(event, buttonquitX, buttonquitY,
                           buttonwidth, buttonheight)) {
            boxbuttoncolor = COLOR_WHITE;
            textbuttoncolor = COLOR_BLACK;
          } else {
            if(MouseInButton(event, buttonrestartX, buttonrestartY,
                             buttonwidth, buttonheight)) {
              boxbuttoncolor = COLOR_WHITE;
              textbuttoncolor = COLOR_BLACK;
            } else {
              boxbuttoncolor = COLOR_BLACK;
              textbuttoncolor = COLOR_WHITE;
            }
            DrawButton(GameWindow->surface, buttonrestartX, buttonrestartY,
                       buttonwidth, buttonheight, boxbuttoncolor,
                       buttonfont, "RESTART", textbuttoncolor);

            boxbuttoncolor = COLOR_BLACK;
            textbuttoncolor = COLOR_WHITE;
          }
          DrawButton(GameWindow->surface, buttonquitX, buttonquitY,
                     buttonwidth, buttonheight, boxbuttoncolor,
                     buttonfont, "QUIT", textbuttoncolor);
          break;
        case SDL_MOUSEBUTTONDOWN:
          if(MouseInButton(event, buttonquitX, buttonquitY,
                           buttonwidth, buttonheight)) {
            quit = OPTION_QUIT;
          } else if(MouseInButton(event, buttonrestartX, buttonrestartY,
                                  buttonwidth, buttonheight)) {
            quit = OPTION_RESTART;
          }
        default: break;
      }
    }

    SleepMS(DELAY_IN_MS / 2);
  }

  TTF_CloseFont(buttonfont);

  SoundStop(1);

  return quit;
}

static void GameRestart(food* ActualFood, snake* PlayerSnake, score* GameScore)
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
  window GameWindow = WindowAndSurfaceInit();

  // Initialize TTF module and the font for texts
  TTF_Font* ScoreFont = DrawTextInit();

  // Initialize the sounds to play
  sound IncreaseSound = SoundInit("SnakeIncrease");
  sound EatSound = SoundInit("SnakeEat");
  sound GameOverSound = SoundInit("GameOver");
  sound GameRestartSound = SoundInit("GameRestart");

  // Create the terrain to move
  terrain LevelTerrain = TerrainCreate();

  // Create the limits
  wall* LevelWalls = WallsCreate();

  // Create the snake for use
  snake PlayerSnake = SnakeCreate();

  // Create first food
  food ActualFood = FoodCreate();

  // Initialize the score
  score GameScore = ScoreCreate();

  // For events on window
  SDL_Event event;

  /* - Game running loop - */
  int arrow = DIRECTION_NONE;
  int quit = OPTION_CONTINUE;

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
    TerrainDraw(GameWindow->surface, LevelTerrain);

    // Draw the limits of the level
    WallsDraw(GameWindow->surface, LevelWalls);

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