#include <SDL2/SDL.h>

#include "color.h"
#include "draw.h"
#include "window.h"

#define WINDOW_WIDTH   640
#define WINDOW_HEIGHT  480

#define WINDOW_LIMIT_UP     0
#define WINDOW_LIMIT_DOWN   (WINDOW_HEIGHT - BOX_SIZE)
#define WINDOW_LIMIT_LEFT   0
#define WINDOW_LIMIT_RIGHT  (WINDOW_WIDTH - BOX_SIZE)

#define BOX_SIZE   20

#define DELAY_IN_MS 15

#define X_OFFSET  (x + (WINDOW_WIDTH/2) - (BOX_SIZE/2))
#define Y_OFFSET  (y + (WINDOW_HEIGHT/2) - (BOX_SIZE/2))

int main(int argc, char* args[])
{
  // The window we'll be rendering to
  SDL_Window* window = NULL;

  // Surface of the window
  SDL_Surface* screenSurface = NULL;

  // For events on window
  SDL_Event event;

  SDL_Color color;

  //Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    window = windowCreate(window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT);

    int last = 0;
    int isarrowpressed;

    int x = 0;
    int y = 0;

    int quit = 0;

    while(!quit) {
      isarrowpressed = 0;
      while(SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT: quit = 1; break;
          case SDL_WINDOWEVENT:
            switch (event.window.event) {
              case SDL_WINDOWEVENT_CLOSE: quit = 1; break;
              default: break;
            } break;
          case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
              case SDLK_ESCAPE: quit = 1; break;
              case SDLK_LEFT: x -= 10; last = 1; break;
              case SDLK_RIGHT: x += 10; last = 2; break;
              case SDLK_UP: y -= 10; last = 3; break;
              case SDLK_DOWN: y += 10; last = 4; break;
              default: break;
            } isarrowpressed = 1; break;
          default: break;
        }
      }

      color = colorBuild(255, 255, 255, 255); // White color

      // Set the surface color to white
      screenSurface = windowSurfaceColor(screenSurface, window, color);

      // Check if a key was pressed and wich was
      if(last && !isarrowpressed) {
        if(last == 1) x -= 3;
        else if(last == 2) x += 3;
        else if(last == 3) y -= 3;
        else y += 3;
      }

      // Correct the position X
      for(;X_OFFSET < WINDOW_LIMIT_LEFT; x++);
      for(;X_OFFSET > WINDOW_LIMIT_RIGHT; x--);

      // Correct the position Y
      for(;Y_OFFSET < WINDOW_LIMIT_UP; y++);
      for(;Y_OFFSET > WINDOW_LIMIT_DOWN; y--);

      color = colorBuild(255, 0, 0, 255); // Red color

      // Draw a red box 20x20 pixels at center of the window
      screenSurface = drawBox(screenSurface, X_OFFSET, Y_OFFSET, BOX_SIZE, color);

      // Update the changes in window
      SDL_UpdateWindowSurface(window);

      // Wait
      SDL_Delay(DELAY_IN_MS);
    }
  }

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
