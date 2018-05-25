#ifndef SNAKING_BUTTON_H
#define SNAKING_BUTTON_H

#include "draw.h"

typedef struct _button_t * button_t;

button_t ButtonQuit;
button_t ButtonRestart;

void ButtonsCreate();
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

void ButtonSetBoxColor(button_t button, color_t boxColor);
/*
 * Set a new box color for the button
 */

void ButtonSetTextColor(button_t button, color_t textColor);
/*
 * Set a new text color for the button
 */

void ButtonsDraw();
/*
 * Draw a button in the surface of window
 */

void ButtonsDestroy();
/*
 * Free the button's memory
 */

#endif //SNAKING_BUTTON_H
