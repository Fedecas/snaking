#ifndef SNAKING_BUTTON_H
#define SNAKING_BUTTON_H

#include "engine/draw.h"

typedef struct _button_t * button_t;

button_t ButtonCreate(int x, int y,
                      int width, int height,
                      SDL_Color boxColor, SDL_Color textColor,
                      char* text);
/*
 * Create a button with his parameters
 */

int ButtonPosX(button_t button);
/*
 * Return the x position of the button
 */

int ButtonPosY(button_t button);
/*
 * Return the y position of the button
 */

int ButtonWidth(button_t button);
/*
 * Return the width of the button
 */

int ButtonHeight(button_t button);
/*
 * Return the height of the button
 */

void ButtonSetBoxColor(button_t button, SDL_Color boxColor);
/*
 * Set a new box color for the button
 */

void ButtonSetTextColor(button_t button, SDL_Color textColor);
/*
 * Set a new text color for the button
 */

void ButtonDraw(SDL_Surface* surface, button_t button, TTF_Font* font);
/*
 * Draw a button in the surface of window
 */

button_t ButtonDestroy(button_t button);
/*
 * Free the button's memory
 */

#endif //SNAKING_BUTTON_H
