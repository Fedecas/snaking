#include "button.h"
#include "window.h"

struct _button_t {
    int x;
    int y;
    int width;
    int height;
    SDL_Color boxColor;
    SDL_Color textColor;
    char* text;
};

static button_t ButtonCreate(int buttonX, int buttonY,
                             int buttonWidth, int buttonHeight,
                             char* buttonText)
{
  button_t NewButton = (button_t) malloc(sizeof(struct _button_t));

  NewButton->x = buttonX;
  NewButton->y = buttonY;
  NewButton->width = buttonWidth;
  NewButton->height = buttonHeight;
  NewButton->boxColor = COLOR_BUTTON_BOX;
  NewButton->textColor = COLOR_BUTTON_TEXT;
  NewButton->text = buttonText;
}

void ButtonsCreate()
{
  int fontHeight;
  TTF_SizeText(ScoreFont, "GAME OVER", NULL, &fontHeight); // TODO ver

  int buttonWidth = WINDOW_WIDTH / 6;
  int buttonHeight = buttonWidth / 2;

  int buttonQuitX = (WINDOW_WIDTH / 2) - (buttonWidth + buttonHeight);
  int buttonQuitY = (WINDOW_HEIGHT / 2) - fontHeight + buttonHeight;

  ButtonQuit = ButtonCreate(buttonQuitX, buttonQuitY,
                            buttonWidth, buttonHeight, "QUIT");

  int buttonRestartX = buttonQuitX + (2 * buttonWidth);
  int buttonRestartY = buttonQuitY;

  ButtonRestart = ButtonCreate(buttonRestartX, buttonRestartY,
                               buttonWidth, buttonHeight, "RESTART");
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

static void ButtonDraw(button_t buttonOption)
{
  DrawBox(buttonOption->x, buttonOption->y,
          buttonOption->width, buttonOption->height, buttonOption->boxColor);

  int fontwidth, fontheight;
  TTF_SizeText(ButtonFont, buttonOption->text, &fontwidth, &fontheight);

  int drawtextY = buttonOption->y + (buttonOption->height / 2) - (fontheight / 2);
  int drawtextX = buttonOption->x + (buttonOption->width / 2) - (fontwidth / 2);

  DrawText(ButtonFont, buttonOption->text, drawtextX, drawtextY, buttonOption->textColor);
}

void ButtonsDraw()
{
  ButtonDraw(ButtonQuit);
  ButtonDraw(ButtonRestart);
}

static button_t ButtonDestroy(button_t buttonOption)
{
  free(buttonOption);
  buttonOption = NULL;

  return buttonOption;
}

void ButtonsDestroy()
{
  ButtonQuit = ButtonDestroy(ButtonQuit);
  ButtonRestart = ButtonDestroy(ButtonRestart);
}