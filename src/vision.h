#ifndef _VISION_H_
#define _VISION_H_

#include "Jeu.h"

typedef enum
{
	AFFICHEE,
	VISITEE,
	JAMAIS_VISITEE
}Champ_vision;

typedef struct
{
	int indice_joueur;
	Case_terrain_espace* case_terrain_espace;
	int centre_vision; /*Va définir un centre, 0 si non, puis correspondra au rayon de vision autour de ce centre*/
	Champ_vision champ_vision;
}Vision_case;


typedef struct
{
	int indice_joueur;
	Terrain_espace* terrain_espace;
	Vision_case* vision_case;
}Vision_terrain;


void initialiser_vision_terrain(Vision_terrain *une_vision_terrain, Terrain_espace *un_terrain, Joueur *un_joueur);
Vision_terrain* creer_vision_terrain(Terrain_espace *un_terrain, Joueur *un_joueur);
void initialiser_vision_case(Vision_case* une_vision_case, Case_terrain_espace* une_case, int indice_joueur);
void liberer_vision_case(Vision_case* une_vision_case);
void liberer_vision_terrain(Vision_terrain* une_vision_terrain);
void detruire_vision_terrain(Vision_terrain** une_vision_terrain);

Vision_case* get_vision_case(Vision_terrain* une_vision, int x, int y);

void parcourir_terrain(Vision_terrain* une_vision, Joueur* un_joueur);
void definir_vision(Vision_terrain* une_vision);

#endif
