#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "case.h"

/**
 * \file      Module terrain
 * \author    Les queues de cheval
 * \version   0.1
 * \date      13 mars 2013
 * \brief     Terrain et ses particularités
 *
 * \details
 */

typedef struct
{
    int taille_x;
    int taille_y;
    Case_terrain *tab_terrain; /*x en abscisse, y en ordonnée, on commence à 0 (à modifier?)*/
}Terrain;

void initilalise_terrain(Terrain *terrain_jeu, int taille_x, int taille_y);
Terrain *creer_terrain(int taille_x, int taille_y);

void libere_terrain(Terrain *terrain_jeu);
void detruit_terrain(Terrain **terrain_jeu);

void set_taille_x(Terrain *terrain_jeu, int x);
int get_taille_x(const Terrain *terrain_jeu);
void set_taille_y(Terrain *terrain_jeu, int y);
int get_taille_y(const Terrain *terrain_jeu);
void set_case_terrain(const Terrain *terrain, int x, int y, char c);
Case_terrain get_case_terrain(const Terrain *terrain, const int x, const int y);


void modification_terrain(const Terrain *terrain, const char c); /* met toutes les cases du terrain avec le type char c*/
void ajouter_planete_terrain(Terrain *terrain, int x, int y); /*va créer une planète et l'ajouter sur la carte aux coordonnées*/

void affiche_terrain(const Terrain *terrain); /*affiche tous les types du terrain*/

/*void test_module_terrain();*/



#endif
