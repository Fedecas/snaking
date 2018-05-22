#include "level/snake.h"

#include "handlers.h"

static int MouseInButton(SDL_Event event, button_t buttonOption)
{
  int buttonPosX = ButtonPosX(buttonOption);
  int buttonPosY = ButtonPosY(buttonOption);
  int buttonWidth = ButtonWidth(buttonOption);
  int buttonHeight = ButtonHeight(buttonOption);

  int MouseInX = (event.motion.x >= buttonPosX)
                 && (event.motion.x <= buttonPosX + buttonWidth);
  int MouseInY = (event.motion.y >= buttonPosY)
                 && (event.motion.y <= buttonPosY + buttonHeight);

  return (MouseInX && MouseInY);
}

void HandleInputDirection(int* quit, int* arrow)
{
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: *quit = OPTION_QUIT; break;
      case SDL_WINDOWEVENT:
        switch (event.window.event) {
          case SDL_WINDOWEVENT_CLOSE: *quit = OPTION_QUIT; break;
          default: break;
        } break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE: *quit = OPTION_QUIT; break;
          case SDLK_LEFT: *arrow = DIRECTION_LEFT; break;
          case SDLK_RIGHT: *arrow = DIRECTION_RIGHT; break;
          case SDLK_UP: *arrow = DIRECTION_UP; break;
          case SDLK_DOWN: *arrow = DIRECTION_DOWN; break;
          default: break;
        } break;
      default: break;
    }
  }
}

void HandleInputOption(int* quit, button_t buttonQuit, button_t buttonRestart)
{
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: *quit = OPTION_QUIT; break;
      case SDL_WINDOWEVENT:
        switch (event.window.event) {
          case SDL_WINDOWEVENT_CLOSE: *quit = OPTION_QUIT; break;
          default: break;
        } break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE: *quit = OPTION_QUIT; break;
          default: break;
        }
      case SDL_MOUSEMOTION:
        if(MouseInButton(event, buttonQuit)) {
          ButtonSetBoxColor(buttonQuit, COLOR_WHITE);
          ButtonSetTextColor(buttonQuit, COLOR_BLACK);
        } else {
          if(MouseInButton(event, buttonRestart)) {
            ButtonSetBoxColor(buttonRestart, COLOR_WHITE);
            ButtonSetTextColor(buttonRestart, COLOR_BLACK);
          } else {
            ButtonSetBoxColor(buttonRestart, COLOR_BLACK);
            ButtonSetTextColor(buttonRestart, COLOR_WHITE);
          }

          ButtonSetBoxColor(buttonQuit, COLOR_BLACK);
          ButtonSetTextColor(buttonQuit, COLOR_WHITE);
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if(MouseInButton(event, buttonQuit)) {
          *quit = OPTION_QUIT;
        } else if(MouseInButton(event, buttonRestart)) {
          *quit = OPTION_RESTART;
        }
      default: break;
    }
  }
}