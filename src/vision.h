#ifndef _VISION_H_
#define _VISION_H_

#include "terrain_espace.h"

typedef enum
{
	AFFICHEE = 1,
	VISITEE,
	JAMAIS_VISITEE
}Champ_vision;

typedef struct
{
	int indice_joueur;
	int centre_vision; /*Va dÈfinir un centre, 0 si non, puis correspondra au rayon de vision autour de ce centre*/
	Champ_vision champ_vision;
}Vision_case;


typedef struct
{
	int indice_joueur;
	Terrain_espace* terrain_espace;
	Vision_case* vision_case;/*tableau de vision_case*/
}Vision_terrain;


void initialiser_vision_terrain(Vision_terrain *une_vision_terrain, Terrain_espace *un_terrain, int indice_joueur);
Vision_terrain* creer_vision_terrain(Terrain_espace *un_terrain, int indice_joueur);
void initialiser_vision_case(Vision_case* une_vision_case, int indice_joueur);
Vision_case* creer_vision_case(int indice_joueur);
void liberer_vision_case(Vision_case* une_vision_case);
void liberer_vision_terrain(Vision_terrain* une_vision_terrain);
void detruire_vision_terrain(Vision_terrain** une_vision_terrain);

Vision_case* get_vision_case(Vision_terrain* une_vision, int x, int y);
int get_centre_vision(Vision_case* une_case);
Champ_vision get_champ_vision(Vision_case* une_case);

void parcourir_terrain(Vision_terrain* une_vision, int indice_joueur);
void definir_vision(Vision_terrain* une_vision);
void testRegression_Vision_terrain();
void testRegression_Vision_case();
#endif
