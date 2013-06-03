#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_

#include "jeu.h"

/**
 * \struct Sauvegarde
 * \brief Sauvegarde du jeu
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
void detruire_sauvegarde(Sauvegarde **une_sauvegarde);
Sauvegarde* selection_ouverture(const char nom[30]);
void testRegression_sauvegarde(void);
#endif
