#ifndef SNAKE_COLOR_H
#define SNAKE_COLOR_H

#define COLOR_WHITE   colorBuild(255, 255, 255, 255)
#define COLOR_MAGENTA colorBuild(255, 0, 255, 255)
#define COLOR_DRED    colorBuild(128, 0, 0, 255)
#define COLOR_RED     colorBuild(255, 0, 0, 255)
#define COLOR_ORANGE  colorBuild(255, 128, 0, 255)
#define COLOR_YELLOW  colorBuild(255, 255, 0, 255)
#define COLOR_LGREEN  colorBuild(128, 255, 0, 255)
#define COLOR_GREEN   colorBuild(0, 255, 0, 255)
#define COLOR_DGREEN  colorBuild(38, 151, 57, 255)
#define COLOR_AQUA    colorBuild(0, 255, 128, 255)
#define COLOR_CYAN    colorBuild(0, 255, 255, 255)
#define COLOR_LBLUE   colorBuild(0, 128, 255, 255)
#define COLOR_BLUE    colorBuild(0, 0, 255, 255)
#define COLOR_DBLUE   colorBuild(0, 0, 128, 255)
#define COLOR_BLACK   colorBuild(0, 0, 0, 255)

SDL_Color colorBuild(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
/*
 * Build a SDL_Color from integers
 */

#endif //SNAKE_COLOR_H