#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include "case.h"


/**
 * \file      Module terrain
 * \author    Les queux de cheval
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
    Case_terrain *tab_terrain;
}Terrain;


void set_taille_x(Terrain terrain_jeu, int x);
int get_taille_x(Terrain terrain_jeu);

void set_taille_y(Terrain terrain_jeu, int y);
int get_taille_y(Terrain terrain_jeu);

void initilalise_terrain(Terrain *terrain_jeu, int taille_x, int taille_y);
Terrain *creer_terrain(int taille_x, int taille_y);

void libere_terrain(Terrain *terrain_jeu);
void detruit_terrain(Terrain **terrain_jeu);





#endif
