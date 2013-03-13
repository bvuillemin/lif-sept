#include <stdlib.h>
#include <stdio.h>

#include "case.h"
#include "terrain.h"

void set_taille_x(terrain terrain_jeu, int x)
{
    terrain_jeu.taille_x = x;
}

int get_taille_x(terrain terrain_jeu)
{
    return terrain_jeu.taille_x;
}

void set_taille_y(terrain terrain_jeu, int y)
{
    terrain_jeu.taille_y = y;
}

int get_taille_y(terrain terrain_jeu)
{
    return terrain_jeu.taille_y;
}

void initilalise_terrain(terrain *terrain_de_jeu, int taille_x, int taille_y)
{
    terrain_de_jeu->taille_x = taille_x;
    terrain_de_jeu->taille_y = taille_y;
    terrain_de_jeu->tab_terrain = (Case *)malloc(sizeof(Case)*taille_x*taille_y);
}

Terrain *creer_terrain(int taille_x, int taille_y)
{
    Terrain *terrain = (terrain *)malloc(sizeof(terrain));
    initialise_terrain(terrain, taille_x, taille_y);
    return terrain;
}
