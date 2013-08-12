//g++ -o sokoban main.c `sdl-config --cflags --libs` -lGL -lGLU
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "main.h"

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1) 
    {
      fprintf(stderr, "SDL:Init error: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
  charge_images();
  if((ecran = SDL_SetVideoMode(408, 408, 32, SDL_HWSURFACE  | SDL_FULLSCREEN )) == NULL)
    {
      fprintf(stderr, "SDL:VIdeo error : %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
  SDL_WM_SetCaption("Sokoban", NULL);
  events();
  SDL_Quit();
  return EXIT_SUCCESS;
}

