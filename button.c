#include "button.h"

struct _button_t {
    int x;
    int y;
    int width;
    int height;
    SDL_Color boxColor;
    SDL_Color textColor;
    char* text;
} _button_t;

button_t ButtonCreate(int buttonX, int buttonY,
                      int buttonWidth, int buttonHeight,
                      SDL_Color buttonColor, SDL_Color textColor,
                      char* buttonText)
{
  button_t NewButton = (button_t) malloc(sizeof(_button_t));

  NewButton->x = buttonX;
  NewButton->y = buttonY;
  NewButton->width = buttonWidth;
  NewButton->height = buttonHeight;
  NewButton->boxColor = buttonColor;
  NewButton->textColor = textColor;
  NewButton->text = buttonText;

  return NewButton;
}

int ButtonPosX(button_t buttonOption)
{
  return (buttonOption->x);
}

int ButtonPosY(button_t buttonOption)
{
  return (buttonOption->y);
}

int ButtonWidth(button_t buttonOption)
{
  return (buttonOption->width);
}

int ButtonHeight(button_t buttonOption)
{
  return (buttonOption->height);
}

void ButtonSetBoxColor(button_t buttonOption, SDL_Color newBoxColor)
{
  buttonOption->boxColor = newBoxColor;
}

void ButtonSetTextColor(button_t buttonOption, SDL_Color newTextColor)
{
  buttonOption->textColor = newTextColor;
}

void ButtonDraw(SDL_Surface* LevelSurface, button_t buttonOption, TTF_Font* font)
{
  DrawBox(LevelSurface, buttonOption->x, buttonOption->y,
          buttonOption->width, buttonOption->height, buttonOption->boxColor);

  int fontwidth, fontheight;
  TTF_SizeText(font, buttonOption->text, &fontwidth, &fontheight);

  int drawtextY = buttonOption->y + (buttonOption->height / 2) - (fontheight / 2);
  int drawtextX = buttonOption->x + (buttonOption->width / 2) - (fontwidth / 2);

  DrawText(LevelSurface, font, buttonOption->text, drawtextX, drawtextY, buttonOption->textColor);
}

button_t ButtonDestroy(button_t buttonOption)
{
  free(buttonOption);
  buttonOption = NULL;

  return buttonOption;
}