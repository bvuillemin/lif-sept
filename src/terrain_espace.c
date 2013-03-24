#include <stdlib.h>
#include <stdio.h>

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

Case_terrain_espace get_case_terrain_espace(const Terrain_espace *terrain_espace, const int x, const int y)
{
    return terrain_espace->tab_terrain_espace[x*(terrain_espace->taille_espace_x)+y];
    /*return terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_y)+x];*/
}

void set_case_terrain_espace(const Terrain_espace *terrain_espace, int x, int y, char c)
{
    terrain_espace->tab_terrain_espace[y*(terrain_espace->taille_espace_y)+x].type_case_terrain_espace = c;
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
    Case_terrain_espace unecase;
    for(i=0;i<terrain_espace->taille_espace_x;i++)
    {
        for(j=0;j<terrain_espace->taille_espace_y;j++)
        {
            unecase = get_case_terrain_espace(terrain_espace, i, j);
            printf("|%c|", unecase.type_case_terrain_espace);
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
            set_case_terrain_espace(terrain_espace, i, j, c);
        }
    }
}

void ajouter_planete_terrain_espace(Terrain_espace *terrain_espace, int x, int y)
{
    Planete *terre;
    terre = creer_planete();
    ajouter_planete(&(terrain_espace->tab_terrain_espace[x*(terrain_espace->taille_espace_x)+y]), terre);
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

