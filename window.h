#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#endif //SNAKE_WINDOW_H

SDL_Window* windowCreate(SDL_Window* window, int posX, int posY, int width, int height);
/*
 *  Create a window on the screen with size width * height
 */

SDL_Surface* windowSurfaceColor(SDL_Surface* screenSurface, SDL_Window* window, SDL_Color color);
/*
 * Set the window surface with new color
 */