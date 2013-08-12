#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Sokoban.h"
#include <stdio.h>
#include <stdlib.h>

void charge_images()
{
  position.x = 0;
  position.y = 0;
  menu = IMG_Load("images/10121.jpg");
  mur = IMG_Load("images/10113.jpg");
  caisse = IMG_Load("images/10114.jpg");
  caisse_ok = IMG_Load("images/10117.jpg");
  cible = IMG_Load("images/10118.png");
  mario = IMG_Load("images/45.gif");
  mario_right = IMG_Load("images/46.gif");
  mario_left = IMG_Load("images/47.gif");
  mario_down = IMG_Load("images/48.gif");}

void events()
{
  int continuer = 1;
  SDL_Event event;
  SDL_BlitSurface(menu, NULL, ecran, &position);
  while (continuer)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
        {
	case SDL_QUIT:
	  continuer = 0;
	  break;
	case SDL_KEYDOWN:
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      continuer = 0;
	      break;
	    case SDLK_a:
	      jouer(1);
	      continuer = 0;
	      break;
	    case SDLK_z:
	      printf("pas fait\n");
	      break;
	    }
	  break;
        }
      SDL_Flip(ecran);
    }
  sokoban_free();
}

void dessin()
{
  int i = 0, j = 0;
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  for(j = 0; j < 13; j++)
    {
      for(i = 0; i < 13; i++)
	{
	  switch(carte[i][j])
	    {
	    case '0':
	      break;
	    case '1': //start
	      break;
	    case '2':
	      SDL_BlitSurface(mur, NULL, ecran, &position);
	      break;
	    case '3':
	      SDL_BlitSurface(caisse, NULL, ecran, &position);
	      break;
	    case '4':
	      SDL_BlitSurface(caisse_ok, NULL, ecran, &position);
	      break;
	    case '5':
	      SDL_BlitSurface(cible, NULL, ecran, &position);
	      break;
	    case '6':
	      SDL_BlitSurface(mario_left, NULL, ecran, &position);
	      break;
	    case '7':
	      SDL_BlitSurface(mario, NULL, ecran, &position);
	      break;
	    case '8':
	      SDL_BlitSurface(mario_right, NULL, ecran, &position);
	      break;
	    case '9':
	      SDL_BlitSurface(mario_down, NULL, ecran, &position);
	      break;
	    }
	  position.x += 34;
	}
      position.y = position.y + 34;
      position.x = 0;
    }
  position.x = marioX*34;
  position.y = marioY*34;
  SDL_BlitSurface(mario, NULL, ecran, &position);
  position.x = 0;
  position.y = 0;
}

void charge_carte()
{
  FILE *f;
  char c = ' ';
  int x = 0;
  int y = 0;
  if((f = fopen("lvl", "r")) == NULL )
    {
      fprintf(stderr, "Impossible d'ouvrir le fichier");
      exit(EXIT_FAILURE);
    }
  while((c = fgetc(f)) != EOF)
    {
      if(c == '1')
	{
	  marioX = x;
	  marioY = y;
	  carte[x][y] = '0';
	  printf("trouve %d %d\n", marioX, marioY);
	}
      else
	{
	  if(c == '3')
	    {
	      nb_caisses++;
	    }
	  carte[x][y] = c;
	}
      x = (x+1)%13;
      if(x == 0)
	{
	  y++;
	}
    }
  fclose(f);
}

void jouer(int niveau)
{
  charge_carte(niveau);
  SDL_Event event;
  int continuer = 1;
  dessin();
  while (continuer && (nb_caisses > 0))
    {
      SDL_WaitEvent(&event);
      switch(event.type)
        {
	case SDL_QUIT:
	  continuer = 0;
	  break;
	case SDL_KEYDOWN:
	  switch(event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      continuer = 0;
	      break;
	    case SDLK_LEFT:
	      if(marioX-1 > -1 && ((carte[marioX-1][marioY] != '2') &&
		  !(carte[marioX-1][marioY] == '3' && carte[marioX-2][marioY] == '2')))
		{
		  if(carte[marioX-1][marioY] == '3')
		    {
 		        carte[marioX-1][marioY] = '0';
			if(carte[marioX-2][marioY] == '5') 
			{
				carte[marioX-2][marioY] ='4';
				nb_caisses--;
			}
			else
			{ 
				carte[marioX-2][marioY] = '3'; 
			}		        
		  }
		  marioX--;
		}
	      break;
	    case SDLK_RIGHT:
	      if(marioX+1 < 12 && ((carte[marioX+1][marioY] != '2') &&
		  !(carte[marioX+1][marioY] == '3' && carte[marioX+2][marioY] == '2')))
		{
		  if(carte[marioX+1][marioY] == '3')
		    {
			carte[marioX+1][marioY] = '0';
			if(carte[marioX+2][marioY] == '5') 
			{
				carte[marioX+2][marioY] ='4';
				nb_caisses--;
			}
			else
			{ 
				carte[marioX+2][marioY] = '3'; 
			} 
		    }
		  marioX++;
		}
	      break;
	    case SDLK_DOWN:
	      if(marioY+1 < 12 && ((carte[marioX][marioY+1] != '2') &&
		  !(carte[marioX][marioY+1] == '3' && carte[marioX][marioY+2] == '2')))
		{
		  if(carte[marioX][marioY+1] == '3')
		    {
			carte[marioX][marioY+1] = '0';
			if(carte[marioX][marioY+2] == '5') 
			{
				carte[marioX][marioY+2] ='4';
				nb_caisses--;
			}
			else
			{ 
				carte[marioX][marioY+2] = '3'; 
			}
			//carte[marioX][marioY+2] = (carte[marioX][marioY+2] == '5') ? '4' : '3';
		    }
		  marioY++;
		}
	      break;
	    case SDLK_UP:
	      if(marioY-1 > -1 && ((carte[marioX][marioY-1] != '2') &&
		  !(carte[marioX][marioY-1] == '3' && carte[marioX][marioY-2] == '2')))
		{
		  if(carte[marioX][marioY-1] == '3')
		    {
		        carte[marioX][marioY-1] = '0';
			if(carte[marioX][marioY-2] == '5') 
			{
				carte[marioX][marioY-2] ='4';
				nb_caisses--;
			}
			else
			{ 
				carte[marioX][marioY-2] = '3'; 
			}
			//carte[marioX][marioY-2] = (carte[marioX][marioY-2] == '5') ? '4' : '3';	
		    }
		  marioY--;
		}
	      break;
	    }
	  dessin();
	  break;
        }
      SDL_Flip(ecran);
    }
}

void sokoban_free()
{
  SDL_FreeSurface(mur);
  SDL_FreeSurface(caisse);
  SDL_FreeSurface(caisse_ok);
  SDL_FreeSurface(cible);
  SDL_FreeSurface(mario);
  SDL_FreeSurface(mario_right);
  SDL_FreeSurface(mario_left);
  SDL_FreeSurface(mario_down);
  SDL_Quit();
}  
