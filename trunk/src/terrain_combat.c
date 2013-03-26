#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "case_terrain_combat.h"
#include "terrain_combat.h"

void set_taille_combat_x(Terrain_combat *terrain_jeu_combat, int x)
{
    terrain_jeu_combat->taille_combat_x = x;
}

int get_taille_combat_x(const Terrain_combat *terrain_jeu_combat)
{
    return terrain_jeu_combat->taille_combat_x;
}

void set_taille_combat_y(Terrain_combat *terrain_jeu_combat, int y)
{
    terrain_jeu_combat->taille_combat_y = y;
}

int get_taille_combat_y(const Terrain_combat *terrain_jeu_combat)
{
    return terrain_jeu_combat->taille_combat_y;
}

Case_terrain_combat* get_case_terrain_combat(const Terrain_combat *terrain_combat, const int x, const int y)
{
    return &(terrain_combat->tab_terrain_combat[x*(terrain_combat->taille_combat_x)+y]);
}

void set_type_case_terrain_combat(const Terrain_combat *terrain_combat, int x, int y, char c)
{
    terrain_combat->tab_terrain_combat[y*(terrain_combat->taille_combat_y)+x].type_case_terrain_combat = c;
}

void initilalise_terrain_combat(Terrain_combat *terrain_jeu_combat, int taille_combat_x, int taille_combat_y)
{
    int i, j;
    terrain_jeu_combat->taille_combat_x = taille_combat_x;
    terrain_jeu_combat->taille_combat_y = taille_combat_y;
    terrain_jeu_combat->tab_terrain_combat = (Case_terrain_combat *)malloc(sizeof(Case_terrain_combat)*taille_combat_x*taille_combat_y);
    for(i=0;i<terrain_jeu_combat->taille_combat_x;i++)
    {
        for(j=0;j<terrain_jeu_combat->taille_combat_y;j++)
        {
           terrain_jeu_combat->tab_terrain_combat[j*(terrain_jeu_combat->taille_combat_y)+i].x_combat = i;
           terrain_jeu_combat->tab_terrain_combat[j*(terrain_jeu_combat->taille_combat_y)+i].y_combat = j;
        }
    }

}

Terrain_combat *creer_terrain_combat(int taille_combat_x, int taille_combat_y)
{
    Terrain_combat *terrain_combat = (Terrain_combat *)malloc(sizeof(Terrain_combat));
    initilalise_terrain_combat(terrain_combat, taille_combat_x, taille_combat_y);
    return terrain_combat;
}

void libere_terrain_combat(Terrain_combat *terrain_jeu_combat)
{
    free(terrain_jeu_combat->tab_terrain_combat);
    terrain_jeu_combat->taille_combat_x=0;
    terrain_jeu_combat->taille_combat_y=0;
}

void detruit_terrain_combat(Terrain_combat **terrain_jeu_combat)
{
    libere_terrain_combat(*terrain_jeu_combat);
    free(*terrain_jeu_combat);
    *terrain_jeu_combat = NULL;
}

void affiche_terrain_combat(const Terrain_combat *terrain_combat)
{
    int i, j;
    Case_terrain_combat *une_case;
    for(i=0;i<terrain_combat->taille_combat_x;i++)
    {
        for(j=0;j<terrain_combat->taille_combat_y;j++)
        {
            une_case = get_case_terrain_combat(terrain_combat, i, j);
            if(une_case->presence_unite == true)
            {
                printf("|F|");
            }
            else{printf("|%c|", une_case->type_case_terrain_combat);}
        }
        printf("\n");
    }
    printf("\n");
}

void modification_terrain_combat(const Terrain_combat *terrain_combat, const char c)
{
    int i, j;
    for(i=0;i<terrain_combat->taille_combat_x;i++)
    {
        for(j=0;j<terrain_combat->taille_combat_y;j++)
        {
            set_type_case_terrain_combat(terrain_combat, i, j, c);
        }
    }
}




/*void test_module_terrain_combat()
{
    Terrain_combat *terrain_combat;
    terrain_combat = creer_terrain(20, 20);
    modification_terrain(terrain_combat, 'E');
    affiche_terrain(terrain_combat);

    affiche_terrain(terrain_combat);

    detruit_terrain_combat(&terrain_combat);

}

*/

