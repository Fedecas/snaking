#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#endif //SNAKE_WINDOW_H

#define WINDOW_WIDTH   800
#define WINDOW_HEIGHT  600

#define WINDOW_LIMIT_UP     0
#define WINDOW_LIMIT_DOWN   (WINDOW_HEIGHT - BOX_SIZE)
#define WINDOW_LIMIT_LEFT   0
#define WINDOW_LIMIT_RIGHT  (WINDOW_WIDTH - BOX_SIZE)

SDL_Window* windowCreate(SDL_Window* window, int posX, int posY, int width, int height);
/*
 *  Create a window on the screen with size width * height
 */

SDL_Surface* windowSurfaceColor(SDL_Surface* screenSurface, SDL_Window* window, SDL_Color color);
/*
 * Set the window surface with new color
 */