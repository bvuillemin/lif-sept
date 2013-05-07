#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "case_terrain_espace.h"
#include "terrain_espace.h"
#include "joueur.h"

void set_taille_espace_x(Terrain_espace *terrain_jeu_espace, int x)
{
    terrain_jeu_espace->taille_espace_x = x;
}

int get_taille_espace_x(const Terrain_espace *terrain_jeu_espace)
{
    return terrain_jeu_espace->taille_espace_x;
}

void set_taille_espace_y(Terrain_espace *terrain_jeu_espace, int y)
{
    terrain_jeu_espace->taille_espace_y = y;
}

int get_taille_espace_y(const Terrain_espace *terrain_jeu_espace)
{
    return terrain_jeu_espace->taille_espace_y;
}

Case_terrain_espace* get_case_terrain_espace(const Terrain_espace *terrain_espace, const int x, const int y)
{
    return &(terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_x)+x]);
}

void modifie_type_case_terrain_espace(const Terrain_espace *terrain_espace, int x, int y, char c)
{
	set_type_case_terrain_espace(terrain_espace->tab_terrain_espace+(y*(terrain_espace->taille_espace_x)+x),c);
}

Planete* get_planete_terrain_espace(const Terrain_espace *terrain_espace, int x, int y)
{
	if(terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_x)+x].type_case_terrain_espace == 'P')
	{
		return terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_x)+x].planete;
	}
	else {return NULL;}
}

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

void affiche_terrain_espace(const Terrain_espace *terrain_espace)
{
    int i, j;
    Case_terrain_espace *une_case;
    for(j=0;j<terrain_espace->taille_espace_y;j++)
    {
        for(i=0;i<terrain_espace->taille_espace_x;i++)
        {
            une_case = get_case_terrain_espace(terrain_espace, i, j);
            if(une_case->presence_flotte == true)
            {
                printf("|F|");
            }
            else{printf("|%c|", une_case->type_case_terrain_espace);}
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

void ajouter_planete_terrain_espace(Terrain_espace *terrain_espace, int x, int y, char nom_planete[30])
{
    Planete *terre;
    terre = creer_planete(nom_planete);
    ajouter_planete(&(terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_x)+x]), terre);
}


void calcul_deplacement_flotte(Flotte *une_flotte)
{
    int i;
    int min = 1000;
    for(i=0;i<une_flotte->taille_flotte;i++)
    {
        if (une_flotte->tab_unite[i].pt_mouvement_unite < min)
        {
            min = une_flotte->tab_unite[i].pt_mouvement_unite;
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

bool deplacement_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y)
{
    if(peut_se_deplacer(une_flotte, x, y))
    {
        int distance;
        int x_depart, y_depart;
        Case_terrain_espace *case_depart;
        Case_terrain_espace *case_arrivee;
        x_depart = get_x_flotte(une_flotte);
        y_depart = get_y_flotte(une_flotte);
        case_depart = get_case_terrain_espace(un_terrain_espace, x_depart, y_depart);
        case_arrivee = get_case_terrain_espace(un_terrain_espace, x, y);
        if((x_depart == x) && (y_depart == y))
        {
            return false;
        }
		if(case_arrivee->presence_flotte == false)
		{
			ajouter_flotte(case_arrivee, une_flotte);
			retirer_flotte(case_depart);
			distance = calcul_distance(x_depart, y_depart, x, y);
			enlever_pt_mouvement_espace_flotte(une_flotte, distance);
			return true;
		}
		if(case_arrivee->presence_flotte == true)
		{
		    if(fusion_flotte(un_joueur, un_terrain_espace, une_flotte, x, y))
		    {
		        /*free(une_flotte);*/
		        return true;
		    }
		}
    }
    return false;
}

bool fusion_flotte(Joueur *un_joueur, Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y)
{
    int i;
    int nb_unite = une_flotte->taille_flotte;
    int distance;
    int pt_mvt_arrivee;
    int pt_mvt_depart = get_pt_mouvement_espace_flotte(une_flotte);
    int x_depart = get_x_flotte(une_flotte);
    int y_depart = get_y_flotte(une_flotte);
    Case_terrain_espace *case_depart;
    Case_terrain_espace *case_arrivee;
    Flotte *flotte_arrivee;

    case_depart = get_case_terrain_espace(un_terrain_espace, x_depart, y_depart);
    case_arrivee = get_case_terrain_espace(un_terrain_espace, x, y);
    flotte_arrivee = get_flotte(case_arrivee);
    pt_mvt_arrivee = get_pt_mouvement_espace_flotte(flotte_arrivee);

    if((flotte_arrivee->taille_flotte + une_flotte->taille_flotte <= flotte_arrivee->taille_maximum_flotte) && (une_flotte->indice_joueur == flotte_arrivee->indice_joueur))
    {
        for(i=0;i<nb_unite;i++)
        {
            transferer_unite_flotte(flotte_arrivee, &une_flotte->tab_unite[i]);
        }
        retirer_flotte(case_depart);
        if(une_flotte->indice_tableau_joueur < flotte_arrivee->indice_tableau_joueur)
        {
            case_arrivee->flotte = &un_joueur->tab_flotte[flotte_arrivee->indice_tableau_joueur - 1];
        }
        else
        {
            case_arrivee->flotte = &un_joueur->tab_flotte[flotte_arrivee->indice_tableau_joueur];
        }
        retirer_flotte_joueur(un_joueur, une_flotte->indice_tableau_joueur);
        /*liberer_flotte(une_flotte);*/
        /*free(une_flotte);*/

        distance = calcul_distance(x_depart, y_depart, x, y);
        if(pt_mvt_arrivee > (pt_mvt_depart - distance))
        {
            enlever_pt_mouvement_espace_flotte(flotte_arrivee, distance);
        }
        return true;
    }
    return false;
}

void sauvegarde_terrain_espace(const Terrain_espace *un_terrain_espace, FILE*f)
{
    int i,j;
    fprintf(f, "Terrain_Espace\n");
    fprintf(f, "%d\n", un_terrain_espace->taille_espace_x);
    fprintf(f, "%d\n", un_terrain_espace->taille_espace_y);
    for(i=0;i<un_terrain_espace->taille_espace_x;i++)
    {
        for(j=0;j<un_terrain_espace->taille_espace_y;j++)
        {
            sauvegarde_case_terrain_espace(&un_terrain_espace->tab_terrain_espace[i*(un_terrain_espace->taille_espace_y)+j], f);
        }
    }
    fprintf(f, "FinTerrain_Espace\n");
}

Terrain_espace* ouverture_terrain(FILE *f)
{
    Terrain_espace *terrain_ouvert;
    char chaine[50];
    int b, c, i, j;
    sscanf(fgets(chaine, 50, f), "%d", &b);
    sscanf(fgets(chaine, 50, f), "%d", &c);
    terrain_ouvert = creer_terrain_espace(b, c);
    for(i=0;i<terrain_ouvert->taille_espace_x;i++)
    {
        for(j=0;j<terrain_ouvert->taille_espace_y;j++)
        {
            terrain_ouvert->tab_terrain_espace[i*(terrain_ouvert->taille_espace_y)+j] = *ouverture_case_terrain_espace(f);
        }
        printf("\n");
    }
    return terrain_ouvert;
}

/*void test_module_terrain_espace()
{
    Terrain_espace_espace *terrain_espace;
    terrain_espace = creer_terrain(20, 20);
    modification_terrain(terrain_espace, 'E');
    affiche_terrain(terrain_espace);

    ajouter_planete_terrain(terrain_espace, 4, 2);
    affiche_terrain(terrain_espace);

    affiche_planete(terrain_espace->tab_terrain_espace[2*(terrain_espace->taille_espace_x)+1].planete);

    detruit_terrain_espace(&terrain_espace);

}

*/

