#ifndef _IA_H_
#define _IA_H_

#include "jeu.h"

typedef enum
{
	EXPLORATION,
	DEFENSE,
	ATTAQUE
}COMPORTEMENT_IA;


typedef enum
{
	NON,
	FAIBLE,
	IMPORTANTE,
	TOTALE
}NIVEAU_MENACE;


void appeler_ia(Terrain_espace* un_terrain_espace, Joueur *un_joueur);
void choisir_case_deplacement_ia(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte* une_flotte);

#endif // _IA_H_
