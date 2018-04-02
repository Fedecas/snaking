#include <SDL2/SDL.h>

#include "color.h"
#include "draw.h"
#include "window.h"

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
    window = windowCreate(window, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480);

    int quit = 0;
    while(!quit) {
      while(SDL_PollEvent(&event)) {
        // Check if the cross has been pressed
        if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)) {
          quit = 1;
        }
      }

      color = colorBuild(255, 255, 255, 255); // White color

      // Set the surface color to white
      screenSurface = windowSurfaceColor(screenSurface, window, color);

      color = colorBuild(255, 0, 0, 255); // Red color

      // Draw a red box 50x50 pixels at center of the window
      screenSurface = drawBox(screenSurface, 295, 190, 50, 50, color);

      // Update the changes in window
      SDL_UpdateWindowSurface(window);

      // Wait 100 ms
      SDL_Delay(100);
    }
  }

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
