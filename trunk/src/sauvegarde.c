#include <stdlib.h>
#include <stdio.h>

#include "terrain_espace.h"

void sauvegarde_terrain(const Terrain_espace *terrain_jeu_espace, const char nom[30])
{
    FILE *f;
    int i,j;
    f = fopen(nom, "w");
    if (f==NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", nom);
    }

    for(i=0;i<terrain_jeu_espace->taille_espace_x;i++)
    {
        fprintf(f, "#");
        for(j=0;j<terrain_jeu_espace->taille_espace_y;j++)
        {
           fprintf(f,"%c", terrain_jeu_espace->tab_terrain_espace[j*(terrain_jeu_espace->taille_espace_y)+i].type_case_terrain_espace);
        }
        fprintf(f, "#\n");
    }
    fclose(f);
}
