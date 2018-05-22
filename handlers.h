#ifndef SNAKING_HANDLERS_H
#define SNAKING_HANDLERS_H

#include "button.h"
#include "engine/window.h"

#define OPTION_CONTINUE   0
#define OPTION_QUIT       1
#define OPTION_RESTART    2

void HandleInputDirection(int* quit, int* arrow);
/*
 * Catch the pressed arrow for snake direction, or quit if correspond
 */

void HandleInputOption(int* quit, button_t buttonQuit, button_t buttonRestart);
/*
 * Catch the option button pressed, or quit if correspond
 */

#endif //SNAKING_HANDLERS_H