#include "Constants.h"
#include <SDL.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <stdio.h>

int main(void) {
  SDL_Window *window = NULL;

  SDL_Surface *screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    perror("[ERROR] could not start SDL.");
    return -1;
  }

  window =
      SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       SCREEN_WDITH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    perror("Could not create SDL winodw!");
    return -1;
  }

  screenSurface = SDL_GetWindowSurface(window);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
