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

void affichage_ecran(Terrain_espace *un_terrain_espace);
SDL_Surface* creer_affichage_terrain(Terrain_espace *un_terrain_espace);
SDL_Surface* affichage_terrain(Terrain_espace *un_terrain_espace, SDL_Surface *carte);

void pause();

/*pour le combat :*/
void affichage_ecran_combat(Terrain_combat *un_terrain_combat);
SDL_Surface* creer_affichage_terrain_combat(Terrain_combat *un_terrain_combat);
SDL_Surface* affichage_terrain_combat(Terrain_combat *un_terrain_combat, SDL_Surface *carte);
#endif
