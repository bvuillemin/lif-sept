#include <stdlib.h>
#include <stdio.h>

#include "case.h"
#include "terrain.h"

void set_taille_x(Terrain *terrain_jeu, int x)
{
    terrain_jeu->taille_x = x;
}

int get_taille_x(const Terrain *terrain_jeu)
{
    return terrain_jeu->taille_x;
}

void set_taille_y(Terrain *terrain_jeu, int y)
{
    terrain_jeu->taille_y = y;
}

int get_taille_y(const Terrain *terrain_jeu)
{
    return terrain_jeu->taille_y;
}

Case_terrain get_case_terrain(const Terrain *terrain, const int x, const int y)
{
    return terrain->tab_terrain[x*(terrain->taille_x)+y];
    //return terrain->tab_terrain[y*(terrain->taille_y)+x];
}

void set_case_terrain(const Terrain *terrain, int x, int y, char c)
{
    terrain->tab_terrain[y*(terrain->taille_y)+x].type_case = c;
}


void initialise_terrain(Terrain *terrain_jeu, int taille_x, int taille_y)
{
    terrain_jeu->taille_x = taille_x;
    terrain_jeu->taille_y = taille_y;
    terrain_jeu->tab_terrain = (Case_terrain *)malloc(sizeof(Case_terrain)*taille_x*taille_y);

}

Terrain *creer_terrain(int taille_x, int taille_y)
{
    Terrain *terrain = (Terrain *)malloc(sizeof(Terrain));
    initialise_terrain(terrain, taille_x, taille_y);
    return terrain;
}

void libere_terrain(Terrain *terrain_jeu)
{
    free(terrain_jeu->tab_terrain);
    terrain_jeu->taille_x=0;
    terrain_jeu->taille_y=0;
}

void detruit_terrain(Terrain **terrain_jeu)
{
    libere_terrain(*terrain_jeu);
    free(*terrain_jeu);
    *terrain_jeu = NULL;
}



void affiche_terrain(const Terrain *terrain)
{
    int i, j;
    Case_terrain unecase;
    for(i=0;i<terrain->taille_x;i++)
    {
        for(j=0;j<terrain->taille_y;j++)
        {
            unecase = get_case_terrain(terrain, i, j);
            printf("|%c|", unecase.type_case);
        }
        printf("\n");
    }
}


void modification_terrain(const Terrain *terrain, const char c)
{
    int i, j;
    for(i=0;i<terrain->taille_x;i++)
    {
        for(j=0;j<terrain->taille_y;j++)
        {
            set_case_terrain(terrain, i, j, c);
        }
    }
}


void test_module_terrain()
{
    Terrain *terrain;
    terrain = creer_terrain(20, 20);
    modification_terrain(terrain, 'E');
    set_case_terrain(terrain, 1, 2, 'P');
    affiche_terrain(terrain);
}


