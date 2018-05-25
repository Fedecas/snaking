#ifndef SNAKE_COLORS_H
#define SNAKE_COLORS_H

static inline SDL_Color mk_SDL_Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  SDL_Color color = {red, green, blue, alpha};
  return color;
}

#define COLOR_BLACK                 mk_SDL_Color(0, 0, 0, 255)
#define COLOR_WHITE                 mk_SDL_Color(255, 255, 255, 255)

#define COLOR_BUTTON_BOX            COLOR_BLACK
#define COLOR_BUTTON_TEXT           COLOR_WHITE
#define COLOR_BUTTON_SELECTED_BOX   COLOR_WHITE
#define COLOR_BUTTON_SELECTED_TEXT  COLOR_BLACK

#define COLOR_FOOD                  mk_SDL_Color(109, 76, 65, 255)

#define COLOR_SCORE                 mk_SDL_Color(171, 71, 188, 255)

#define COLOR_SNAKE_HEAD            mk_SDL_Color(192, 202, 51, 255)
#define COLOR_SNAKE_BODY            mk_SDL_Color(211, 47, 47, 255)

#define COLOR_TERRAIN               mk_SDL_Color(255, 249, 196, 255)

#define COLOR_WALL                  mk_SDL_Color(96, 125, 139, 255)

#endif //SNAKE_COLORS_H
