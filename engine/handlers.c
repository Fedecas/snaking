#include "../level/snake.h"

#include "handlers.h"

static SDL_Event event;

static int MouseInButton(button_t buttonOption)
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

void HandleInputDirection()
{
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
}

void HandleInputOption()
{
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
        if(MouseInButton(ButtonQuit)) {
          ButtonSetBoxColor(ButtonQuit, COLOR_BUTTON_SELECTED_BOX);
          ButtonSetTextColor(ButtonQuit, COLOR_BUTTON_SELECTED_TEXT);
        } else {
          if(MouseInButton(ButtonRestart)) {
            ButtonSetBoxColor(ButtonRestart, COLOR_BUTTON_SELECTED_BOX);
            ButtonSetTextColor(ButtonRestart, COLOR_BUTTON_SELECTED_TEXT);
          } else {
            ButtonSetBoxColor(ButtonRestart, COLOR_BUTTON_BOX);
            ButtonSetTextColor(ButtonRestart, COLOR_BUTTON_TEXT);
          }

          ButtonSetBoxColor(ButtonQuit, COLOR_BUTTON_BOX);
          ButtonSetTextColor(ButtonQuit, COLOR_BUTTON_TEXT);
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if(MouseInButton(ButtonQuit)) {
          quit = OPTION_QUIT;
        } else if(MouseInButton(ButtonRestart)) {
          quit = OPTION_RESTART;
        }
      default: break;
    }
  }
}