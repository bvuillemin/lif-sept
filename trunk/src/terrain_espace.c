/**
 * \file      terrain_espace.c
 * \author    BODARD, REYNAUD, VUILLEMIN
 * \version   1.0
 * \brief     Définit un terrain d'espace
 * \details   Cette classe définit un terrain d'espace et ses caractéristiques
 */

#include <math.h>
#include <assert.h>
#include "terrain_espace.h"

/************************************************************************/
/* Initialisation, création et destruction                              */
/************************************************************************/

void initilaliser_terrain_espace(Terrain_espace *terrain_jeu_espace, int taille_espace_x, int taille_espace_y)
{
	int i, j;
	terrain_jeu_espace->taille_espace_x = taille_espace_x;
	terrain_jeu_espace->taille_espace_y = taille_espace_y;
	terrain_jeu_espace->tab_terrain_espace = (Case_terrain_espace *)malloc(sizeof(Case_terrain_espace)*(taille_espace_x*taille_espace_y+taille_espace_x));
	for(i=0;i<terrain_jeu_espace->taille_espace_y;i++)
	{
		for(j=0;j<terrain_jeu_espace->taille_espace_x;j++)
		{
			initialiser_case_espace(&(terrain_jeu_espace->tab_terrain_espace[i*(terrain_jeu_espace->taille_espace_x)+j]));
			terrain_jeu_espace->tab_terrain_espace[i*(terrain_jeu_espace->taille_espace_x)+j].x_espace = j;
			terrain_jeu_espace->tab_terrain_espace[i*(terrain_jeu_espace->taille_espace_x)+j].y_espace = i;
		}
	}
	terrain_jeu_espace->affichage_x=1;
	terrain_jeu_espace->affichage_y=1;

}

Terrain_espace *creer_terrain_espace(int taille_espace_x, int taille_espace_y)
{
	Terrain_espace *terrain_espace = (Terrain_espace *)malloc(sizeof(Terrain_espace));
	initilaliser_terrain_espace(terrain_espace, taille_espace_x, taille_espace_y);
	return terrain_espace;
}

void liberer_terrain_espace(Terrain_espace *terrain_jeu_espace)
{
	int i, j;
	for(i=0;i<terrain_jeu_espace->taille_espace_y;i++)
	{
		for(j=0;j<terrain_jeu_espace->taille_espace_x;j++)
		{
			liberer_case_terrain_espace(terrain_jeu_espace->tab_terrain_espace + (i*(terrain_jeu_espace->taille_espace_x)+j));
		}
	}
	free(terrain_jeu_espace->tab_terrain_espace);
	terrain_jeu_espace->taille_espace_x=0;
	terrain_jeu_espace->taille_espace_y=0;
	terrain_jeu_espace->affichage_x=0;
	terrain_jeu_espace->affichage_y=0;
}

void detruire_terrain_espace(Terrain_espace **terrain_jeu_espace)
{
	liberer_terrain_espace(*terrain_jeu_espace);
	free(*terrain_jeu_espace);
	*terrain_jeu_espace = NULL;
}


/************************************************************************/
/* Fonctions set et get                                                 */
/************************************************************************/

int get_taille_espace_x(const Terrain_espace *terrain_jeu_espace)
{
    return terrain_jeu_espace->taille_espace_x;
}

int get_taille_espace_y(const Terrain_espace *terrain_jeu_espace)
{
    return terrain_jeu_espace->taille_espace_y;
}

Case_terrain_espace* get_case_terrain_espace(const Terrain_espace *terrain_espace, const int x, const int y)
{
	assert((x>=0)&&(y>=0)&&(x<terrain_espace->taille_espace_x)&&(y<terrain_espace->taille_espace_y));
	return &(terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_x)+x]);
}

Planete* get_planete_terrain_espace(const Terrain_espace *terrain_espace, int x, int y)
{
	assert((x>=0)&&(y>=0)&&(x<terrain_espace->taille_espace_x)&&(y<terrain_espace->taille_espace_y));
	if(terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_x)+x].type_case_terrain_espace == 'P')
	{
		return terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_x)+x].planete;
	}
	else {return NULL;}
}

void set_affichage(Terrain_espace* un_terrain, int x, int y)
{
	un_terrain->affichage_x = x;
	un_terrain->affichage_y = y;
}

int get_affichage_x(const Terrain_espace* un_terrain)
{
	return un_terrain->affichage_x;
}

int get_affichage_y(const Terrain_espace* un_terrain)
{
	return un_terrain->affichage_y;
}

void set_affichage_x(Terrain_espace* un_terrain, int nb)
{
	un_terrain->affichage_x = nb;
}

void set_affichage_y(Terrain_espace* un_terrain, int nb)
{
	un_terrain->affichage_y = nb;
}


/************************************************************************/
/* Fonctions diverses                                                   */
/************************************************************************/

void modifie_type_case_terrain_espace(const Terrain_espace *terrain_espace, int x, int y, char c)
{
	set_type_case_terrain_espace(terrain_espace->tab_terrain_espace+(y*(terrain_espace->taille_espace_x)+x),c);
}

void affiche_terrain_espace(const Terrain_espace *terrain_espace)
{
    int i, j;
    Case_terrain_espace *une_case;
    for(j=0;j <= terrain_espace->taille_espace_y;j++)
    {
        for(i=0;i<=terrain_espace->taille_espace_x;i++)
        {
			if((i == 0) && (j != 0))
			{
				printf("|%d|", j%10);
			}
			if(j == 0)
			{
				printf("|%d|", i%10);
			}
			if((i!=0) && (j!=0))
			{
				une_case = get_case_terrain_espace(terrain_espace, i - 1, j - 1);
				if(une_case->presence_flotte == true)
				{
					printf("|F|");
				}
				else{printf("|%c|", une_case->type_case_terrain_espace);}
			}
        }
        printf("\n");
    }
    printf("\n");
}

void modification_terrain_espace(const Terrain_espace *terrain_espace, const char c)
{
    int i, j;
    for(i=0;i<terrain_espace->taille_espace_x;i++)
    {
        for(j=0;j<terrain_espace->taille_espace_y;j++)
        {
            modifie_type_case_terrain_espace(terrain_espace, i, j, c);
        }
    }
}

void ajouter_planete_terrain_espace(Terrain_espace *terrain_espace, int x, int y, char nom_planete[30], int metal, int argent, int carburant, int  population)
{
    Planete *une_planete;
    une_planete = creer_planete(nom_planete);
	modification_production_planete(une_planete, metal, argent, carburant, population);
    ajouter_planete(&(terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_x)+x]), une_planete);
}

void calcul_deplacement_flotte(Flotte *une_flotte)
{
    int i;
    int min = 1000;
    for(i=0;i<une_flotte->taille_flotte;i++)
    {
        if (une_flotte->tab_unite[i]->pt_mouvement_unite < min)
        {
            min = une_flotte->tab_unite[i]->pt_mouvement_unite;
        }
    }
    une_flotte->pt_mouvement_espace_flotte = min;
}

bool peut_se_deplacer(Flotte *une_flotte, int x, int y)
{
    int x_min, y_min, x_max, y_max;
    x_min = une_flotte->x_flotte - une_flotte->pt_mouvement_espace_flotte;
    y_min = une_flotte->y_flotte - une_flotte->pt_mouvement_espace_flotte;
    x_max = une_flotte->x_flotte + une_flotte->pt_mouvement_espace_flotte;
    y_max = une_flotte->y_flotte + une_flotte->pt_mouvement_espace_flotte;

    if((x>=x_min) && (x<=x_max) && (y>=y_min) && (y<=y_max) && (une_flotte->pt_mouvement_espace_flotte >= 0))
    {
        return true;
    }
    else {return false;}
}

int calcul_distance(int x_depart, int y_depart, int x_arrivee, int y_arrivee)
{
    return ceil(sqrt(pow(x_depart - x_arrivee, 2) + pow(y_depart - y_arrivee, 2)) - 0.1); /*on enleve 0.1 pour etre un peu plus précis: si on se deplace de 7.05 on veut que ce soit 7*/
}

int indice_tableau(Terrain_espace* un_terrain_espace, int x, int y)
{
	return y*(un_terrain_espace->taille_espace_x)+x;
}



/************************************************************************/
/* Fonctions sauvegarde et chargement                                   */
/************************************************************************/

void sauvegarde_terrain_espace(const Terrain_espace *un_terrain_espace, FILE*f)
{
    int i,j;
    fprintf(f, "Terrain_Espace\n");
    fprintf(f, "%d\n", un_terrain_espace->taille_espace_x);
    fprintf(f, "%d\n", un_terrain_espace->taille_espace_y);
    for(j=0;j<un_terrain_espace->taille_espace_y;j++)
    {
        for(i=0;i<un_terrain_espace->taille_espace_x;i++)
        {
            sauvegarde_case_terrain_espace(&un_terrain_espace->tab_terrain_espace[i*(un_terrain_espace->taille_espace_y)+j], f);
        }
    }
}

Terrain_espace* ouverture_terrain_espace(FILE *f)
{
    Terrain_espace *terrain_ouvert;
    char chaine[50];
    int b, c, i, j;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    sscanf(fgets(chaine, 50, f), "%d", &c);
    terrain_ouvert = creer_terrain_espace(b, c);
    for(j=0;j<terrain_ouvert->taille_espace_y;j++)
    {
        for(i=0;i<terrain_ouvert->taille_espace_x;i++)
        {
            terrain_ouvert->tab_terrain_espace[i*(terrain_ouvert->taille_espace_y)+j] = *ouverture_case_terrain_espace(f);
        }
    }
    return terrain_ouvert;
}

void testRegression_Terrain_espace(void)
{
    Terrain_espace *un_terrain_espace;
    un_terrain_espace = creer_terrain_espace(1, 1);
    modification_terrain_espace(un_terrain_espace, 'E');
    assert(un_terrain_espace->tab_terrain_espace->type_case_terrain_espace == 'E');
    detruire_terrain_espace(&un_terrain_espace);

}