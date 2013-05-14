#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "ia.h"
#include "vision.h"

void appeler_ia(Terrain_espace* un_terrain_espace, Joueur *un_joueur)
{
	choisir_case_deplacement_ia(un_joueur, un_terrain_espace, un_joueur->tab_flotte);
}


bool detecter_case_non_visitee_plus_proche(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte* une_flotte, int* x, int *y)
{
	int i, j;
	bool trouve = false;
	Vision_case* une_case;
	int distance;
	int distance_min = 1000;
	int x_trouve, y_trouve;
	int aleatoire = 0;

	for(i=0;i<un_terrain_espace->taille_espace_x;i++)
	{
		for(j=0;j<un_terrain_espace->taille_espace_y;j++)
		{
			une_case = get_vision_case(un_joueur->vision_terrain, i, j);
			if(une_case->champ_vision == JAMAIS_VISITEE)
			{
				trouve = true;
				distance = calcul_distance(get_x_flotte(une_flotte), get_y_flotte(une_flotte), i, j);

				/*Génération d'un nombre aléatoire entre 0 et 1, le rand()%1 ne peut pas marcher*/
				aleatoire = rand()%10;
				if(aleatoire < 5)
				{
					aleatoire = 0;
				}
				else
				{
					aleatoire = 1;
				}

				if(aleatoire == 0)
				{
					if((distance < distance_min))
					{
						distance_min = distance;
						x_trouve = i;
						y_trouve = j;
					}
				}
				if(aleatoire == 1)
				{
					if((distance <= distance_min))
					{
						distance_min = distance;
						x_trouve = i;
						y_trouve = j;
					}
				}
			}
		}
	}
	if(trouve)
	{
		*x = x_trouve;
		*y = y_trouve;
		return true;
	}
	return false;
}

void recherche_chemin_plus_court_flotte(Terrain_espace* un_terrain_espace, Flotte* une_flotte, int x_destination, int y_destination, int* res_x, int* res_y)
{
	int x,y; /*Coordonnées du point de départ*/
	int i, j; /*Compteurs de boucle*/
	int portee, x_max, y_max, x_min, y_min; /*Bornes de l'ensemble de recherche*/
	int distance_arrivee; /*Sera le minimum jusqu'au point d'arrivée*/
	int res_x_min, res_y_min;

	x = get_x_flotte(une_flotte);
	y = get_y_flotte(une_flotte);
	portee = get_pt_mouvement_espace_flotte(une_flotte);

	x_max = x + portee;
	y_max = y + portee;
	x_min = x - portee;
	y_min = y - portee;

	/*on verifie qu'on ne sort pas du terrain*/
	if(x_max >= un_terrain_espace->taille_espace_x)
	{
		x_max = un_terrain_espace->taille_espace_x;
	}
	if(y_max >= un_terrain_espace->taille_espace_y)
	{
		y_max = un_terrain_espace->taille_espace_y;
	}
	if(x_min < 0)
	{
		x_min = 0;
	}
	if(y_min < 0)
	{
		y_min = 0;
	}

	/*On initialise les valeurs du minimum*/
	distance_arrivee = calcul_distance(x_min, y_min, x_destination, y_destination);
	res_x_min = x_min;
	res_y_min = y_min;

	/*on va chercher dans la boucle la valeur à portée de la flotte et qui correspond au min de la distance avec la destination*/
	for(i=x_min;i<=x_max;i++)
	{
		for(j=y_min;j<=y_max;j++)
		{
			if(calcul_distance(i, j, x, y) <= portee)
			{
				if(calcul_distance(i, j, x_destination, y_destination) < distance_arrivee)
				{
					distance_arrivee = calcul_distance(i, j, x_destination, y_destination);
					res_x_min = i;
					res_y_min = j;
				}
			}
		}
	}
	*res_x = res_x_min;
	*res_y = res_y_min;
}

void choisir_case_deplacement_ia(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte* une_flotte)
{
	int i, j;
	int k, l;
	int x, y;
	int x2, y2;

	if (true) /*rajouter flag exploration*/
	{
		while(une_flotte->pt_mouvement_espace_flotte > 0)
		{
			if(detecter_case_non_visitee_plus_proche(un_joueur, un_terrain_espace, une_flotte, &x, &y))
			{
				if (calcul_distance(get_x_flotte(une_flotte), get_y_flotte(une_flotte), x, y) <= get_pt_mouvement_espace_flotte(une_flotte))
				{
					printf("deplacement flotte depuis %d-%d a case %d-%d (case non visitee a portee)\n", get_x_flotte(une_flotte), get_y_flotte(une_flotte), x, y);
					deplacement_flotte(un_joueur, un_terrain_espace, une_flotte, x, y);
				}
				else
				{
					recherche_chemin_plus_court_flotte(un_terrain_espace, une_flotte, x, y, &x2, &y2);
					printf("deplacement flotte depuis %d-%d a case %d-%d (case non visitee pas a portee) \n", get_x_flotte(une_flotte), get_y_flotte(une_flotte), x2, y2);
					deplacement_flotte(un_joueur, un_terrain_espace, une_flotte, x2, y2);
				}		
			}
			else
			{
				i = rand()%un_terrain_espace->taille_espace_x;
				j = rand()%un_terrain_espace->taille_espace_y;
				if(calcul_distance(get_x_flotte(une_flotte), get_y_flotte(une_flotte), i, j) <= get_pt_mouvement_espace_flotte(une_flotte))
				{
					k = get_x_flotte(une_flotte);
					l = get_y_flotte(une_flotte);
					deplacement_flotte(un_joueur, un_terrain_espace, une_flotte, i, j);
					printf("deplacement flotte depuis %d-%d a case %d-%d\n",k, l, i, j);
				}
			}
			parcourir_terrain(un_joueur->vision_terrain, 0);
		}
	}
}