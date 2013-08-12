#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

SDL_Surface *ecran;
SDL_Surface *maSurface;
SDL_Surface *zozor;
SDL_Rect position;

void charge_images()
{
  position.x = 0;
  position.y = 0;
  maSurface = IMG_Load("pack_images_sdz/lac_en_montagne.bmp");
  zozor = IMG_Load("images/10121.gif");
  SDL_BlitSurface(maSurface, NULL, ecran, &position);
  //SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format, 0, 0, 255));
  //SDL_SetAlpha(zozor, SDL_SRCALPHA, 128);
  position.x = 500;
  position.y = 260;
  SDL_BlitSurface(zozor, NULL, ecran, &position);
  SDL_FreeSurface(maSurface);
}

void events()
{
  SDL_Event event;
  int continuer = 1;

  while (continuer)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
        case SDL_QUIT:
	  continuer = 0;
	  break;
        case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_ESCAPE:
	      continuer = 0;
	      break;
            }
	  break;
	}
      SDL_Flip(ecran);
    }
}

int main()
{
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      fprintf(stderr ,"SDL error");
      return -1;
    }
  SDL_WM_SetIcon(SDL_LoadBMP("pack_images_sdz/sdl_icone.bmp"), NULL);
  if((ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_FULLSCREEN)) == NULL)
    {
      fprintf(stderr ,"SDL error");
      return -1;      
    } 
  SDL_WM_SetCaption("SDL images", NULL);
  charge_images();
  events();
  SDL_Quit();
  return 0;
}
