#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "terrain_espace.h"

typedef struct
{
    int nb_terrain_espace;
    Terrain_espace* terrain_espace;
    int nb_planete;
    Planete* tab_planete;
    int nb_flotte;
    Flotte* tab_flotte;
}Sauvegarde;

void initialise_sauvegarde(Sauvegarde *une_sauvegarde);
Sauvegarde *creer_sauvegarde();
void creer_fichier_sauvegarde(const char nom[30], Terrain_espace *un_terrain_espace);
void ajouter_terrain_espace_sauvegarde(Sauvegarde *une_sauvegarde, Terrain_espace *un_terrain_espace);
void ajouter_planete_sauvegarde(Sauvegarde *une_sauvegarde, Planete *une_planete);
void ajouter_flotte_sauvegarde(Sauvegarde *une_sauvegarde, Flotte *une_flotte);

void detruire_sauvegarde(const char nom[30]);
Terrain_espace* selection_ouverture(const char nom[30]);

#endif
