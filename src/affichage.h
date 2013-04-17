#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#include <SDL/SDL.h>
#ifdef __APPLE__
#include "SDL_image.h"
#else
#include <SDL/SDL_image.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "terrain_espace.h"
#include "case_terrain_espace.h"
#include "unite.h"
#include "planete.h"
#include "niveau.h"
#include "terrain_combat.h"
/**
 * \file      Module terrain
 * \author
 * \version   0.1
 * \date      13 mars 2013
 * \brief
 *
 * \details
 */
bool test_souris_rectangle (SDL_Rect taille_surface, int x, int y);
void initialise_sdl_rect(SDL_Rect un_rectangle, int x, int y, int w, int h);
bool booleen_case_pointeur_souris(Terrain_espace *un_terrain_espace, int x, int y);
Case_terrain_espace* case_pointeur_souris(Terrain_espace *un_terrain_espace, int x, int y) ;

void affichage_ecran(Jeu *un_jeu, Terrain_espace *un_terrain_espace);
SDL_Surface* creer_affichage_terrain(Terrain_espace *un_terrain_espace);
SDL_Surface* affichage_terrain(Terrain_espace *un_terrain_espace, SDL_Surface *carte);
SDL_Surface* affichage_ressource(Jeu *un_jeu, SDL_Surface *surface_ressource);

void pause();

/*pour le combat :*/
void affichage_ecran_combat(Terrain_combat *un_terrain_combat);
SDL_Surface* creer_affichage_terrain_combat(Terrain_combat *un_terrain_combat);
SDL_Surface* affichage_terrain_combat(Terrain_combat *un_terrain_combat, SDL_Surface *carte);
#endif
