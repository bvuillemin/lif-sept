#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "ia.h"

void appeler_ia(Terrain_espace* un_terrain_espace, Joueur *un_joueur)
{
	choisir_case_deplacement_ia(un_joueur, un_terrain_espace, un_joueur->tab_flotte);
}

void choisir_case_deplacement_ia(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte* une_flotte)
{
	int i, j;
	int k, l;
	if (true) /*rajouter flag exploration*/
	{
		while(une_flotte->pt_mouvement_espace_flotte > 0)
		{
			i = rand()%un_terrain_espace->taille_espace_x;
			j = rand()%un_terrain_espace->taille_espace_y;
			if(calcul_distance(une_flotte->x_flotte, une_flotte->y_flotte, i, j) == 10)
			{
				k = une_flotte->x_flotte;
				l = une_flotte->y_flotte;
				deplacement_flotte(un_joueur, un_terrain_espace, une_flotte, i, j);
				printf("deplacement flotte depuis %d-%d a case %d-%d",k, l, i, j);
			}
		}
	}

}