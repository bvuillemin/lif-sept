#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "terrain_espace.h"
#include "jeu.h"

/**
 * \struct Sauvegarde
 * \brief Planète du jeu
 */
typedef struct
{
    /** terrain_espace enregistrée dans cette sauvegarde */
    Terrain_espace* terrain_espace;
    /** jeu enregistré dans cette sauvegarde */
    Jeu* jeu;
}Sauvegarde;

void initialise_sauvegarde(Sauvegarde *une_sauvegarde);
Sauvegarde *creer_sauvegarde();
void creer_fichier_sauvegarde(const char nom[30], Terrain_espace *un_terrain_espace, Jeu *un_jeu);
void detruire_sauvegarde(const char nom[30]);
Sauvegarde* selection_ouverture(const char nom[30]);

#endif
