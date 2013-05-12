#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "vision.h"


/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initialiser_vision_terrain(Vision_terrain *une_vision_terrain, Terrain_espace *un_terrain, Joueur *un_joueur)
{
	int i, j, indice_joueur;
	Case_terrain_espace *une_case;

	indice_joueur = get_numero_joueur(un_joueur);
	une_vision_terrain->indice_joueur;
	une_vision_terrain->terrain_espace = un_terrain;
	une_vision_terrain->vision_case = (Vision_case *)malloc(sizeof(Vision_case) * get_taille_espace_x(un_terrain) * get_taille_espace_y(un_terrain));
	for(i=0;i<un_terrain->taille_espace_y;i++)
	{
		for(j=0;j<un_terrain->taille_espace_x;j++)
		{
			une_case = get_case_terrain_espace(un_terrain, j, i);
			initialiser_vision_case(&une_vision_terrain->vision_case[indice_tableau(un_terrain, i, j)], une_case, indice_joueur);
		}
	}
}

Vision_terrain* creer_vision_terrain(Terrain_espace* un_terrain, Joueur* un_joueur)
{
	Vision_terrain* une_vision = (Vision_terrain *)malloc(sizeof(Vision_terrain));
	initialiser_vision_terrain(une_vision, un_terrain, un_joueur);
	return une_vision;
}

void initialiser_vision_case(Vision_case* une_vision_case, Case_terrain_espace* une_case, int indice_joueur)
{
	une_vision_case->indice_joueur = indice_joueur;
	une_vision_case->case_terrain_espace = une_case;
	une_vision_case->centre_vision = 0;
	une_vision_case->champ_vision = JAMAIS_VISITEE;
}

void liberer_vision_case(Vision_case* une_vision_case)
{
	une_vision_case->indice_joueur = -1;
	une_vision_case->case_terrain_espace = NULL;
	une_vision_case->centre_vision = 0;
	une_vision_case->champ_vision = JAMAIS_VISITEE;
}

void liberer_vision_terrain(Vision_terrain* une_vision_terrain)
{
	une_vision_terrain->indice_joueur = -1;
	une_vision_terrain->terrain_espace = NULL;
	free(une_vision_terrain->vision_case);
}

void detruire_vision_terrain(Vision_terrain** une_vision_terrain)
{
	liberer_vision_terrain(*une_vision_terrain);
	free(*une_vision_terrain);
	une_vision_terrain = NULL;
}


/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

Vision_case* get_vision_case(Vision_terrain* une_vision, int x, int y)
{
	return &(une_vision->vision_case[y*(une_vision->terrain_espace->taille_espace_x)+x]);
}


/************************************************************************/
/* Fonctions qui vont définir la vision du terrain                      */
/************************************************************************/

/*fonction qui va parcourir tout le terrain et définir pour un joueur donné ses centres de vision*/
void parcourir_terrain(Vision_terrain* une_vision, Joueur* un_joueur)
{
	int i, j, indice_joueur;
	Case_terrain_espace* une_case;
	Terrain_espace* un_terrain = une_vision->terrain_espace;
	Vision_case* une_vision_case;
	indice_joueur = get_numero_joueur(un_joueur);
	for(i=0;i<un_terrain->taille_espace_y;i++)
	{
		for(j=0;j<un_terrain->taille_espace_x;j++)
		{
			une_case = get_case_terrain_espace(un_terrain, j, i);
			une_vision_case = get_vision_case(une_vision, i, j);
			/*on met toutes les cases précédemment visitée a VISITEE*/
			if (une_vision_case->champ_vision == AFFICHEE)
			{
				une_vision_case->champ_vision = VISITEE;
			}
			/*on calcule ensuite les centres de vision*/
			if(une_case->presence_flotte)
			{
				if(une_case->flotte->indice_joueur == indice_joueur)
				{
					une_vision_case->centre_vision = une_case->flotte->vision;
					une_vision_case->champ_vision = AFFICHEE;
				}
			}
			if (une_case->type_case_terrain_espace == 'P')
			{
				if(une_case->planete->indice_joueur == indice_joueur)
				{
					une_vision_case->centre_vision = une_case->planete->vision;
					une_vision_case->champ_vision = AFFICHEE;
				}
			}
		}
	}
}

/*fonction qui à partir des centres de vision va calculer la vision pour les cases autour*/
void definir_vision(Vision_terrain* une_vision)
{
	int i, j;
	int rayon, k, l;
	Terrain_espace* un_terrain;
	Vision_case* une_vision_case;

	for(i=0;i<un_terrain->taille_espace_y;i++)
	{
		for(j=0;j<un_terrain->taille_espace_x;j++)
		{
			une_vision_case = get_vision_case(une_vision, i, j);
			if (une_vision_case->centre_vision > 0)
			{
				rayon = une_vision_case->centre_vision;
				for(k = (i-rayon);k <= (i+rayon);k++)
				{
					for(l = (j-rayon);l <= (j+rayon);l++)
					{
						if((k>0) && (k<un_terrain->taille_espace_y) && (l>0) && (l<un_terrain->taille_espace_x))
						{
							une_vision_case->champ_vision = AFFICHEE;
						}
					}
				}
			}
		}
	}
}