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
    Case *tab_terrain;
}terrain;


void set_taille_x(terrain terrain_jeu, int x);
int get_taille_x(terrain terrain_jeu);

void set_taille_y(terrain terrain_jeu, int y);
int get_taille_y(terrain terrain_jeu);

void initilalise_terrain(terrain *terrain_de_jeu, int taille_x, int taille_y);
Terrain *creer_terrain(int taille_x, int taille_y);






#endif
