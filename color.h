#ifndef SNAKE_COLOR_H
#define SNAKE_COLOR_H

#define COLOR_WHITE   colorBuild(255, 255, 255, 255)
#define COLOR_RED     colorBuild(255, 0, 0, 255)
#define COLOR_ORANGE  colorBuild(255, 122, 0, 255)
#define COLOR_GREEN   colorBuild(0, 255, 0, 255)
#define COLOR_BLUE    colorBuild(0, 0, 255, 255)
#define COLOR_BLACK   colorBuild(0, 0, 0, 255)

SDL_Color colorBuild(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
/*
 * Build a SDL_Color from integers
 */

#endif //SNAKE_COLOR_H