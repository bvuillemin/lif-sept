#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "terrain_espace.h"

void sauvegarde_terrain(const Terrain_espace *un_terrain_espace, const char nom[30]);

void sauvegarde_planete(const Planete *une_planete, const char nom[30]);


#endif
