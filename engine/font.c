#include "block.h"
#include "button.h"
#include "font.h"

void FontInitModuleAndScore()
{
  TTF_Init();

  ScoreFont = TTF_OpenFont(FONT_PATH, FONT_SIZE);

  if(ScoreFont == NULL) {
    printf("[error] Score font could not be loaded! TTF_Error: %s\n", SDL_GetError());
  }
}

void FontInitButton()
{
  int buttonWidth = ButtonWidth(ButtonQuit);
  int buttonHeight = ButtonHeight(ButtonQuit);

  ButtonFont = TTF_OpenFont(FONT_PATH, (buttonWidth + buttonHeight) / 10);

  if(ButtonFont == NULL) {
    printf("[error] Button font could not be loaded! TTF_Error: %s\n", SDL_GetError());
  }
}

void FontQuitButton()
{
  TTF_CloseFont(ButtonFont);
  ButtonFont = NULL;
}

void FontQuitScore()
{
  TTF_CloseFont(ScoreFont);
  ScoreFont = NULL;

  TTF_Quit();
}