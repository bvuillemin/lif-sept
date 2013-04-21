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
SDL_Surface* affichage_ecran_combat(const Terrain_combat *un_terrain_combat);
void afficher_ecran_terrain_combat(const Terrain_combat *un_terrain_combat, SDL_Surface * une_surface);
SDL_Surface* creer_affichage_terrain_combat(Terrain_combat *un_terrain_combat);
SDL_Surface* affichage_terrain_combat(Terrain_combat *un_terrain_combat, SDL_Surface *carte);

/*
SDL_Surface * surface = NULL;
SDL_Rect position;
Uint32 couleur;

couleur = SDL_MapRGB(surface->format,r,g,b);
surface =SDL_SetVideoMode(TAILLE_ECRAN_COMBAT_X,TAILLE_ECRAN_COMBAT_Y,nb_couleur,SDL_HWSURFACE|SDL_RESIZABLE|SDL_DOUBLEBUF)
SDL_CreateRGBSurface(options, taille_x, taille_y, nb_couleurs, 0, 0, 0, 0)
SDL_FillRect(surface, NULL, couleur)
SDL_BlitSurface(surface_a_coller,NULL,surface_support,&position)
SDL_WM_SetCaption("nom_fenetre","nom_icone");
SDL_WM_SetIcon(IMG_Load("sdl_icone.bmp"), NULL);
SDL_FreeSurface(surface)
*/
#endif
