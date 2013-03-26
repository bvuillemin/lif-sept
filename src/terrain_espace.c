#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "case_terrain_espace.h"
#include "terrain_espace.h"

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
    return &(terrain_espace->tab_terrain_espace[x*(terrain_espace->taille_espace_x)+y]);
}

void modifie_type_case_terrain_espace(const Terrain_espace *terrain_espace, int x, int y, char c)
{
    terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_y)+x].type_case_terrain_espace = c;
}

Planete* get_planete_terrain_espace(const Terrain_espace *terrain_espace, int x, int y)
{
    return terrain_espace->tab_terrain_espace[x*(terrain_espace->taille_espace_x)+y].planete;
}

void initilalise_terrain_espace(Terrain_espace *terrain_jeu_espace, int taille_espace_x, int taille_espace_y)
{
    int i, j;
    terrain_jeu_espace->taille_espace_x = taille_espace_x;
    terrain_jeu_espace->taille_espace_y = taille_espace_y;
    terrain_jeu_espace->tab_terrain_espace = (Case_terrain_espace *)malloc(sizeof(Case_terrain_espace)*taille_espace_x*taille_espace_y);
    for(i=0;i<terrain_jeu_espace->taille_espace_x;i++)
    {
        for(j=0;j<terrain_jeu_espace->taille_espace_y;j++)
        {
           terrain_jeu_espace->tab_terrain_espace[j*(terrain_jeu_espace->taille_espace_y)+i].x_espace = i;
           terrain_jeu_espace->tab_terrain_espace[j*(terrain_jeu_espace->taille_espace_y)+i].y_espace = j;
        }
    }

}

Terrain_espace *creer_terrain_espace(int taille_espace_x, int taille_espace_y)
{
    Terrain_espace *terrain_espace = (Terrain_espace *)malloc(sizeof(Terrain_espace));
    initilalise_terrain_espace(terrain_espace, taille_espace_x, taille_espace_y);
    return terrain_espace;
}

void libere_terrain_espace(Terrain_espace *terrain_jeu_espace)
{
    free(terrain_jeu_espace->tab_terrain_espace);
    terrain_jeu_espace->taille_espace_x=0;
    terrain_jeu_espace->taille_espace_y=0;
}

void detruit_terrain_espace(Terrain_espace **terrain_jeu_espace)
{
    libere_terrain_espace(*terrain_jeu_espace);
    free(*terrain_jeu_espace);
    *terrain_jeu_espace = NULL;
}

void affiche_terrain_espace(const Terrain_espace *terrain_espace)
{
    int i, j;
    Case_terrain_espace *une_case;
    for(i=0;i<terrain_espace->taille_espace_x;i++)
    {
        for(j=0;j<terrain_espace->taille_espace_y;j++)
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

void ajouter_planete_terrain_espace(Terrain_espace *terrain_espace, int x, int y)
{
    Planete *terre;
    terre = creer_planete();
    ajouter_planete(&(terrain_espace->tab_terrain_espace[x*(terrain_espace->taille_espace_x)+y]), terre);
}


void calcul_deplacement_flotte(Flotte *une_flotte)
{
    int i;
    int min = 1000;
    for(i=0;i<une_flotte->taille_flotte;i++)
    {
        if (une_flotte->tab_unite[i].pt_mouvement_espace < min)
        {
            min = une_flotte->tab_unite[i].pt_mouvement_espace;
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

    if((x>x_min) && (x<x_max) && (y>y_min) && (y<y_max))
    {
        return true;
    }
    else {return false;}
}

bool deplacement_flotte(Terrain_espace *un_terrain_espace, Flotte *une_flotte, int x, int y)
{
    if(peut_se_deplacer(une_flotte, x, y))
    {
        int x_depart, y_depart;
        x_depart = get_x_flotte(une_flotte);
        y_depart = get_y_flotte(une_flotte);
        Case_terrain_espace *case_depart;
        Case_terrain_espace *case_arrivee;
        case_depart = get_case_terrain_espace(un_terrain_espace, x_depart, y_depart);
        case_arrivee = get_case_terrain_espace(un_terrain_espace, x, y);
        ajouter_flotte(case_arrivee, une_flotte);
        retirer_flotte(case_depart);

        return true;
    }
    else {return false;}

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

