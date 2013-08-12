#ifndef SOKOBAN_H
#include <SDL/SDL.h>
#define SOKOBAN_H
void events();
void sokoban_free();
void jouer(int jouer);
void dessin();
int marioX;
int marioY;
int nb_caisses = 0;
char carte  [13][13];
SDL_Surface *ecran = NULL;
SDL_Surface *menu = NULL;
SDL_Surface *caisse = NULL;
SDL_Surface *caisse_ok = NULL;
SDL_Surface *mur;
SDL_Surface *mario_left = NULL;
SDL_Surface *mario_down = NULL;
SDL_Surface *mario_right = NULL;
SDL_Surface *mario = NULL;
SDL_Surface *cible = NULL;
SDL_Rect position; 
#endif
