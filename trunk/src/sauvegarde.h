#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "terrain_espace.h"

void detruire_sauvegarde(const char nom[30]);
void sauvegarde_terrain(const Terrain_espace *un_terrain_espace, const char nom[30]);
void sauvegarde_planete(const Planete *une_planete, const char nom[30]);
void sauvegarde_flotte(const Flotte *une_flotte, const char nom[30]);
void sauvegarde_unite(const Unite *une_unite, const char nom[30]);
Terrain_espace* ouverture_terrain(FILE *f, long a);
Planete* ouverture_planete(FILE *f, long a);
Flotte* ouverture_flotte(FILE *f, long a);
Terrain_espace* selection_ouverture(const char nom[30], long a);

#endif