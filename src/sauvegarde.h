#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "terrain_espace.h"
#include "jeu.h"
typedef struct
{
    Terrain_espace* terrain_espace;
    Jeu* jeu;
}Sauvegarde;

void initialise_sauvegarde(Sauvegarde *une_sauvegarde);
Sauvegarde *creer_sauvegarde();
void creer_fichier_sauvegarde(const char nom[30], Terrain_espace *un_terrain_espace);
void ajouter_terrain_espace_sauvegarde(Sauvegarde *une_sauvegarde, Terrain_espace *un_terrain_espace);
void ajouter_planete_sauvegarde(Sauvegarde *une_sauvegarde, Planete *une_planete);
void ajouter_flotte_sauvegarde(Sauvegarde *une_sauvegarde, Flotte *une_flotte);

void detruire_sauvegarde(const char nom[30]);
Sauvegarde* selection_ouverture(const char nom[30]);

#endif
